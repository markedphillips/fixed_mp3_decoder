//.. (c) 1998-2018 Mark Phillips Copyright 

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "debug.h"

jmp_buf mp3jbuf;

#include "mp3.h"
#include "mp3lib.h"

#define READ_EVERY_HEADER
#define TRY_RESYNCH

/* Global mp .. it's a hack */
struct mpstr *gmp;

int dsp_InitMP3(struct mpstr *mp) 
{
	memset(mp,0,sizeof(struct mpstr));
	
	mp->header = 0;
	mp->framesize = 0;
	mp->fsizeold = -1;
	mp->bsize = 0;
	mp->fr.single = -1;
	mp->bsnum = 0;
	mp->synth_bo = 1;
	mp->iHeaderBytes = 0;
	mp->iValidBytes = 0;
	
	init_layer3(SBLIMIT);
	
	return !0;
}

void dsp_ExitMP3(struct mpstr *mp)
{
	mp->header = 0;
	mp->framesize = 0;
	mp->fsizeold = -1;
	mp->bsize = 0;
	mp->fr.single = -1;
	mp->bsnum = 0;
	mp->synth_bo = 1;
	mp->iValidBytes = 0;
}

static unsigned long read_head(tHippMPEGBitstream *bs)
{
	unsigned long head = ((unsigned long)(bs->bufptr[0]) << 24) |
		((unsigned long)(bs->bufptr[1]) << 16) |
		((unsigned long)(bs->bufptr[2]) << 8) |
		(unsigned long)(bs->bufptr[3]) &
		0xffffffff;

	bs->bytesleft -= 4;
	bs->bufptr += 4;
	return head;
}

static void add_bytes_to_header(tHippMPEGBitstream *bs, unsigned long* header, int iBytesToAdd)
{
	while (iBytesToAdd > 0)
	{
		*header = (((*header) << 8) | bs->bufptr[0]) & 0xffffffff;
		--iBytesToAdd;
		--bs->bytesleft;
		++bs->bufptr;
	}
}


extern int head_check(unsigned long head);

// Given an input buffer, find the first MP3 header.
int
dsp_SynchMP3(tHippMPEGBitstream *bs)
{
	unsigned long ulHeadTest;

	if (bs->bytesleft < 4)
		return MP3_NEED_MORE;

	ulHeadTest = ((unsigned long)(bs->bufptr[0]) << 24) |
		((unsigned long)(bs->bufptr[1]) << 16) |
		((unsigned long)(bs->bufptr[2]) << 8) |
		(unsigned long)(bs->bufptr[3]) &
		0xffffffff;

	if (!head_check(ulHeadTest))
	{
		while (bs->bytesleft > 4)
		{
			++(bs->bufptr);
			--bs->bytesleft;
			ulHeadTest = ((ulHeadTest << 8) | bs->bufptr[3]) & 0xffffffff;
			if (head_check(ulHeadTest))
				return MP3_OK;
		}
	}
	else
		return MP3_OK;

	return MP3_ERR;
}

extern long mp3_freqs[9];
extern int mp3_tabsel_123[2][3][16];

int
dsp_DecodeHeader(struct mpstr *mp, tHippMPEGBitstream *bs,
	unsigned long* ulSamplingFrequency, unsigned long* ulChannels, unsigned long* ulBitRate)
{
	dsp_InitMP3(mp);
	
	/* First decode header */
	if(mp->framesize == 0) {
		if(bs->bytesleft < 4)
			return MP3_NEED_MORE;

		mp->header = read_head(bs);
		if (decode_header(&mp->fr,mp->header) != MP3_OK)
			return MP3_ERR;
		mp->framesize = mp->fr.framesize;
	}

	if (ulSamplingFrequency)
		*ulSamplingFrequency = mp3_freqs[mp->fr.sampling_frequency];
	if (ulChannels)
		*ulChannels = mp->fr.stereo;
	if (ulBitRate)
		*ulBitRate = mp3_tabsel_123[mp->fr.lsf][mp->fr.lay-1][mp->fr.bitrate_index] * 1000;
	dsp_ExitMP3(mp);

	return MP3_OK;
}

int dsp_DecodeMP3(struct mpstr *mp, tHippMPEGBitstream *bs,
	unsigned char *out_left, unsigned char *out_right, int osize, int *iBytesWritten)
{
	int k;
	int iBytesToRead;
#ifndef READ_EVERY_HEADER
	bool bDecodeHeader = (mp->header == 0);
#endif	// READ_EVERY_HEADER
	
	*iBytesWritten = 0;

	gmp = mp;

//	if(osize < 4608) {
	if(osize < 2304) {
//		DEBUG("MP3 output buffer is full\n");
		return MP3_BUFFER_FULL;
	}
		
	if(mp->framesize == 0) {
		// We've started a new frame, so first decode the header.
		if(bs->bytesleft < (4 - mp->iHeaderBytes))
		{
			mp->iHeaderBytes += bs->bytesleft;
			add_bytes_to_header(bs, &(mp->header), bs->bytesleft);
			return MP3_NEED_MORE;
		}

		if (mp->iHeaderBytes)
			add_bytes_to_header(bs, &(mp->header), 4 - mp->iHeaderBytes);
		else
			mp->header = read_head(bs);

#ifndef READ_EVERY_HEADER
		if (bDecodeHeader)
		{
#endif	// READ_EVERY_HEADER
			if (decode_header(&mp->fr,mp->header) != MP3_OK)
#ifdef TRY_RESYNCH
				do {
					DEBUG("Resynch attempt\n");
					// This isn't a perfect resynch since it ingores the bytes already in the header.
					mp->iHeaderBytes = 0;
					if (bs->bytesleft <= 4)
					{
						bs->bytesleft = 0;
						return MP3_NEED_MORE;
					}
					bs->bytesleft--;
					bs->bufptr++;
					if (dsp_SynchMP3(bs) == MP3_ERR)
					{
//						mp->iHeaderBytes += bs->bytesleft;
//						add_bytes_to_header(bs, &(mp->header), bs->bytesleft);
						return MP3_NEED_MORE;
					}
					mp->header = read_head(bs);
				} while (decode_header(&mp->fr, mp->header) != MP3_OK);
#else	// TRY_RESYNCH
				return MP3_ERR;
#endif	// TRY_RESYNCH

			mp->framesize = mp->fr.framesize;
#ifndef READ_EVERY_HEADER
		}
		else
		{
//			if (decode_header_fast(&mp->fr, mp->header) != MP3_OK)
//				return MP3_ERR;
			decode_header_fast(&mp->fr, mp->header);
			mp->framesize = mp->fr.framesize;
		}
#endif	// READ_EVERY_HEADER

		// Switch buffers.
		wordpointer = mp->bsspace[mp->bsnum] + 512;
		mp->bsnum = (mp->bsnum + 1) & 0x1;
		bitindex = 0;
	}

	k = setjmp(mp3jbuf);
		
	if (k)
	{
		mp->fsizeold = mp->framesize;
		mp->framesize = 0;
		mp->header = 0;
		mp->iHeaderBytes = 0;
		mp->iValidBytes = 0;
#ifdef TRY_RESYNCH
		return MP3_NEED_MORE;
#else	// TRY_RESYNCH
		return MP3_ERR;
#endif	// TRY_RESYNCH
	}

	iBytesToRead = mp->fr.framesize - mp->iValidBytes;
	if(iBytesToRead > bs->bytesleft)
	{
//		memcpy((unsigned char*)(wordpointer + mp->iValidBytes), bs->bufptr, bs->bytesleft);
		memcpy(wordpointer + mp->iValidBytes, bs->bufptr, bs->bytesleft);
		mp->iValidBytes += bs->bytesleft;
		bs->bufptr += bs->bytesleft;
		bs->bytesleft = 0;

		return MP3_NEED_MORE;
	}
	else
	{
//		memcpy((unsigned char*)(wordpointer + mp->iValidBytes), bs->bufptr, iBytesToRead);
		memcpy(wordpointer + mp->iValidBytes, bs->bufptr, iBytesToRead);
		mp->iValidBytes = mp->framesize;
		bs->bufptr += iBytesToRead;
		bs->bytesleft -= iBytesToRead;
	}

#if 0
	len = 0;

	while(len < mp->framesize) {
		int nlen;		// Bytes to copy.

		// If more data is needed but the input buffer is empty, then return back to the caller.
		if (bs->bytesleft <= 0)
		{
			mp->fsizeold = mp->framesize;
			mp->framesize = 0;
//			return MP3_NEED_MORE;
			return MP3_OK;
		}

		if( (mp->framesize - len) <= bs->bytesleft) {
			nlen = mp->framesize-len;
		}
		else {
			nlen = bs->bytesleft;
		}
		memcpy(wordpointer+len, bs->bufptr, nlen);
		len += nlen;
		bs->bufptr += nlen;
		bs->bytesleft -= nlen;
	}
#endif

	if(mp->fr.error_protection)
		mp3_getbits(16);
	do_layer3(&mp->fr, out_left, out_right, iBytesWritten);

	mp->fsizeold = mp->framesize;
	mp->framesize = 0;
#ifdef READ_EVERY_HEADER
	mp->header = 0;
#endif	// READ_EVERY_HEADER
	mp->iHeaderBytes = 0;
	mp->iValidBytes = 0;

	return MP3_OK;
}


int set_pointer(long backstep)
{
	unsigned char *bsbufold;
	if(gmp->fsizeold < 0 && backstep > 0) {
		DEBUG("Can't step back %d!\n",backstep);
		return MP3_ERR;
	}
	bsbufold = gmp->bsspace[gmp->bsnum] + 512;
	wordpointer -= backstep;
	if (backstep)
		memcpy(wordpointer,bsbufold+gmp->fsizeold-backstep,backstep);
	bitindex = 0;
	return MP3_OK;
}
