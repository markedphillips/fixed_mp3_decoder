/* 
 * Mpeg Layer-3 audio decoder 
 * --------------------------
 * All rights reserved. See also 'README'
 */ 
//.. (c) 1998-2018 Mark Phillips Copyright 

#include <stdlib.h>
#include "hipp_dsp.h"
#include "mp3.h"
#include "mp3lib.h"
#include "mp3huff.h"

#include "mp3l3init.h"

#include "debug.h"

extern struct mpstr *gmp;

#define MPEG1

#if 0
static Real ispow[8207];
static Real aa_ca[8],aa_cs[8];
static Real COS1[12][6];
static Real win[4][36];
static Real win1[4][36];
static Real gainpow2[256+118+4];
static Real COS9[9];
static Real COS6_1,COS6_2;
static Real tfcos36[9];
static Real tfcos12[3];
int longLimit[9][23];
int shortLimit[9][14];
static int mapbuf0[9][152];
static int mapbuf1[9][156];
static int mapbuf2[9][44];
static Real tan1_1[16],tan2_1[16],tan1_2[16],tan2_2[16];
static Real pow1_1[2][16],pow2_1[2][16],pow1_2[2][16],pow2_2[2][16];
static unsigned int n_slen2[512]; /* MPEG 2.0 slen for 'normal' mode */
static unsigned int i_slen2[256]; /* MPEG 2.0 slen for intensity stereo */
#endif

struct bandInfoStruct {
  short longIdx[23];
  short longDiff[22];
  short shortIdx[14];
  short shortDiff[13];
};

struct bandInfoStruct bandInfo[9] = { 

/* MPEG 1.0 */
 { {0,4,8,12,16,20,24,30,36,44,52,62,74, 90,110,134,162,196,238,288,342,418,576},
   {4,4,4,4,4,4,6,6,8, 8,10,12,16,20,24,28,34,42,50,54, 76,158},
   {0,4*3,8*3,12*3,16*3,22*3,30*3,40*3,52*3,66*3, 84*3,106*3,136*3,192*3},
   {4,4,4,4,6,8,10,12,14,18,22,30,56} } ,

 { {0,4,8,12,16,20,24,30,36,42,50,60,72, 88,106,128,156,190,230,276,330,384,576},
   {4,4,4,4,4,4,6,6,6, 8,10,12,16,18,22,28,34,40,46,54, 54,192},
   {0,4*3,8*3,12*3,16*3,22*3,28*3,38*3,50*3,64*3, 80*3,100*3,126*3,192*3},
   {4,4,4,4,6,6,10,12,14,16,20,26,66} } ,

 { {0,4,8,12,16,20,24,30,36,44,54,66,82,102,126,156,194,240,296,364,448,550,576} ,
   {4,4,4,4,4,4,6,6,8,10,12,16,20,24,30,38,46,56,68,84,102, 26} ,
   {0,4*3,8*3,12*3,16*3,22*3,30*3,42*3,58*3,78*3,104*3,138*3,180*3,192*3} ,
   {4,4,4,4,6,8,12,16,20,26,34,42,12} }  ,

/* MPEG 2.0 */
 { {0,6,12,18,24,30,36,44,54,66,80,96,116,140,168,200,238,284,336,396,464,522,576},
   {6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54 } ,
   {0,4*3,8*3,12*3,18*3,24*3,32*3,42*3,56*3,74*3,100*3,132*3,174*3,192*3} ,
   {4,4,4,6,6,8,10,14,18,26,32,42,18 } } ,

 { {0,6,12,18,24,30,36,44,54,66,80,96,114,136,162,194,232,278,330,394,464,540,576},
   {6,6,6,6,6,6,8,10,12,14,16,18,22,26,32,38,46,52,64,70,76,36 } ,
   {0,4*3,8*3,12*3,18*3,26*3,36*3,48*3,62*3,80*3,104*3,136*3,180*3,192*3} ,
   {4,4,4,6,8,10,12,14,18,24,32,44,12 } } ,

 { {0,6,12,18,24,30,36,44,54,66,80,96,116,140,168,200,238,284,336,396,464,522,576},
   {6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54 },
   {0,4*3,8*3,12*3,18*3,26*3,36*3,48*3,62*3,80*3,104*3,134*3,174*3,192*3},
   {4,4,4,6,8,10,12,14,18,24,30,40,18 } } ,
/* MPEG 2.5 */
 { {0,6,12,18,24,30,36,44,54,66,80,96,116,140,168,200,238,284,336,396,464,522,576} ,
   {6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54},
   {0,12,24,36,54,78,108,144,186,240,312,402,522,576},
   {4,4,4,6,8,10,12,14,18,24,30,40,18} },
 { {0,6,12,18,24,30,36,44,54,66,80,96,116,140,168,200,238,284,336,396,464,522,576} ,
   {6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54},
   {0,12,24,36,54,78,108,144,186,240,312,402,522,576},
   {4,4,4,6,8,10,12,14,18,24,30,40,18} },
 { {0,12,24,36,48,60,72,88,108,132,160,192,232,280,336,400,476,566,568,570,572,574,576},
   {12,12,12,12,12,12,16,20,24,28,32,40,48,56,64,76,90,2,2,2,2,2},
   {0, 24, 48, 72,108,156,216,288,372,480,486,492,498,576},
   {8,8,8,12,16,20,24,28,36,2,2,2,26} } ,
};

extern unsigned char *wordpointer;
extern int bitindex;

#if 1
#define mp3_GET1BIT() ( bitindex < 7 ? \
  (((*wordpointer << bitindex++) & 0xFF) >> 7) : \
                       ( bitindex = 0, (*wordpointer++) & 0x01 ))
#else
#define mp3_GET1BIT() mp3_get1bit()
#endif

#if 1
__inline__
static
unsigned int getbits_fast (int n)
{
  int k = 8 - n;

  if (bitindex < k)
    {
      unsigned char tmp = (*wordpointer << bitindex);
      bitindex += n;
      return (unsigned long)(tmp >> k);
    }
  return mp3_getbits_fast(n);
}
#else
#define getbits_fast(n) mp3_getbits_fast(n)
#endif

static int *map[9][3];
static int *mapend[9][3];


/* 
 * init tables for layer-3 
 */
void init_layer3(int down_sample_sblimit)
{
  int i,j;

  for(j=0;j<9;j++)
  {
   struct bandInfoStruct *bi = &bandInfo[j];
   int *mp;
   int cb,lwin;
   short *bdf;

   mp = map[j][0] = mapbuf0[j];
   bdf = bi->longDiff;
   for(i=0,cb = 0; cb < 8 ; cb++,i+=*bdf++) {
     *mp++ = (*bdf) >> 1;
     *mp++ = i;
     *mp++ = 3;
     *mp++ = cb;
   }
   bdf = bi->shortDiff+3;
   for(cb=3;cb<13;cb++) {
     int l = (*bdf++) >> 1;
     for(lwin=0;lwin<3;lwin++) {
       *mp++ = l;
       *mp++ = i + lwin;
       *mp++ = lwin;
       *mp++ = cb;
     }
     i += 6*l;
   }
   mapend[j][0] = mp;

   mp = map[j][1] = mapbuf1[j];
   bdf = bi->shortDiff+0;
   for(i=0,cb=0;cb<13;cb++) {
     int l = (*bdf++) >> 1;
     for(lwin=0;lwin<3;lwin++) {
       *mp++ = l;
       *mp++ = i + lwin;
       *mp++ = lwin;
       *mp++ = cb;
     }
     i += 6*l;
   }
   mapend[j][1] = mp;

   mp = map[j][2] = mapbuf2[j];
   bdf = bi->longDiff;
   for(cb = 0; cb < 22 ; cb++) {
     *mp++ = (*bdf++) >> 1;
     *mp++ = cb;
   }
   mapend[j][2] = mp;

  }
}

/*
 * read additional side information
 */
#ifdef MPEG1 
static void III_get_side_info_1(struct III_sideinfo *si,int stereo,
 int ms_stereo,long sfreq,int single)
{
   int ch, gr;
   int powdiff = (single == 3) ? 4 : 0;

   si->main_data_begin = mp3_getbits(9);
   if (stereo == 1)
     si->private_bits = getbits_fast(5);
   else 
     si->private_bits = getbits_fast(3);

   for (ch=0; ch<stereo; ch++) {
       si->ch[ch].gr[0].scfsi = -1;
       si->ch[ch].gr[1].scfsi = getbits_fast(4);
   }

   for (gr=0; gr<2; gr++) 
   {
     for (ch=0; ch<stereo; ch++) 
     {
       register gr_info_s *gr_info = &(si->ch[ch].gr[gr]);

       gr_info->part2_3_length = mp3_getbits(12);
       gr_info->big_values = mp3_getbits_fast(9);
       if(gr_info->big_values > 288) {
          DEBUG("big_values too large!\n");
          gr_info->big_values = 288;
       }
       gr_info->pow2gain = gainpow2+256 - mp3_getbits_fast(8) + powdiff;
       if(ms_stereo)
         gr_info->pow2gain += 2;
       gr_info->scalefac_compress = getbits_fast(4);
/* window-switching flag == 1 for block_Type != 0 .. and block-type == 0 -> win-sw-flag = 0 */
       if(mp3_GET1BIT()) 
       {
         int i;
         gr_info->block_type = getbits_fast(2);
         gr_info->mixed_block_flag = mp3_GET1BIT();
         gr_info->table_select[0] = getbits_fast(5);
         gr_info->table_select[1] = getbits_fast(5);
         /*
          * table_select[2] not needed, because there is no region2,
          * but to satisfy some verifications tools we set it either.
          */
         gr_info->table_select[2] = 0;
         for(i=0;i<3;i++)
           gr_info->full_gain[i] = gr_info->pow2gain + (getbits_fast(3)<<3);

         if(gr_info->block_type == 0) {
           DEBUG("Blocktype == 0 and window-switching == 1 not allowed.\n");
           mp3_exit(1);
         }
         /* region_count/start parameters are implicit in this case. */       
         gr_info->region1start = 36>>1;
         gr_info->region2start = 576>>1;
       }
       else 
       {
         int i,r0c,r1c;
         for (i=0; i<3; i++)
           gr_info->table_select[i] = getbits_fast(5);
         r0c = getbits_fast(4);
         r1c = getbits_fast(3);
         gr_info->region1start = bandInfo[sfreq].longIdx[r0c+1] >> 1 ;
         gr_info->region2start = bandInfo[sfreq].longIdx[r0c+1+r1c+1] >> 1;
         gr_info->block_type = 0;
         gr_info->mixed_block_flag = 0;
       }
       gr_info->preflag = mp3_GET1BIT();
       gr_info->scalefac_scale = mp3_GET1BIT();
       gr_info->count1table_select = mp3_GET1BIT();
     }
   }
}
#endif

/*
 * Side Info for MPEG 2.0 / LSF
 */
static void III_get_side_info_2(struct III_sideinfo *si,int stereo,
 int ms_stereo,long sfreq,int single)
{
   int ch;
   int powdiff = (single == 3) ? 4 : 0;

   si->main_data_begin = mp3_getbits(8);
   if (stereo == 1)
     si->private_bits = mp3_GET1BIT();
   else 
     si->private_bits = getbits_fast(2);

   for (ch=0; ch<stereo; ch++) 
   {
       register gr_info_s *gr_info = &(si->ch[ch].gr[0]);

       gr_info->part2_3_length = mp3_getbits(12);
       gr_info->big_values = mp3_getbits_fast(9);
       if(gr_info->big_values > 288) {
         DEBUG("big_values too large!\n");
         gr_info->big_values = 288;
       }
       gr_info->pow2gain = gainpow2+256 - mp3_getbits_fast(8) + powdiff;
       if(ms_stereo)
         gr_info->pow2gain += 2;
       gr_info->scalefac_compress = mp3_getbits(9);
/* window-switching flag == 1 for block_Type != 0 .. and block-type == 0 -> win-sw-flag = 0 */
       if(mp3_GET1BIT()) 
       {
         int i;
         gr_info->block_type = getbits_fast(2);
         gr_info->mixed_block_flag = mp3_GET1BIT();
         gr_info->table_select[0] = getbits_fast(5);
         gr_info->table_select[1] = getbits_fast(5);
         /*
          * table_select[2] not needed, because there is no region2,
          * but to satisfy some verifications tools we set it either.
          */
         gr_info->table_select[2] = 0;
         for(i=0;i<3;i++)
           gr_info->full_gain[i] = gr_info->pow2gain + (getbits_fast(3)<<3);

         if(gr_info->block_type == 0) {
           DEBUG("Blocktype == 0 and window-switching == 1 not allowed.\n");
           mp3_exit(1);
         }
         /* region_count/start parameters are implicit in this case. */       
/* check this again! */
         if(gr_info->block_type == 2)
           gr_info->region1start = 36>>1;
         else if(sfreq == 8)
/* check this for 2.5 and sfreq=8 */
           gr_info->region1start = 108>>1;
         else
           gr_info->region1start = 54>>1;
         gr_info->region2start = 576>>1;
       }
       else 
       {
         int i,r0c,r1c;
         for (i=0; i<3; i++)
           gr_info->table_select[i] = getbits_fast(5);
         r0c = getbits_fast(4);
         r1c = getbits_fast(3);
         gr_info->region1start = bandInfo[sfreq].longIdx[r0c+1] >> 1 ;
         gr_info->region2start = bandInfo[sfreq].longIdx[r0c+1+r1c+1] >> 1;
         gr_info->block_type = 0;
         gr_info->mixed_block_flag = 0;
       }
       gr_info->scalefac_scale = mp3_GET1BIT();
       gr_info->count1table_select = mp3_GET1BIT();
   }
}

#define NEW_SCALEFACTORS
//#undef NEW_SCALEFACTORS
/*
 * read scalefactors
 */
#ifdef MPEG1
static int III_get_scale_factors_1(int *scf, gr_info_s *gr_info)
{
   static unsigned char slen[2][16] = {
     {0, 0, 0, 0, 3, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4},
     {0, 1, 2, 3, 0, 1, 2, 3, 1, 2, 3, 1, 2, 3, 2, 3}
   };
   int numbits;
   int num0 = slen[0][gr_info->scalefac_compress];
   int num1 = slen[1][gr_info->scalefac_compress];

    if (gr_info->block_type == 2) 
    {
      int i=18;
      numbits = (num0 + num1) * 18;

      if (gr_info->mixed_block_flag) {
         for (i=8;i;i--)
           *scf++ = getbits_fast(num0);
         i = 9;
         numbits -= num0; /* num0 * 17 + num1 * 18 */
      }

      for (;i;i--)
        *scf++ = getbits_fast(num0);
      for (i = 18; i; i--)
        *scf++ = getbits_fast(num1);
      *scf++ = 0; *scf++ = 0; *scf++ = 0; /* short[13][0..2] = 0 */
    }
    else 
    {
      int i;
      int scfsi = gr_info->scfsi;

      if(scfsi < 0) { /* scfsi < 0 => granule == 0 */
         for(i=11;i;i--)
           *scf++ = getbits_fast(num0);
         for(i=10;i;i--)
           *scf++ = getbits_fast(num1);
         numbits = (num0 + num1) * 10 + num0;
#ifdef NEW_SCALEFACTORS
		 *scf++ = 0;
#endif
      }
      else {
        numbits = 0;
        if(!(scfsi & 0x8)) {
#ifdef NEW_SCALEFACTORS
		  for(i=0;i<6;i++)
#else
          for (i=6;i;i--)
#endif
            *scf++ = getbits_fast(num0);
          numbits += num0 * 6;
        }
        else {
#ifdef NEW_SCALEFACTORS
			scf+=6;
#else
          *scf++ = 0; *scf++ = 0; *scf++ = 0;  /* set to ZERO necessary? */
          *scf++ = 0; *scf++ = 0; *scf++ = 0;
#endif
        }

        if(!(scfsi & 0x4)) {
#ifdef NEW_SCALEFACTORS
		  for(i=0;i<5;i++)
#else
          for (i=5;i;i--)
#endif
            *scf++ = getbits_fast(num0);
          numbits += num0 * 5;
        }
        else {
#ifdef NEW_SCALEFACTORS
			scf+=5;
#else
			*scf++ = 0; *scf++ = 0; *scf++ = 0;  /* set to ZERO necessary? */
            *scf++ = 0; *scf++ = 0;
#endif
        }

        if(!(scfsi & 0x2)) {
#ifdef NEW_SCALEFACTORS
		  for(i=0;i<5;i++)
#else
          for(i=5;i;i--)
#endif
            *scf++ = getbits_fast(num1);
          numbits += num1 * 5;
        }
        else {
#ifdef NEW_SCALEFACTORS
			scf+=5;
#else
			*scf++ = 0; *scf++ = 0; *scf++ = 0;  /* set to ZERO necessary? */
            *scf++ = 0; *scf++ = 0;
#endif
        }

        if(!(scfsi & 0x1)) {
#ifdef NEW_SCALEFACTORS
		  for(i=0;i<5;i++)
#else
          for(i=5;i;i--)
#endif
            *scf++ = getbits_fast(num1);
          numbits += num1 * 5;
        }
        else {
#ifdef NEW_SCALEFACTORS
			scf+=5;
#else
          *scf++ = 0; *scf++ = 0; *scf++ = 0;  /* set to ZERO necessary? */
          *scf++ = 0; *scf++ = 0;
#endif		
        }
#ifdef NEW_SCALEFACTORS
		*scf++ = 0;  /* no l[21] in original sources */	
#endif
      }
#ifndef NEW_SCALEFACTORS
	  *scf++ = 0;  /* no l[21] in original sources */
#endif
    }
    return numbits;
}
#endif

static int III_get_scale_factors_2(int *scf, gr_info_s *gr_info,int i_stereo)
{
  unsigned char *pnt;
  int i,j;
  unsigned int slen;
  int n = 0;
  int numbits = 0;

  static unsigned char stab[3][6][4] = {
   { { 6, 5, 5,5 } , { 6, 5, 7,3 } , { 11,10,0,0} ,
     { 7, 7, 7,0 } , { 6, 6, 6,3 } , {  8, 8,5,0} } ,
   { { 9, 9, 9,9 } , { 9, 9,12,6 } , { 18,18,0,0} ,
     {12,12,12,0 } , {12, 9, 9,6 } , { 15,12,9,0} } ,
   { { 6, 9, 9,9 } , { 6, 9,12,6 } , { 15,18,0,0} ,
     { 6,15,12,0 } , { 6,12, 9,6 } , {  6,18,9,0} } }; 

  if(i_stereo) /* i_stereo AND second channel -> do_layer3() checks this */
    slen = i_slen2[gr_info->scalefac_compress>>1];
  else
    slen = n_slen2[gr_info->scalefac_compress];

  gr_info->preflag = (slen>>15) & 0x1;

  n = 0;  
  if( gr_info->block_type == 2 ) {
    n++;
    if(gr_info->mixed_block_flag)
      n++;
  }

  pnt = stab[n][(slen>>12)&0x7];

  for(i=0;i<4;i++) {
    int num = slen & 0x7;
    slen >>= 3;
    if(num) {
      for(j=0;j<(int)(pnt[i]);j++)
        *scf++ = getbits_fast(num);
      numbits += pnt[i] * num;
    }
    else {
      for(j=0;j<(int)(pnt[i]);j++)
        *scf++ = 0;
    }
  }
  
  n = (n << 1) + 1;
  for(i=0;i<n;i++)
    *scf++ = 0;

  return numbits;
}

static int pretab1[22] = {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,3,3,3,2,0};
static int pretab2[22] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

#include "real.h"

/*
 * don't forget to apply the same changes to III_dequantize_sample_ms() !!! 
 */
static int III_dequantize_sample(Real xr[SBLIMIT][SSLIMIT],int *scf,
   gr_info_s *gr_info,int sfreq,int part2bits)
{
  int shift = 1 + gr_info->scalefac_scale;
  Real *xrpnt = (Real *) xr;
  int l[3],l3;
  int part2remain = gr_info->part2_3_length - part2bits;
  int *me;

  {
    int bv       = gr_info->big_values;
    int region1  = gr_info->region1start;
    int region2  = gr_info->region2start;

    l3 = ((576>>1)-bv)>>1;   
/*
 * we may lose the 'odd' bit here !! 
 * check this later again 
 */
    if(bv <= region1) {
      l[0] = bv; l[1] = 0; l[2] = 0;
    }
    else {
      l[0] = region1;
      if(bv <= region2) {
        l[1] = bv - l[0];  l[2] = 0;
      }
      else {
        l[1] = region2 - l[0]; l[2] = bv - region2;
      }
    }
  }
 
  if(gr_info->block_type == 2) {
    /*
     * decoding with short or mixed mode BandIndex table 
     */
    int i,max[4];
    int step=0,lwin=0,cb=0;
    register Real v = 0;
    register int *m,mc;

    if(gr_info->mixed_block_flag) {
      max[3] = -1;
      max[0] = max[1] = max[2] = 2;
      m = map[sfreq][0];
      me = mapend[sfreq][0];
    }
    else {
      max[0] = max[1] = max[2] = max[3] = -1;
      /* max[3] not Really needed in this case */
      m = map[sfreq][1];
      me = mapend[sfreq][1];
    }

    mc = 0;
    for(i=0;i<2;i++) {
      int lp = l[i];
      struct newhuff *h = ht+gr_info->table_select[i];
      for(;lp;lp--,mc--) {
        register int x,y;
        if( (!mc) ) {
          mc = *m++;
          xrpnt = ((Real *) xr) + (*m++);
          lwin = *m++;
          cb = *m++;
          if(lwin == 3) {
            v = gr_info->pow2gain[(*scf++) << shift];
            step = 1;
          }
          else {
            v = gr_info->full_gain[lwin][(*scf++) << shift];
            step = 3;
          }
        }
        {
          register short *val = h->table;
          while((y=*val++)<0) {
            if (mp3_GET1BIT())
              val -= y;
            part2remain--;
          }
          x = y >> 4;
          y &= 0xf;
        }
        if(x == 15) {
          max[lwin] = cb;
          part2remain -= h->linbits+1;
          x += mp3_getbits(h->linbits);
          if(mp3_GET1BIT())
            *xrpnt = (int)(MULT_REAL2(-ispow[x], v));
          else
            *xrpnt =  (int)(MULT_REAL2(ispow[x], v));
        }
        else if(x) {
          max[lwin] = cb;
          if(mp3_GET1BIT())
            *xrpnt = MULT_REAL2(-ispow[x], v);
          else
            *xrpnt =  MULT_REAL2(ispow[x], v);
          part2remain--;
        }
        else
          *xrpnt = 0;
        xrpnt += step;
        if(y == 15) {
          max[lwin] = cb;
          part2remain -= h->linbits+1;
          y += mp3_getbits(h->linbits);
          if(mp3_GET1BIT())
            *xrpnt = MULT_REAL2(-ispow[y], v);
          else
            *xrpnt =  MULT_REAL2(ispow[y], v);
        }
        else if(y) {
          max[lwin] = cb;
          if(mp3_GET1BIT())
            *xrpnt = MULT_REAL2(-ispow[y], v);
          else
            *xrpnt =  MULT_REAL2(ispow[y], v);
          part2remain--;
        }
        else
          *xrpnt = 0;
        xrpnt += step;
      }
    }
    for(;l3 && (part2remain > 0);l3--) {
      struct newhuff *h = htc+gr_info->count1table_select;
      register short *val = h->table,a;

      while((a=*val++)<0) {
        part2remain--;
        if(part2remain < 0) {
          part2remain++;
          a = 0;
          break;
        }
        if (mp3_GET1BIT())
          val -= a;
      }

      for(i=0;i<4;i++) {
        if(!(i & 1)) {
          if(!mc) {
            mc = *m++;
            xrpnt = ((Real *) xr) + (*m++);
            lwin = *m++;
            cb = *m++;
            if(lwin == 3) {
              v = gr_info->pow2gain[(*scf++) << shift];
              step = 1;
            }
            else {
              v = gr_info->full_gain[lwin][(*scf++) << shift];
              step = 3;
            }
          }
          mc--;
        }
        if( (a & (0x8>>i)) ) {
          max[lwin] = cb;
          part2remain--;
          if(part2remain < 0) {
            part2remain++;
            break;
          }
          if(mp3_GET1BIT()) 
            *xrpnt = -v;
          else
            *xrpnt = v;
        }
        else
          *xrpnt = 0;
        xrpnt += step;
      }
    }
 
    while( m < me ) {
      if(!mc) {
        mc = *m++;
        xrpnt = ((Real *) xr) + *m++;
        if( (*m++) == 3)
          step = 1;
        else
          step = 3;
        m++; /* cb */
      }
      mc--;
      *xrpnt = 0;
      xrpnt += step;
      *xrpnt = 0;
      xrpnt += step;
/* we could add a little opt. here:
 * if we finished a band for window 3 or a long band
 * further bands could copied in a simple loop without a
 * special 'map' decoding
 */
    }

    gr_info->maxband[0] = max[0]+1;
    gr_info->maxband[1] = max[1]+1;
    gr_info->maxband[2] = max[2]+1;
    gr_info->maxbandl = max[3]+1;

    {
      int rmax = max[0] > max[1] ? max[0] : max[1];
      rmax = (rmax > max[2] ? rmax : max[2]) + 1;
      gr_info->maxb = rmax ? shortLimit[sfreq][rmax] : longLimit[sfreq][max[3]+1];
    }

  }
  else {
    /*
     * decoding with 'long' BandIndex table (block_type != 2)
     */
    int *pretab = gr_info->preflag ? pretab1 : pretab2;
    int i,max = -1;
    int cb = 0;
    register int *m = map[sfreq][2];
    register Real v = 0;
    register int mc = 0;

    /*
     * long hash table values
     */
    for(i=0;i<3;i++) {
      int lp = l[i];
      struct newhuff *h = ht+gr_info->table_select[i];

      for(;lp;lp--,mc--) {
        int x,y;

        if(!mc) {
          mc = *m++;
          v = gr_info->pow2gain[((*scf++) + (*pretab++)) << shift];
          cb = *m++;
        }
        {
          register short *val = h->table;
          while((y=*val++)<0) {
            if (mp3_GET1BIT())
              val -= y;
            part2remain--;
          }
          x = y >> 4;
          y &= 0xf;
        }
        if (x == 15) {
          max = cb;
          part2remain -= h->linbits+1;
          x += mp3_getbits(h->linbits);
          if(mp3_GET1BIT())
            *xrpnt++ = MULT_REAL2(-ispow[x], v);
          else
            *xrpnt++ =  MULT_REAL2(ispow[x], v);
        }
        else if(x) {
          max = cb;
          if(mp3_GET1BIT())
            *xrpnt++ = MULT_REAL2(-ispow[x], v);
          else
            *xrpnt++ =  MULT_REAL2(ispow[x], v);
          part2remain--;
        }
        else
          *xrpnt++ = 0;

        if (y == 15) {
          max = cb;
          part2remain -= h->linbits+1;
          y += mp3_getbits(h->linbits);
          if(mp3_GET1BIT())
            *xrpnt++ = MULT_REAL2(-ispow[y], v);
          else
            *xrpnt++ =  MULT_REAL2(ispow[y], v);
        }
        else if(y) {
          max = cb;
          if(mp3_GET1BIT())
            *xrpnt++ = MULT_REAL2(-ispow[y], v);
          else
            *xrpnt++ =  MULT_REAL2(ispow[y], v);
          part2remain--;
        }
        else
          *xrpnt++ = 0;
      }
    }

    /*
     * short (count1table) values
     */
    for(;l3 && (part2remain > 0);l3--) {
      struct newhuff *h = htc+gr_info->count1table_select;
      register short *val = h->table,a;

      while((a=*val++)<0) {
        part2remain--;
        if(part2remain < 0) {
          part2remain++;
          a = 0;
          break;
        }
        if (mp3_GET1BIT())
          val -= a;
      }

      for(i=0;i<4;i++) {
        if(!(i & 1)) {
          if(!mc) {
            mc = *m++;
            cb = *m++;
            v = gr_info->pow2gain[((*scf++) + (*pretab++)) << shift];
          }
          mc--;
        }
        if ( (a & (0x8>>i)) ) {
          max = cb;
          part2remain--;
          if(part2remain < 0) {
            part2remain++;
            break;
          }
          if(mp3_GET1BIT())
            *xrpnt++ = -v;
          else
            *xrpnt++ = v;
        }
        else
          *xrpnt++ = 0;
      }
    }

    /* 
     * zero part
     */
    for(i=(&xr[SBLIMIT][0]-xrpnt)>>1;i;i--) {
      *xrpnt++ = 0;
      *xrpnt++ = 0;
    }

    gr_info->maxbandl = max+1;
    gr_info->maxb = longLimit[sfreq][gr_info->maxbandl];
  }

#if 0
  if (part2remain > 0) {	// -ecm: Different from our Hipp codec
    bitindex += part2remain;
    wordpointer += (bitindex >> 3);
    bitindex &= 0x07;
  }
  else if(part2remain < 0) {
    DEBUG("mpg123: Can't rewind stream by %d bits!\n",-part2remain);
    return 1; /* -> error */
  }
#else
  while( part2remain > 16 ) {
    mp3_getbits(16); /* Dismiss stuffing Bits */
    part2remain -= 16;
  }
  if(part2remain > 0)
    mp3_getbits(part2remain);
  else if(part2remain < 0) {
    DEBUG("mpg123: Can't rewind stream by %d bits!\n",-part2remain);
    return 1; /* -> error */
  }
#endif

  return 0;
}


static int III_dequantize_sample_ms(Real xr[2][SBLIMIT][SSLIMIT],int *scf,
   gr_info_s *gr_info,int sfreq,int part2bits)
{
  int shift = 1 + gr_info->scalefac_scale;
  Real *xrpnt = (Real *) xr[1];
  Real *xr0pnt = (Real *) xr[0];
  int l[3],l3;
  int part2remain = gr_info->part2_3_length - part2bits;
  int *me;

  {
    int bv       = gr_info->big_values;
    int region1  = gr_info->region1start;
    int region2  = gr_info->region2start;

    l3 = ((576>>1)-bv)>>1;   
/*
 * we may lose the 'odd' bit here !! 
 * check this later gain 
 */
    if(bv <= region1) {
      l[0] = bv; l[1] = 0; l[2] = 0;
    }
    else {
      l[0] = region1;
      if(bv <= region2) {
        l[1] = bv - l[0];  l[2] = 0;
      }
      else {
        l[1] = region2 - l[0]; l[2] = bv - region2;
      }
    }
  }
 
  if(gr_info->block_type == 2) {
    int i,max[4];
    int step=0,lwin=0,cb=0;
    register Real v = 0;
    register int *m,mc = 0;

    if(gr_info->mixed_block_flag) {
      max[3] = -1;
      max[0] = max[1] = max[2] = 2;
      m = map[sfreq][0];
      me = mapend[sfreq][0];
    }
    else {
      max[0] = max[1] = max[2] = max[3] = -1;
      /* max[3] not really needed in this case */
      m = map[sfreq][1];
      me = mapend[sfreq][1];
    }

    for(i=0;i<2;i++) {
      int lp = l[i];
      struct newhuff *h = ht+gr_info->table_select[i];
      for(;lp;lp--,mc--) {
        int x,y;

        if(!mc) {
          mc = *m++;
          xrpnt = ((Real *) xr[1]) + *m;
          xr0pnt = ((Real *) xr[0]) + *m++;
          lwin = *m++;
          cb = *m++;
          if(lwin == 3) {
            v = gr_info->pow2gain[(*scf++) << shift];
            step = 1;
          }
          else {
            v = gr_info->full_gain[lwin][(*scf++) << shift];
            step = 3;
          }
        }
        {
          register short *val = h->table;
          while((y=*val++)<0) {
            if (mp3_GET1BIT())
              val -= y;
            part2remain--;
          }
          x = y >> 4;
          y &= 0xf;
        }
        if(x == 15) {
          max[lwin] = cb;
          part2remain -= h->linbits+1;
          x += mp3_getbits(h->linbits);
          if(mp3_GET1BIT()) {
            Real a = MULT_REAL2(ispow[x], v);
            *xrpnt = *xr0pnt + a;
            *xr0pnt -= a;
          }
          else {
            Real a = MULT_REAL2(ispow[x], v);
            *xrpnt = *xr0pnt - a;
            *xr0pnt += a;
          }
        }
        else if(x) {
          max[lwin] = cb;
          if(mp3_GET1BIT()) {
            Real a = MULT_REAL2(ispow[x], v);
            *xrpnt = *xr0pnt + a;
            *xr0pnt -= a;
          }
          else {
            Real a = MULT_REAL2(ispow[x], v);
            *xrpnt = *xr0pnt - a;
            *xr0pnt += a;
          }
          part2remain--;
        }
        else
          *xrpnt = *xr0pnt;
        xrpnt += step;
        xr0pnt += step;

        if(y == 15) {
          max[lwin] = cb;
          part2remain -= h->linbits+1;
          y += mp3_getbits(h->linbits);
          if(mp3_GET1BIT()) {
            Real a = MULT_REAL2(ispow[y], v);
            *xrpnt = *xr0pnt + a;
            *xr0pnt -= a;
          }
          else {
            Real a = MULT_REAL2(ispow[y], v);
            *xrpnt = *xr0pnt - a;
            *xr0pnt += a;
          }
        }
        else if(y) {
          max[lwin] = cb;
          if(mp3_GET1BIT()) {
            Real a = MULT_REAL2(ispow[y], v);
            *xrpnt = *xr0pnt + a;
            *xr0pnt -= a;
          }
          else {
            Real a = MULT_REAL2(ispow[y], v);
            *xrpnt = *xr0pnt - a;
            *xr0pnt += a;
          }
          part2remain--;
        }
        else
          *xrpnt = *xr0pnt;
        xrpnt += step;
        xr0pnt += step;
      }
    }

    for(;l3 && (part2remain > 0);l3--) {
      struct newhuff *h = htc+gr_info->count1table_select;
      register short *val = h->table,a;

      while((a=*val++)<0) {
        part2remain--;
        if(part2remain < 0) {
          part2remain++;
          a = 0;
          break;
        }
        if (mp3_GET1BIT())
          val -= a;
      }

      for(i=0;i<4;i++) {
        if(!(i & 1)) {
          if(!mc) {
            mc = *m++;
            xrpnt = ((Real *) xr[1]) + *m;
            xr0pnt = ((Real *) xr[0]) + *m++;
            lwin = *m++;
            cb = *m++;
            if(lwin == 3) {
              v = gr_info->pow2gain[(*scf++) << shift];
              step = 1;
            }
            else {
              v = gr_info->full_gain[lwin][(*scf++) << shift];
              step = 3;
            }
          }
          mc--;
        }
        if( (a & (0x8>>i)) ) {
          max[lwin] = cb;
          part2remain--;
          if(part2remain < 0) {
            part2remain++;
            break;
          }
          if(mp3_GET1BIT()) {
            *xrpnt = *xr0pnt + v;
            *xr0pnt -= v;
          }
          else {
            *xrpnt = *xr0pnt - v;
            *xr0pnt += v;
          }
        }
        else
          *xrpnt = *xr0pnt;
        xrpnt += step;
        xr0pnt += step;
      }
    }
 
    while( m < me ) {
      if(!mc) {
        mc = *m++;
        xrpnt = ((Real *) xr[1]) + *m;
        xr0pnt = ((Real *) xr[0]) + *m++;
        if(*m++ == 3)
          step = 1;
        else
          step = 3;
        m++; /* cb */
      }
      mc--;
      *xrpnt = *xr0pnt;
      xrpnt += step;
      xr0pnt += step;
      *xrpnt = *xr0pnt;
      xrpnt += step;
      xr0pnt += step;
/* we could add a little opt. here:
 * if we finished a band for window 3 or a long band
 * further bands could copied in a simple loop without a
 * special 'map' decoding
 */
    }

    gr_info->maxband[0] = max[0]+1;
    gr_info->maxband[1] = max[1]+1;
    gr_info->maxband[2] = max[2]+1;
    gr_info->maxbandl = max[3]+1;

    {
      int rmax = max[0] > max[1] ? max[0] : max[1];
      rmax = (rmax > max[2] ? rmax : max[2]) + 1;
      gr_info->maxb = rmax ? shortLimit[sfreq][rmax] : longLimit[sfreq][max[3]+1];
    }
  }
  else {
    int *pretab = gr_info->preflag ? pretab1 : pretab2;
    int i,max = -1;
    int cb = 0;
    register int mc=0,*m = map[sfreq][2];
    register Real v = 0;

    for(i=0;i<3;i++) {
      int lp = l[i];
      struct newhuff *h = ht+gr_info->table_select[i];

      for(;lp;lp--,mc--) {
        int x,y;
        if(!mc) {
          mc = *m++;
          cb = *m++;
          v = gr_info->pow2gain[((*scf++) + (*pretab++)) << shift];
        }
        {
          register short *val = h->table;
          while((y=*val++)<0) {
            if (mp3_GET1BIT())
              val -= y;
            part2remain--;
          }
          x = y >> 4;
          y &= 0xf;
        }
        if (x == 15) {
          max = cb;
          part2remain -= h->linbits+1;
          x += mp3_getbits(h->linbits);
          if(mp3_GET1BIT()) {
            Real a = MULT_REAL2(ispow[x], v);
            *xrpnt++ = *xr0pnt + a;
            *xr0pnt++ -= a;
          }
          else {
            Real a = MULT_REAL2(ispow[x], v);
            *xrpnt++ = *xr0pnt - a;
            *xr0pnt++ += a;
          }
        }
        else if(x) {
          max = cb;
          if(mp3_GET1BIT()) {
            Real a = MULT_REAL2(ispow[x], v);
            *xrpnt++ = *xr0pnt + a;
            *xr0pnt++ -= a;
          }
          else {
            Real a = MULT_REAL2(ispow[x], v);
            *xrpnt++ = *xr0pnt - a;
            *xr0pnt++ += a;
          }
          part2remain--;
        }
        else
          *xrpnt++ = *xr0pnt++;

        if (y == 15) {
          max = cb;
          part2remain -= h->linbits+1;
          y += mp3_getbits(h->linbits);
          if(mp3_GET1BIT()) {
            Real a = MULT_REAL2(ispow[y], v);
            *xrpnt++ = *xr0pnt + a;
            *xr0pnt++ -= a;
          }
          else {
            Real a = MULT_REAL2(ispow[y], v);
            *xrpnt++ = *xr0pnt - a;
            *xr0pnt++ += a;
          }
        }
        else if(y) {
          max = cb;
          if(mp3_GET1BIT()) {
            Real a = MULT_REAL2(ispow[y], v);
            *xrpnt++ = *xr0pnt + a;
            *xr0pnt++ -= a;
          }
          else {
            Real a = MULT_REAL2(ispow[y], v);
            *xrpnt++ = *xr0pnt - a;
            *xr0pnt++ += a;
          }
          part2remain--;
        }
        else
          *xrpnt++ = *xr0pnt++;
      }
    }

    for(;l3 && (part2remain > 0);l3--) {
      struct newhuff *h = htc+gr_info->count1table_select;
      register short *val = h->table,a;

      while((a=*val++)<0) {
        part2remain--;
        if(part2remain < 0) {
          part2remain++;
          a = 0;
          break;
        }
        if (mp3_GET1BIT())
          val -= a;
      }

      for(i=0;i<4;i++) {
        if(!(i & 1)) {
          if(!mc) {
            mc = *m++;
            cb = *m++;
            v = gr_info->pow2gain[((*scf++) + (*pretab++)) << shift];
          }
          mc--;
        }
        if ( (a & (0x8>>i)) ) {
          max = cb;
          part2remain--;
          if(part2remain <= 0) {
            part2remain++;
            break;
          }
          if(mp3_GET1BIT()) {
            *xrpnt++ = *xr0pnt + v;
            *xr0pnt++ -= v;
          }
          else {
            *xrpnt++ = *xr0pnt - v;
            *xr0pnt++ += v;
          }
        }
        else
          *xrpnt++ = *xr0pnt++;
      }
    }
    for(i=(&xr[1][SBLIMIT][0]-xrpnt)>>1;i;i--) {
      *xrpnt++ = *xr0pnt++;
      *xrpnt++ = *xr0pnt++;
    }

    gr_info->maxbandl = max+1;
    gr_info->maxb = longLimit[sfreq][gr_info->maxbandl];
  }

#if 0
  if (part2remain > 0) {	// -ecm: Different from our Hipp codec
    bitindex += part2remain;
    wordpointer += (bitindex >> 3);
    bitindex &= 0x07;
  }
  else if(part2remain < 0) {
    DEBUG("mpg123: Can't rewind stream by %d bits!\n",-part2remain);
    return 1; /* -> error */
  }
#else
  while ( part2remain > 16 ) {
    mp3_getbits(16); /* Dismiss stuffing Bits */
    part2remain -= 16;
  }
  if(part2remain > 0 )
    mp3_getbits(part2remain);
  else if(part2remain < 0) {
    DEBUG("mpg123: Can't rewind stream by %d bits!\n",-part2remain);
    return 1; /* -> error */
  }
#endif
  return 0;
}



/* 
 * III_stereo: calculate Real channel values for Joint-I-Stereo-mode
 */
static void III_i_stereo(Real xr_buf[2][SBLIMIT][SSLIMIT],int *scalefac,
   gr_info_s *gr_info,int sfreq,int ms_stereo,int lsf)
{
      Real (*xr)[SBLIMIT*SSLIMIT] = (Real (*)[SBLIMIT*SSLIMIT] ) xr_buf;
      struct bandInfoStruct *bi = &bandInfo[sfreq];
      Real *tab1,*tab2;

      if(lsf) {
        int p = gr_info->scalefac_compress & 0x1;
	    if(ms_stereo) {
          tab1 = pow1_2[p]; tab2 = pow2_2[p];
        }
        else {
          tab1 = pow1_1[p]; tab2 = pow2_1[p];
        }
      }
      else {
        if(ms_stereo) {
          tab1 = tan1_2; tab2 = tan2_2;
        }
        else {
          tab1 = tan1_1; tab2 = tan2_1;
        }
      }

      if (gr_info->block_type == 2)
      {
         int lwin,do_l = 0;
         if( gr_info->mixed_block_flag )
           do_l = 1;

         for (lwin=0;lwin<3;lwin++) /* process each window */
         {
             /* get first band with zero values */
           int is_p,sb,idx,sfb = gr_info->maxband[lwin];  /* sfb is minimal 3 for mixed mode */
           if(sfb > 3)
             do_l = 0;

           for(;sfb<12;sfb++)
           {
             is_p = scalefac[sfb*3+lwin-gr_info->mixed_block_flag]; /* scale: 0-15 */ 
             if(is_p != 7) {
               Real t1,t2;
               sb = bi->shortDiff[sfb];
               idx = bi->shortIdx[sfb] + lwin;
               t1 = tab1[is_p]; t2 = tab2[is_p];
               for (; sb > 0; sb--,idx+=3)
               {
                 Real v = xr[0][idx];
//                 xr[0][idx] = (v * t1) >> 15;
//                 xr[1][idx] = (v * t2) >> 15;
				 xr[0][idx] = MULT_REAL(v, t1);
                 xr[1][idx] = MULT_REAL(v, t2);
               }
             }
           }

#if 1
/* in the original: copy 10 to 11 , here: copy 11 to 12 
maybe still wrong??? (copy 12 to 13?) */
           is_p = scalefac[11*3+lwin-gr_info->mixed_block_flag]; /* scale: 0-15 */
           sb = bi->shortDiff[12];
           idx = bi->shortIdx[12] + lwin;
#else
           is_p = scalefac[10*3+lwin-gr_info->mixed_block_flag]; /* scale: 0-15 */
           sb = bi->shortDiff[11];
           idx = bi->shortIdx[11] + lwin;
#endif
           if(is_p != 7)
           {
             Real t1,t2;
             t1 = tab1[is_p]; t2 = tab2[is_p];
             for ( ; sb > 0; sb--,idx+=3 )
             {  
               Real v = xr[0][idx];
//               xr[0][idx] = (v * t1) >> 15;
//               xr[1][idx] = (v * t2) >> 15;
               xr[0][idx] = MULT_REAL(v, t1);
               xr[1][idx] = MULT_REAL(v, t2);
             }
           }
         } /* end for(lwin; .. ; . ) */

         if (do_l)
         {
/* also check l-part, if ALL bands in the three windows are 'empty'
 * and mode = mixed_mode 
 */
           int sfb = gr_info->maxbandl;
           int idx = bi->longIdx[sfb];

           for ( ; sfb<8; sfb++ )
           {
             int sb = bi->longDiff[sfb];
             int is_p = scalefac[sfb]; /* scale: 0-15 */
             if(is_p != 7) {
               Real t1,t2;
               t1 = tab1[is_p]; t2 = tab2[is_p];
               for ( ; sb > 0; sb--,idx++)
               {
                 Real v = xr[0][idx];
//                 xr[0][idx] = (v * t1) >> 15;
//                 xr[1][idx] = (v * t2) >> 15;
                 xr[0][idx] = MULT_REAL(v, t1);
                 xr[1][idx] = MULT_REAL(v, t2);
               }
             }
             else 
               idx += sb;
           }
         }     
      } 
      else /* ((gr_info->block_type != 2)) */
      {
        int sfb = gr_info->maxbandl;
        int is_p,idx = bi->longIdx[sfb];
        for ( ; sfb<21; sfb++)
        {
          int sb = bi->longDiff[sfb];
          is_p = scalefac[sfb]; /* scale: 0-15 */
          if(is_p != 7) {
            Real t1,t2;
            t1 = tab1[is_p]; t2 = tab2[is_p];
            for ( ; sb > 0; sb--,idx++)
            {
               Real v = xr[0][idx];
//               xr[0][idx] = (v * t1) >> 15;
//               xr[1][idx] = (v * t2) >> 15;
               xr[0][idx] = MULT_REAL(v, t1);
               xr[1][idx] = MULT_REAL(v, t2);
            }
          }
          else
            idx += sb;
        }

        is_p = scalefac[20]; /* copy l-band 20 to l-band 21 */
        if(is_p != 7)
        {
          int sb;
          Real t1 = tab1[is_p],t2 = tab2[is_p]; 

          for ( sb = bi->longDiff[21]; sb > 0; sb--,idx++ )
          {
            Real v = xr[0][idx];
//            xr[0][idx] = (v * t1) >> 15;
//            xr[1][idx] = (v * t2) >> 15;
            xr[0][idx] = MULT_REAL(v, t1);
            xr[1][idx] = MULT_REAL(v, t2);
          }
        }
      } /* ... */
}

static void III_antialias(Real xr[SBLIMIT][SSLIMIT], gr_info_s *gr_info)
{
   int sblim;

   if(gr_info->block_type == 2)
   {
      if(!gr_info->mixed_block_flag) 
        return;
      sblim = 1; 
   }
   else {
     sblim = gr_info->maxb-1;
   }

   /* 31 alias-reduction operations between each pair of sub-bands */
   /* with 8 butterflies between each pair                         */

   {
     int sb;
     Real *xr1=(Real *) xr[1];

     for(sb=sblim;sb;sb--,xr1+=10)
     {
       int ss;
       Real *cs=aa_cs,*ca=aa_ca;
       Real *xr2 = xr1;

       for(ss=7;ss>=0;ss--)
       {       /* upper and lower butterfly inputs */
         register Real bu = *--xr2,bd = *xr1;
//         *xr2   = ((bu * (*cs)   ) - (bd * (*ca)   )) >> 15;
//         *xr1++ = ((bd * (*cs++) ) + (bu * (*ca++) )) >> 15;
         *xr2   = MULT_REAL(bu, (*cs)) - MULT_REAL(bd, (*ca));
         *xr1++ = MULT_REAL(bd, (*cs++)) + MULT_REAL(bu, (*ca++));
       }
     }
  }
}

/*
 DCT insipired by Jeff Tsay's DCT from the maplay package
 this is an optimized version with manual unroll.

 References:
 [1] S. Winograd: "On Computing the Discrete Fourier Transform",
     Mathematics of Computation, Volume 32, Number 141, January 1978,
     Pages 175-199
*/

static void dct36(Real *inbuf,Real *o1,Real *o2,Real *wintab,Real *tsbuf)
{
  {
    register Real *in = inbuf;

    in[17]+=in[16]; in[16]+=in[15]; in[15]+=in[14];
    in[14]+=in[13]; in[13]+=in[12]; in[12]+=in[11];
    in[11]+=in[10]; in[10]+=in[9];  in[9] +=in[8];
    in[8] +=in[7];  in[7] +=in[6];  in[6] +=in[5];
    in[5] +=in[4];  in[4] +=in[3];  in[3] +=in[2];
    in[2] +=in[1];  in[1] +=in[0];

    in[17]+=in[15]; in[15]+=in[13]; in[13]+=in[11]; in[11]+=in[9];
    in[9] +=in[7];  in[7] +=in[5];  in[5] +=in[3];  in[3] +=in[1];


  {

/*
#define MACRO0(v) { \
    Real tmp; \
    out2[9+(v)] = ((tmp = sum0 + sum1) * w[27+(v)]) >> 15; \
    out2[8-(v)] = (tmp * w[26-(v)]) >> 15;  } \
    sum0 -= sum1; \
    ts[SBLIMIT*(8-(v))] = out1[8-(v)] + ((sum0 * w[8-(v)]) >> 15); \
    ts[SBLIMIT*(9+(v))] = out1[9+(v)] + ((sum0 * w[9+(v)]) >> 15); 
#define MACRO1(v) { \
	Real sum0,sum1; \
    sum0 = tmp1a + tmp2a; \
	sum1 = ((tmp1b + tmp2b) * tfcos36[(v)]) >> 15; \
	MACRO0(v); }
#define MACRO2(v) { \
    Real sum0,sum1; \
    sum0 = tmp2a - tmp1a; \
    sum1 = ((tmp2b - tmp1b) * tfcos36[(v)]) >> 15; \
	MACRO0(v); }
*/

#define MACRO0(v) { \
    Real tmp; \
    out2[9+(v)] = MULT_REAL2((tmp = sum0 + sum1), w[27+(v)]); \
    out2[8-(v)] = MULT_REAL2(tmp, w[26-(v)]);  } \
    sum0 -= sum1; \
    ts[SBLIMIT*(8-(v))] = out1[8-(v)] + MULT_REAL(sum0, w[8-(v)]); \
    ts[SBLIMIT*(9+(v))] = out1[9+(v)] + MULT_REAL(sum0, w[9+(v)]); 
#define MACRO1(v) { \
	Real sum0,sum1; \
    sum0 = tmp1a + tmp2a; \
	sum1 = MULT_REAL2((tmp1b + tmp2b), tfcos36[(v)]); \
	MACRO0(v); }
#define MACRO2(v) { \
    Real sum0,sum1; \
    sum0 = tmp2a - tmp1a; \
    sum1 = MULT_REAL2((tmp2b - tmp1b), tfcos36[(v)]); \
	MACRO0(v); }

    register const Real *c = COS9;
    register Real *out2 = o2;
	register Real *w = wintab;
	register Real *out1 = o1;
	register Real *ts = tsbuf;

    Real ta33,ta66,tb33,tb66;

    ta33 = MULT_REAL2(in[2*3+0], c[3]);
    ta66 = MULT_REAL2(in[2*6+0], c[6]);
    tb33 = MULT_REAL2(in[2*3+1], c[3]);
    tb66 = MULT_REAL2(in[2*6+1], c[6]);

    { 
      Real tmp1a,tmp2a,tmp1b,tmp2b;
/*
      tmp1a =             ((in[2*1+0] * c[1]) >> 15) + ta33 + ((in[2*5+0] * c[5]) >> 15) + ((in[2*7+0] * c[7]) >> 15);
      tmp1b =             ((in[2*1+1] * c[1]) >> 15) + tb33 + ((in[2*5+1] * c[5]) >> 15) + ((in[2*7+1] * c[7]) >> 15);
      tmp2a = in[2*0+0] + ((in[2*2+0] * c[2]) >> 15) + ((in[2*4+0] * c[4]) >> 15) + ta66 + ((in[2*8+0] * c[8]) >> 15);
      tmp2b = in[2*0+1] + ((in[2*2+1] * c[2]) >> 15) + ((in[2*4+1] * c[4]) >> 15) + tb66 + ((in[2*8+1] * c[8]) >> 15);
*/
      tmp1a =             MULT_REAL2(in[2*1+0], c[1]) + ta33 + MULT_REAL2(in[2*5+0], c[5]) + MULT_REAL2(in[2*7+0], c[7]);
      tmp1b =             MULT_REAL2(in[2*1+1], c[1]) + tb33 + MULT_REAL2(in[2*5+1], c[5]) + MULT_REAL2(in[2*7+1], c[7]);
      tmp2a = in[2*0+0] + MULT_REAL2(in[2*2+0], c[2]) + MULT_REAL2(in[2*4+0], c[4]) + ta66 + MULT_REAL2(in[2*8+0], c[8]);
      tmp2b = in[2*0+1] + MULT_REAL2(in[2*2+1], c[2]) + MULT_REAL2(in[2*4+1], c[4]) + tb66 + MULT_REAL2(in[2*8+1], c[8]);

      MACRO1(0);
      MACRO2(8);
    }

    {
      Real tmp1a,tmp2a,tmp1b,tmp2b;
/*
      tmp1a = (( in[2*1+0] - in[2*5+0] - in[2*7+0] ) * c[3]) >> 15;
      tmp1b = (( in[2*1+1] - in[2*5+1] - in[2*7+1] ) * c[3]) >> 15;
      tmp2a = ((( in[2*2+0] - in[2*4+0] - in[2*8+0] ) * c[6]) >> 15) - in[2*6+0] + in[2*0+0];
      tmp2b = ((( in[2*2+1] - in[2*4+1] - in[2*8+1] ) * c[6]) >> 15) - in[2*6+1] + in[2*0+1];
*/
      tmp1a = MULT_REAL2(( in[2*1+0] - in[2*5+0] - in[2*7+0] ), c[3]);
      tmp1b = MULT_REAL2(( in[2*1+1] - in[2*5+1] - in[2*7+1] ), c[3]);
      tmp2a = MULT_REAL2(( in[2*2+0] - in[2*4+0] - in[2*8+0] ), c[6]) - in[2*6+0] + in[2*0+0];
      tmp2b = MULT_REAL2(( in[2*2+1] - in[2*4+1] - in[2*8+1] ), c[6]) - in[2*6+1] + in[2*0+1];

      MACRO1(1);
      MACRO2(7);
    }

    {
      Real tmp1a,tmp2a,tmp1b,tmp2b;
/*
      tmp1a =             ((in[2*1+0] * c[5]) >> 15) - ta33 - ((in[2*5+0] * c[7]) >> 15) + ((in[2*7+0] * c[1]) >> 15);
      tmp1b =             ((in[2*1+1] * c[5]) >> 15) - tb33 - ((in[2*5+1] * c[7]) >> 15) + ((in[2*7+1] * c[1]) >> 15);
      tmp2a = in[2*0+0] - ((in[2*2+0] * c[8]) >> 15) - ((in[2*4+0] * c[2]) >> 15) + ta66 + ((in[2*8+0] * c[4]) >> 15);
      tmp2b = in[2*0+1] - ((in[2*2+1] * c[8]) >> 15) - ((in[2*4+1] * c[2]) >> 15) + tb66 + ((in[2*8+1] * c[4]) >> 15);
*/
      tmp1a =             MULT_REAL2(in[2*1+0], c[5]) - ta33 - MULT_REAL2(in[2*5+0], c[7]) + MULT_REAL2(in[2*7+0], c[1]);
      tmp1b =             MULT_REAL2(in[2*1+1], c[5]) - tb33 - MULT_REAL2(in[2*5+1], c[7]) + MULT_REAL2(in[2*7+1], c[1]);
      tmp2a = in[2*0+0] - MULT_REAL2(in[2*2+0], c[8]) - MULT_REAL2(in[2*4+0], c[2]) + ta66 + MULT_REAL2(in[2*8+0], c[4]);
      tmp2b = in[2*0+1] - MULT_REAL2(in[2*2+1], c[8]) - MULT_REAL2(in[2*4+1], c[2]) + tb66 + MULT_REAL2(in[2*8+1], c[4]);

      MACRO1(2);
      MACRO2(6);
    }

    {
      Real tmp1a,tmp2a,tmp1b,tmp2b;
/*
      tmp1a =             ((in[2*1+0] * c[7]) >> 15) - ta33 + ((in[2*5+0] * c[1]) >> 15) - ((in[2*7+0] * c[5]) >> 15);
      tmp1b =             ((in[2*1+1] * c[7]) >> 15) - tb33 + ((in[2*5+1] * c[1]) >> 15) - ((in[2*7+1] * c[5]) >> 15);
      tmp2a = in[2*0+0] - ((in[2*2+0] * c[4]) >> 15) + ((in[2*4+0] * c[8]) >> 15) + ta66 - ((in[2*8+0] * c[2]) >> 15);
      tmp2b = in[2*0+1] - ((in[2*2+1] * c[4]) >> 15) + ((in[2*4+1] * c[8]) >> 15) + tb66 - ((in[2*8+1] * c[2]) >> 15);
*/
      tmp1a =             MULT_REAL2(in[2*1+0], c[7]) - ta33 + MULT_REAL2(in[2*5+0], c[1]) - MULT_REAL2(in[2*7+0], c[5]);
      tmp1b =             MULT_REAL2(in[2*1+1], c[7]) - tb33 + MULT_REAL2(in[2*5+1], c[1]) - MULT_REAL2(in[2*7+1], c[5]);
      tmp2a = in[2*0+0] - MULT_REAL2(in[2*2+0], c[4]) + MULT_REAL2(in[2*4+0], c[8]) + ta66 - MULT_REAL2(in[2*8+0], c[2]);
      tmp2b = in[2*0+1] - MULT_REAL2(in[2*2+1], c[4]) + MULT_REAL2(in[2*4+1], c[8]) + tb66 - MULT_REAL2(in[2*8+1], c[2]);

      MACRO1(3);
      MACRO2(5);
    }

	{
		Real sum0,sum1;
    	sum0 =  in[2*0+0] - in[2*2+0] + in[2*4+0] - in[2*6+0] + in[2*8+0];
//    	sum1 = ((in[2*0+1] - in[2*2+1] + in[2*4+1] - in[2*6+1] + in[2*8+1] ) * tfcos36[4]) >> 15;
    	sum1 = MULT_REAL2((in[2*0+1] - in[2*2+1] + in[2*4+1] - in[2*6+1] + in[2*8+1] ), tfcos36[4]);
		MACRO0(4);
	}
  }

  }
}

/*
 * new DCT12
 */
static void dct12(Real *in,Real *rawout1,Real *rawout2,register Real *wi,register Real *ts)
{
/*
#define DCT12_PART1 \
             in5 = in[5*3];  \
     in5 += (in4 = in[4*3]); \
     in4 += (in3 = in[3*3]); \
     in3 += (in2 = in[2*3]); \
     in2 += (in1 = in[1*3]); \
     in1 += (in0 = in[0*3]); \
                             \
     in5 += in3; in3 += in1; \
                             \
     MULTEQ_REAL(in2, COS6_1); \
     MULTEQ_REAL(in3, COS6_1); \
*/
#define DCT12_PART1 \
             in5 = in[5*3];  \
     in5 += (in4 = in[4*3]); \
     in4 += (in3 = in[3*3]); \
     in3 += (in2 = in[2*3]); \
     in2 += (in1 = in[1*3]); \
     in1 += (in0 = in[0*3]); \
                             \
     in5 += in3; in3 += in1; \
                             \
     in2 = MULT_REAL2(in2, COS6_1); \
     in3 = MULT_REAL2(in3, COS6_1); \

#define DCT12_PART2 \
     in0 += MULT_REAL2(in4, COS6_2); \
                          \
     in4 = in0 + in2;     \
     in0 -= in2;          \
                          \
     in1 += MULT_REAL2(in5, COS6_2); \
                          \
     in5 = MULT_REAL2((in1 + in3), tfcos12[0]); \
     in1 = MULT_REAL2((in1 - in3), tfcos12[2]); \
                         \
     in3 = in4 + in5;    \
     in4 -= in5;         \
                         \
     in2 = in0 + in1;    \
     in0 -= in1;


   {
     Real in0,in1,in2,in3,in4,in5;
     register Real *out1 = rawout1;
     ts[SBLIMIT*0] = out1[0]; ts[SBLIMIT*1] = out1[1]; ts[SBLIMIT*2] = out1[2];
     ts[SBLIMIT*3] = out1[3]; ts[SBLIMIT*4] = out1[4]; ts[SBLIMIT*5] = out1[5];
 
     DCT12_PART1

     {
       Real tmp0,tmp1 = (in0 - in4);
       {
//         Real tmp2 = ((in1 - in5) * tfcos12[1]) >> 15;
         Real tmp2 = MULT_REAL2((in1 - in5), tfcos12[1]);
         tmp0 = tmp1 + tmp2;
         tmp1 -= tmp2;
       }
/*
       ts[(17-1)*SBLIMIT] = out1[17-1] + ((tmp0 * wi[11-1]) >> 15);
       ts[(12+1)*SBLIMIT] = out1[12+1] + ((tmp0 * wi[6+1]) >> 15);
       ts[(6 +1)*SBLIMIT] = out1[6 +1] + ((tmp1 * wi[1]) >> 15);
       ts[(11-1)*SBLIMIT] = out1[11-1] + ((tmp1 * wi[5-1]) >> 15);
*/
       ts[(17-1)*SBLIMIT] = out1[17-1] + MULT_REAL2(tmp0, wi[11-1]);
       ts[(12+1)*SBLIMIT] = out1[12+1] + MULT_REAL2(tmp0, wi[6+1]);
       ts[(6 +1)*SBLIMIT] = out1[6 +1] + MULT_REAL2(tmp1, wi[1]);
       ts[(11-1)*SBLIMIT] = out1[11-1] + MULT_REAL2(tmp1, wi[5-1]);
     }

     DCT12_PART2

/*
     ts[(17-0)*SBLIMIT] = out1[17-0] + ((in2 * wi[11-0]) >> 15);
     ts[(12+0)*SBLIMIT] = out1[12+0] + ((in2 * wi[6+0]) >> 15);
     ts[(12+2)*SBLIMIT] = out1[12+2] + ((in3 * wi[6+2]) >> 15);
     ts[(17-2)*SBLIMIT] = out1[17-2] + ((in3 * wi[11-2]) >> 15);

     ts[(6+0)*SBLIMIT]  = out1[6+0] + ((in0 * wi[0]) >> 15);
     ts[(11-0)*SBLIMIT] = out1[11-0] + ((in0 * wi[5-0]) >> 15);
     ts[(6+2)*SBLIMIT]  = out1[6+2] + ((in4 * wi[2]) >> 15);
     ts[(11-2)*SBLIMIT] = out1[11-2] + ((in4 * wi[5-2]) >> 15);
*/
     ts[(17-0)*SBLIMIT] = out1[17-0] + MULT_REAL2(in2, wi[11-0]);
     ts[(12+0)*SBLIMIT] = out1[12+0] + MULT_REAL2(in2, wi[6+0]);
     ts[(12+2)*SBLIMIT] = out1[12+2] + MULT_REAL2(in3, wi[6+2]);
     ts[(17-2)*SBLIMIT] = out1[17-2] + MULT_REAL2(in3, wi[11-2]);

     ts[(6+0)*SBLIMIT]  = out1[6+0] + MULT_REAL2(in0, wi[0]);
     ts[(11-0)*SBLIMIT] = out1[11-0] + MULT_REAL2(in0, wi[5-0]);
     ts[(6+2)*SBLIMIT]  = out1[6+2] + MULT_REAL2(in4, wi[2]);
     ts[(11-2)*SBLIMIT] = out1[11-2] + MULT_REAL2(in4, wi[5-2]);

  }

  in++;

  {
     Real in0,in1,in2,in3,in4,in5;
     register Real *out2 = rawout2;
 
     DCT12_PART1

     {
       Real tmp0,tmp1 = (in0 - in4);
       {
//         Real tmp2 = ((in1 - in5) * tfcos12[1]) >> 15;
         Real tmp2 = MULT_REAL2((in1 - in5), tfcos12[1]);
         tmp0 = tmp1 + tmp2;
         tmp1 -= tmp2;
       }
/*
       out2[5-1] = (tmp0 * wi[11-1]) >> 15;
       out2[0+1] = (tmp0 * wi[6+1] ) >> 15;
       ts[(12+1)*SBLIMIT] += (tmp1 * wi[1]) >> 15;
       ts[(17-1)*SBLIMIT] += (tmp1 * wi[5-1]) >> 15;
*/
       out2[5-1] = MULT_REAL2(tmp0, wi[11-1]);
       out2[0+1] = MULT_REAL2(tmp0, wi[6+1]);
       ts[(12+1)*SBLIMIT] += MULT_REAL2(tmp1, wi[1]);
       ts[(17-1)*SBLIMIT] += MULT_REAL2(tmp1, wi[5-1]);
     }

     DCT12_PART2

/*
     out2[5-0] = (in2 * wi[11-0]) >> 15;
     out2[0+0] = (in2 * wi[6+0]) >> 15;
     out2[0+2] = (in3 * wi[6+2]) >> 15;
     out2[5-2] = (in3 * wi[11-2]) >> 15;

     ts[(12+0)*SBLIMIT] += (in0 * wi[0]) >> 15;
     ts[(17-0)*SBLIMIT] += (in0 * wi[5-0]) >> 15;
     ts[(12+2)*SBLIMIT] += (in4 * wi[2]) >> 15;
     ts[(17-2)*SBLIMIT] += (in4 * wi[5-2]) >> 15;
*/
     out2[5-0] = MULT_REAL2(in2, wi[11-0]);
     out2[0+0] = MULT_REAL2(in2, wi[6+0]);
     out2[0+2] = MULT_REAL2(in3, wi[6+2]);
     out2[5-2] = MULT_REAL2(in3, wi[11-2]);

     ts[(12+0)*SBLIMIT] += MULT_REAL2(in0, wi[0]);
     ts[(17-0)*SBLIMIT] += MULT_REAL2(in0, wi[5-0]);
     ts[(12+2)*SBLIMIT] += MULT_REAL2(in4, wi[2]);
     ts[(17-2)*SBLIMIT] += MULT_REAL2(in4, wi[5-2]);
  }

  in++; 

  {
     Real in0,in1,in2,in3,in4,in5;
     register Real *out2 = rawout2;
     out2[12]=out2[13]=out2[14]=out2[15]=out2[16]=out2[17]=0;

     DCT12_PART1

     {
       Real tmp0,tmp1 = (in0 - in4);
       {
//         Real tmp2 = ((in1 - in5) * tfcos12[1]) >> 15;
         Real tmp2 = MULT_REAL2((in1 - in5), tfcos12[1]);
         tmp0 = tmp1 + tmp2;
         tmp1 -= tmp2;
       }
/*
       out2[11-1] = (tmp0 * wi[11-1]) >> 15;
       out2[6 +1] = (tmp0 * wi[6+1]) >> 15;
       out2[0+1] += (tmp1 * wi[1]) >> 15;
       out2[5-1] += (tmp1 * wi[5-1]) >> 15;
*/
       out2[11-1] = MULT_REAL2(tmp0, wi[11-1]);
       out2[6 +1] = MULT_REAL2(tmp0, wi[6+1]);
       out2[0+1] += MULT_REAL2(tmp1, wi[1]);
       out2[5-1] += MULT_REAL2(tmp1, wi[5-1]);
     }

     DCT12_PART2

/*
     out2[11-0] = (in2 * wi[11-0]) >> 15;
     out2[6 +0] = (in2 * wi[6+0]) >> 15;
     out2[6 +2] = (in3 * wi[6+2]) >> 15;
     out2[11-2] = (in3 * wi[11-2]) >> 15;

     out2[0+0] += (in0 * wi[0]) >> 15;
     out2[5-0] += (in0 * wi[5-0]) >> 15;
     out2[0+2] += (in4 * wi[2]) >> 15;
     out2[5-2] += (in4 * wi[5-2]) >> 15;
*/
     out2[11-0] = MULT_REAL2(in2, wi[11-0]);
     out2[6 +0] = MULT_REAL2(in2, wi[6+0]);
     out2[6 +2] = MULT_REAL2(in3, wi[6+2]);
     out2[11-2] = MULT_REAL2(in3, wi[11-2]);

     out2[0+0] += MULT_REAL2(in0, wi[0]);
     out2[5-0] += MULT_REAL2(in0, wi[5-0]);
     out2[0+2] += MULT_REAL2(in4, wi[2]);
     out2[5-2] += MULT_REAL2(in4, wi[5-2]);
  }
}

/*
 * III_hybrid
 */
static void III_hybrid(Real fsIn[SBLIMIT][SSLIMIT],Real tsOut[SSLIMIT][SBLIMIT],
   int ch, gr_info_s *gr_info)
{
   Real *tspnt = (Real *) tsOut;
   Real (*block)[2][SBLIMIT*SSLIMIT] = gmp->hybrid_block;
   int *blc = gmp->hybrid_blc;
   Real *rawout1,*rawout2;
   int bt;
   int sb = 0;

   {
     int b = blc[ch];
     rawout1=block[b][ch];
     b=-b+1;
     rawout2=block[b][ch];
     blc[ch] = b;
   }

  
   if(gr_info->mixed_block_flag) {
     sb = 2;
     dct36(fsIn[0],rawout1,rawout2,win[0],tspnt);
     dct36(fsIn[1],rawout1+18,rawout2+18,win1[0],tspnt+1);
     rawout1 += 36; rawout2 += 36; tspnt += 2;
   }
 
   bt = gr_info->block_type;
   if(bt == 2) {
     for (; sb<gr_info->maxb; sb+=2,tspnt+=2,rawout1+=36,rawout2+=36) {
       dct12(fsIn[sb],rawout1,rawout2,win[2],tspnt);
       dct12(fsIn[sb+1],rawout1+18,rawout2+18,win1[2],tspnt+1);
     }
   }
   else {
     for (; sb<gr_info->maxb; sb+=2,tspnt+=2,rawout1+=36,rawout2+=36) {
       dct36(fsIn[sb],rawout1,rawout2,win[bt],tspnt);
       dct36(fsIn[sb+1],rawout1+18,rawout2+18,win1[bt],tspnt+1);
     }
   }

   for(;sb<SBLIMIT;sb++,tspnt++) {
     int i;
     for(i=0;i<SSLIMIT;i++) {
       tspnt[i*SBLIMIT] = *rawout1++;
       *rawout2++ = 0;
     }
   }
}

#ifdef HIPP_EQ

extern void calculate_eq_presets(float preamp, float *b, float *out);
extern void calculate_sonique_eq_presets(float preamp, float *b, float *out);

static Real s_presetValues[576];
static bool s_bEQOn = false;

int
change_equalizer_setting(bool bEQOn, float fPreamp, float* fBands, int nBands)
{
	float b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Real out[576];

	if (bEQOn)
	{
		// At the moment, only 10-band Winamp equalizer settings are supported.
		if (nBands != 10)
			return 0;

		DEBUG("1\n");
		if (nBands == 10)
			calculate_eq_presets(fPreamp, fBands, out);
		else if (nBands == 20)
			calculate_sonique_eq_presets(fPreamp, fBands, out);
		else
			return 0;
		DEBUG("2\n");
		memcpy(s_presetValues, out, 576 * sizeof(Real));
		DEBUG("3\n");
	}

	s_bEQOn = bEQOn;

	return 1;
}
#endif	// HIPP_EQ

/*
 * main layer3 handler
 */
#define SCALEFACTOR_PER_CHANNEL
//#undef SCALEFACTOR_PER_CHANNEL

#define USE_DEQUANTIZE_MS

int do_layer3(struct mp3frame *fr,unsigned char *pcm_sample_left, unsigned char * pcm_sample_right, int *pcm_point)
{
  int gr, ch, ss,clip=0;
#ifdef SCALEFACTOR_PER_CHANNEL
  static int scalefacs[2][39]; /* max 39 for short[13][3] mode, mixed: 38, long: 22 */ 
#else
  int scalefacs[39]; /* max 39 for short[13][3] mode, mixed: 38, long: 22 */
#endif
  struct III_sideinfo sideinfo;
  int stereo = fr->stereo;
  int single = fr->single;
  int ms_stereo,i_stereo;
  int sfreq = fr->sampling_frequency;
  int stereo1,granules;
  // Real *p0, *p1;

  if(stereo == 1) { /* stream is mono */
    stereo1 = 1;
    single = 0;
  }
  else if(single >= 0) /* stream is stereo, but force to mono */
    stereo1 = 1;
  else
    stereo1 = 2;

  if(fr->mode == MPG_MD_JOINT_STEREO) {
    ms_stereo = fr->mode_ext & 0x2;
    i_stereo  = fr->mode_ext & 0x1;
  }
  else
    ms_stereo = i_stereo = 0;

  if(fr->lsf) {
    granules = 1;
    III_get_side_info_2(&sideinfo,stereo,ms_stereo,sfreq,single);
  }
  else {
    granules = 2;
#ifdef MPEG1
    III_get_side_info_1(&sideinfo,stereo,ms_stereo,sfreq,single);
#else
    DEBUG("Not supported\n");
#endif
  }

  if(set_pointer(sideinfo.main_data_begin) == MP3_ERR)
    return 0;

  for (gr=0;gr<granules;gr++) 
  {
    static Real hybridIn[2][SBLIMIT][SSLIMIT];
    static Real hybridOut[2][SSLIMIT][SBLIMIT];

    {
      gr_info_s *gr_info = &(sideinfo.ch[0].gr[gr]);
      long part2bits;
#ifdef SCALEFACTOR_PER_CHANNEL
      if(fr->lsf)
        part2bits = III_get_scale_factors_2(scalefacs[0],gr_info,0);
      else
#ifdef MPEG1
        part2bits = III_get_scale_factors_1(scalefacs[0],gr_info);
#else	// MPEG1
		DEBUG("Not supported\n");
#endif	// MPEG1
      if(III_dequantize_sample(hybridIn[0], scalefacs[0],gr_info,sfreq,part2bits))
        return clip;
#else	// SCALEFACTOR_PER_CHANNEL
      if(fr->lsf)
        part2bits = III_get_scale_factors_2(scalefacs,gr_info,0);
      else
#ifdef MPEG1
        part2bits = III_get_scale_factors_1(scalefacs,gr_info);
#else	// MPEG1
		DEBUG("Not supported\n");
#endif	// MPEG1
      if(III_dequantize_sample(hybridIn[0], scalefacs,gr_info,sfreq,part2bits))
        return clip;
#endif	// SCALEFACTOR_PER_CHANNEL

    }

    if(stereo == 2) {
      gr_info_s *gr_info = &(sideinfo.ch[1].gr[gr]);
      long part2bits;
#ifdef SCALEFACTOR_PER_CHANNEL
      if(fr->lsf) 
        part2bits = III_get_scale_factors_2(scalefacs[1],gr_info,i_stereo);
      else
#ifdef MPEG1
        part2bits = III_get_scale_factors_1(scalefacs[1],gr_info);
#else	// MPEG1
		DEBUG("Not supported\n");
#endif	// MPEG1

#ifndef USE_DEQUANTIZE_MS
      if(III_dequantize_sample(hybridIn[1],scalefacs[1],gr_info,sfreq,part2bits))
          return clip;

      if(ms_stereo) {
        int i;
        Real *ptr0 = (Real *)hybridIn[0];
        Real *ptr1 = (Real *)hybridIn[1];

        for(i=0;i<SBLIMIT*SSLIMIT;i++) {
          Real tmp0,tmp1;
          tmp0 = *ptr0;
          tmp1 = *ptr1;
          *ptr1++ = tmp0 - tmp1;  
          *ptr0++ = tmp0 + tmp1;
        }
      }
#else	// USE_DEQUANTIZE_MS
      if(ms_stereo) {
        if(III_dequantize_sample_ms(hybridIn,scalefacs[1],gr_info,sfreq,part2bits))
          return clip;
      }
      else {
        if(III_dequantize_sample(hybridIn[1],scalefacs[1],gr_info,sfreq,part2bits))
          return clip;
      }
#endif	// USE_DEQUANTIZE_MS

      if(i_stereo)
        III_i_stereo(hybridIn,scalefacs[1],gr_info,sfreq,ms_stereo,fr->lsf);

#else	// SCALEFACTOR_PER_CHANNEL

      if(fr->lsf) 
        part2bits = III_get_scale_factors_2(scalefacs,gr_info,i_stereo);
      else
#ifdef MPEG1
        part2bits = III_get_scale_factors_1(scalefacs,gr_info);
#else	// MPEG1
		DEBUG("Not supported\n");
#endif	// MPEG1

#ifndef USE_DEQUANTIZE_MS
      if(III_dequantize_sample(hybridIn[1],scalefacs,gr_info,sfreq,part2bits))
          return clip;

      if(ms_stereo) {
        int i;
        Real *ptr0 = (Real *)hybridIn[0];
        Real *ptr1 = (Real *)hybridIn[1];

        for(i=0;i<SBLIMIT*SSLIMIT;i++) {
          Real tmp0,tmp1;
          tmp0 = *ptr0;
          tmp1 = *ptr1;
          *ptr1++ = tmp0 - tmp1;  
          *ptr0++ = tmp0 + tmp1;
        }
      }
#else	// USE_DEQUANTIZE_MS
      if(ms_stereo) {
        if(III_dequantize_sample_ms(hybridIn,scalefacs,gr_info,sfreq,part2bits))
          return clip;
      }
      else {
        if(III_dequantize_sample(hybridIn[1],scalefacs,gr_info,sfreq,part2bits))
          return clip;
      }
#endif	// USE_DEQUANTIZE_MS

      if(i_stereo)
        III_i_stereo(hybridIn,scalefacs,gr_info,sfreq,ms_stereo,fr->lsf);

#endif	// SCALEFACTOR_PER_CHANNEL


      if(ms_stereo || i_stereo || (single == 3) ) {
        if(gr_info->maxb > sideinfo.ch[0].gr[gr].maxb) 
          sideinfo.ch[0].gr[gr].maxb = gr_info->maxb;
        else
          gr_info->maxb = sideinfo.ch[0].gr[gr].maxb;
      }

      switch(single) {
        case 3:
          {
            register int i;
            register Real *in0 = (Real *) hybridIn[0],*in1 = (Real *) hybridIn[1];
            for(i=0;i<SSLIMIT*gr_info->maxb;i++,in0++) {
              *in0 = (*in0 + *in1++); /* *0.5 done by pow-scale */ 
            }
          }
          break;
        case 1:
          {
            register int i;
            register Real *in0 = (Real *) hybridIn[0],*in1 = (Real *) hybridIn[1];
            for(i=0;i<SSLIMIT*gr_info->maxb;i++) {
              *in0++ = *in1++;
            }
             
          }
          break;
      }
    }

#ifdef HIPP_EQ
	// Equalization
	if (s_bEQOn)
	{
		int i = 0, sb;
		if (single >= 0)
		{
			for (sb = 0; sb < SBLIMIT; ++sb)
				for (ss = 0; ss < SSLIMIT; ++ss)
					hybridIn[0][sb][ss] = (hybridIn[0][sb][ss] * s_presetValues[i++]) >> 15;
		}
		else
		{
			for (sb = 0; sb < SBLIMIT; ++sb)
				for (ss = 0; ss < SSLIMIT; ++ss)
				{
					hybridIn[0][sb][ss] = (hybridIn[0][sb][ss] * s_presetValues[i]) >> 15;
					hybridIn[1][sb][ss] = (hybridIn[1][sb][ss] * s_presetValues[i++]) >> 15;
				}
		}
	}
#endif	// HIPP_EQ

    for(ch=0;ch<stereo1;ch++) {
      gr_info_s *gr_info = &(sideinfo.ch[ch].gr[gr]);
      III_antialias(hybridIn[ch],gr_info);
      III_hybrid(hybridIn[ch], hybridOut[ch], ch,gr_info);
    }

   for(ss=0;ss<SSLIMIT;ss++) {
      if(single >= 0) {
        clip += synth_1to1_mono(hybridOut[0][ss],pcm_sample_left,pcm_point);
      }
      else {
        int p1 = *pcm_point;
        clip += synth_1to1_single(hybridOut[0][ss],0,pcm_sample_left,&p1);
        clip += synth_1to1_single(hybridOut[1][ss],1,pcm_sample_right, pcm_point);
//        clip += synth_1to1(hybridOut[0][ss],0,pcm_sample_left,&p1);
//        clip += synth_1to1(hybridOut[1][ss],1,pcm_sample_right, pcm_point);
      }
    }

#if 0
    p0 = (Real *)hybridOut[0];
    p1 = (Real *)hybridOut[1];

    for(ss=0;ss<SSLIMIT;ss++) {
      if(single >= 0) {
        clip += synth_1to1_mono(*p0++,pcm_sample_left,pcm_point);
      }
      else {
        int tmp = *pcm_point;
        clip += synth_1to1_single(*p0++,0,pcm_sample_left,&tmp);
        clip += synth_1to1_single(*p1++,1,pcm_sample_right, pcm_point);
      }
    }
#endif

  }
  
  return clip;
}


