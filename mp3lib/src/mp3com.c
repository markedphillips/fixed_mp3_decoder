/* (c) 1998-2018 Mark Phillips Copyright */

#include <ctype.h>
#include <stdlib.h>
#include <signal.h>
#include "debug.h"

#include "mp3.h"

//#define TEST_EVERY_HEADER

struct parameter param = { 1 , 1 , 0 , 0 };

int mp3_tabsel_123[2][3][16] = {
   { {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,},
     {0,32,48,56, 64, 80, 96,112,128,160,192,224,256,320,384,},
     {0,32,40,48, 56, 64, 80, 96,112,128,160,192,224,256,320,} },

   { {0,32,48,56,64,80,96,112,128,144,160,176,192,224,256,},
     {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,},
     {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,} }
};

long mp3_freqs[9] = { 44100, 48000, 32000,
                  22050, 24000, 16000 ,
                  11025 , 12000 , 8000 };

int bitindex;
unsigned char *wordpointer;
unsigned char *pcm_sample;
int mp3_pcm_point = 0;


#if 0
static void get_II_stuff(struct mp3frame *fr)
{
  static int translate[3][2][16] = 
   { { { 0,2,2,2,2,2,2,0,0,0,1,1,1,1,1,0 } ,
       { 0,2,2,0,0,0,1,1,1,1,1,1,1,1,1,0 } } ,
     { { 0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0 } ,
       { 0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0 } } ,
     { { 0,3,3,3,3,3,3,0,0,0,1,1,1,1,1,0 } ,
       { 0,3,3,0,0,0,1,1,1,1,1,1,1,1,1,0 } } };

  int table,sblim;
  static struct al_table *tables[5] = 
       { alloc_0, alloc_1, alloc_2, alloc_3 , alloc_4 };
  static int sblims[5] = { 27 , 30 , 8, 12 , 30 };

  if(fr->lsf)
    table = 4;
  else
    table = translate[fr->sampling_frequency][2-fr->stereo][fr->bitrate_index];
  sblim = sblims[table];

  fr->alloc = tables[table];
  fr->II_sblimit = sblim;
}
#endif

#define HDRCMPMASK 0xfffffd00

//#define	SUPPORT_25	// Uncomment this to enable support for MPEG Layer 2.5

//#if 0
int head_check(unsigned long head)
{
#ifdef SUPPORT_25
	if( (head & 0xffe00000) != 0xffe00000)
#else
	if( (head & 0xfff00000) != 0xfff00000)
#endif	// SUPPORT_25
		return 0;
	if(!((head>>17)&3))
		return 0;
	if( ((head>>12)&0xf) == 0xf)
		return 0;
	if( ((head>>10)&0x3) == 0x3 )
		return 0;
	return 1;
}
//#endif

static void print_header(struct mp3frame *fr)
{
	static char *modes[4] = { "Stereo", "Joint-Stereo", "Dual-Channel", "Single-Channel" };
	static char *layers[4] = { "Unknown" , "I", "II", "III" };
/*
	DEBUG("MPEG %s, Layer: %s, Freq: %d, mode: %s, modext: %d, BPF : %d\n", 
		fr->mpeg25 ? "2.5" : (fr->lsf ? "2.0" : "1.0"),
		layers[fr->lay],mp3_freqs[fr->sampling_frequency],
		modes[fr->mode],fr->mode_ext,fr->framesize+4);
	DEBUG("Channels: %d, copyright: %s, original: %s, CRC: %s, emphasis: %d.\n",
		fr->stereo,fr->copyright?"Yes":"No",
		fr->original?"Yes":"No",fr->error_protection?"Yes":"No",
		fr->emphasis);
	DEBUG("Bitrate: %d Kbits/s, Extension value: %d\n",
		mp3_tabsel_123[fr->lsf][fr->lay-1][fr->bitrate_index],fr->extension);
*/
}

#if 0
void print_header_compact(struct mp3frame *fr)
{
	static char *modes[4] = { "stereo", "joint-stereo", "dual-channel", "mono" };
	static char *layers[4] = { "Unknown" , "I", "II", "III" };
 
	DEBUG("MPEG %s layer %s, %d kbit/s, %d Hz %s\n",
		fr->mpeg25 ? "2.5" : (fr->lsf ? "2.0" : "1.0"),
		layers[fr->lay],
		mp3_tabsel_123[fr->lsf][fr->lay-1][fr->bitrate_index],
		mp3_freqs[fr->sampling_frequency], modes[fr->mode]);
}

#endif

/*
 * the code a header and write the information
 * into the frame structure
 */
int decode_header(struct mp3frame *fr, unsigned long newhead)
{
//static int s_brIndex = 0;
	int iRet = MP3_OK;

#ifdef TEST_EVERY_HEADER
	if (!head_check(newhead))
	{
		//DEBUG("Head check failed\n");
		return MP3_ERR;
	}
#endif	// TEST_EVERY_HEADER
    if( newhead & (1<<20) ) {
		fr->lsf = (newhead & (1<<19)) ? 0x0 : 0x1;
		fr->mpeg25 = 0;
    }
    else {
#ifdef SUPPORT_25
		fr->lsf = 1;
		fr->mpeg25 = 1;
#else
		//DEBUG("Layer 2.5 not supported!\n");
		return MP3_ERR;
#endif	// SUPPORT_25
    }
    
    fr->lay = 4-((newhead>>17)&3);
    if( ((newhead>>10)&0x3) == 0x3) {
      //DEBUG("Stream error\n");
	  return MP3_ERR;
    }
    if(fr->mpeg25) {
      fr->sampling_frequency = 6 + ((newhead>>10)&0x3);
    }
    else
      fr->sampling_frequency = ((newhead>>10)&0x3) + (fr->lsf*3);

    fr->error_protection = ((newhead>>16)&0x1)^0x1;

    if(fr->mpeg25) /* allow Bitrate change for 2.5 ... */
      fr->bitrate_index = ((newhead>>12)&0xf);

    fr->bitrate_index = ((newhead>>12)&0xf);
/*
if (s_brIndex != fr->bitrate_index)
DEBUG("Bitrate change: from %d to %d\n", s_brIndex, fr->bitrate_index);
s_brIndex = fr->bitrate_index;
*/
    fr->padding   = ((newhead>>9)&0x1);
    fr->extension = ((newhead>>8)&0x1);
    fr->mode      = ((newhead>>6)&0x3);
    fr->mode_ext  = ((newhead>>4)&0x3);
    fr->copyright = ((newhead>>3)&0x1);
    fr->original  = ((newhead>>2)&0x1);
    fr->emphasis  = newhead & 0x3;

    fr->stereo    = (fr->mode == MPG_MD_MONO) ? 1 : 2;

    if(!fr->bitrate_index)
    {
      //DEBUG("Free format not supported.\n");
      return MP3_ERR;
    }

    switch(fr->lay)
    {
      case 1:
#if 0
		fr->do_layer = do_layer1;
        fr->jsbound = (fr->mode == MPG_MD_JOINT_STEREO) ? 
                         (fr->mode_ext<<2)+4 : 32;
        fr->framesize  = (long) mp3_tabsel_123[fr->lsf][0][fr->bitrate_index] * 12000;
        fr->framesize /= mp3_freqs[fr->sampling_frequency];
        fr->framesize  = ((fr->framesize+fr->padding)<<2)-4;
#else
        //DEBUG("Layer 1 not supported!\n");
		return MP3_ERR;
#endif
        break;
      case 2:
#if 0
		fr->do_layer = do_layer2;
        get_II_stuff(fr);
        fr->jsbound = (fr->mode == MPG_MD_JOINT_STEREO) ?
                         (fr->mode_ext<<2)+4 : fr->II_sblimit;
        fr->framesize = (long) mp3_tabsel_123[fr->lsf][1][fr->bitrate_index] * 144000;
        fr->framesize /= mp3_freqs[fr->sampling_frequency];
        fr->framesize += fr->padding - 4;
#else
        //DEBUG("Layer 2 not supported!\n");
		return MP3_ERR;
#endif
        break;
      case 3:
#if 0
        fr->do_layer = do_layer3;
        if(fr->lsf)
          ssize = (fr->stereo == 1) ? 9 : 17;
        else
          ssize = (fr->stereo == 1) ? 17 : 32;
#endif

#if 0
        if(fr->error_protection)
          ssize += 2;
#endif
          fr->framesize  = (long) mp3_tabsel_123[fr->lsf][2][fr->bitrate_index] * 144000;
          fr->framesize /= mp3_freqs[fr->sampling_frequency]<<(fr->lsf);
          fr->framesize = fr->framesize + fr->padding - 4;
        break; 
      default:
        //DEBUG("Sorry, unknown layer type.\n"); 
        return MP3_ERR;
    }

#ifdef TEST_EVERY_HEADER
//	print_header(fr);
#endif	// TEST_EVERY_HEADER

    return iRet;

}

/*
 * the code a header and write the information
 * into the frame structure
 */
int decode_header_fast(struct mp3frame *fr, unsigned long newhead)
{
	int iRet = MP3_OK;
	int iOldPadding = fr->padding;

#ifdef EDDEBUG
	if (!head_check(newhead))
	{
		//DEBUG("Head check failed\n");
		return MP3_ERR;
	}
#endif	// EDDEBUG

    fr->padding   = ((newhead>>9)&0x1);

	fr->framesize += (fr->padding - iOldPadding);

/*
	fr->framesize  = (long) mp3_tabsel_123[fr->lsf][2][fr->bitrate_index] * 144000;
	fr->framesize /= mp3_freqs[fr->sampling_frequency]<<(fr->lsf);
	fr->framesize = fr->framesize + fr->padding - 4;
*/

    return iRet;

}

unsigned int mp3_getbits(int number_of_bits)
{
  unsigned long rval;

  if(!number_of_bits)
    return 0;

  {
    rval = wordpointer[0];
    rval <<= 8;
    rval |= wordpointer[1];
    rval <<= 8;
    rval |= wordpointer[2];
    rval <<= bitindex;
    rval &= 0xffffff;

    bitindex += number_of_bits;

    rval >>= (24-number_of_bits);

    wordpointer += (bitindex>>3);
    bitindex &= 7;
  }
  return rval;
}

unsigned int mp3_getbits_fast(int number_of_bits)
{
  unsigned long rval;

  {
    rval = wordpointer[0];
    rval <<= 8;	
    rval |= wordpointer[1];
    rval <<= bitindex;
    rval &= 0xffff;
    bitindex += number_of_bits;

    rval >>= (16-number_of_bits);

    wordpointer += (bitindex>>3);
    bitindex &= 7;
  }
  return rval;
}

unsigned int mp3_get1bit(void)
{
  unsigned char rval;
  rval = *wordpointer << bitindex;

  bitindex++;
  wordpointer += (bitindex>>3);
  bitindex &= 7;

  return rval>>7;
}



