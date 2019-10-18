//........................................................................................
//........................................................................................
//.. File Name: mp3_codec_hipp.h																	..
//.. Date: 7/17/2000																	..
//.. Author(s): Eric Gibbs, Mark Phillips																..
//.. Description of content: interface for the CPCMCodec class			 				..
//.. Usage: This is a part of the IObjects Direct Streaming Services Library 			..
//.. Last Modified By: Ed Miller
//.. Modification date: 10/24/2000														..
//........................................................................................
//.. Copyright:(c) 1995-2000 Interactive Objects Inc.  									..
//..	 All rights reserved. This code may not be redistributed in source or linkable  ..
//.. 	 object form without the express written consent of Interactive Objects.        ..
//.. Contact Information: www.iobjects.com												..
//........................................................................................
//........................................................................................

#if !defined(_IJAM_MP3_CODEC_HIPP_H__)
#define	_IJAM_MP3_CODEC_HIPP_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define WRITE_WAVE_DATA

#include "MediaPlayer.h"
#ifdef MULTIBUF
#include "PlaylistInputStream.h"
#else
#include "FileInputStream.h"
#endif
#ifdef WRITE_WAVE_DATA
#include "FileOutputStream.h"
#endif	// WRITE_WAVE_DATA
#include "mpgdata.h"
#include "mpgaudio.h"

//extern "C"
//{
#include <hipp_dsp.h>
//}

struct id3tag {
	char tag[3];
	char title[30];
	char artist[30];
	char album[30];
	char year[4];
	char comment[30];
	unsigned char genre;
};

// Defines taken from mp3_play.c
//#define DECODE_BUFLEN 9216
//#define DECODE_BUFLEN 8192
#define DECODE_BUFLEN 4096
//#define DECODE_BUFLEN 2048
//#define DECODE_BUFLEN 1024


class CMP3HippCodec : public ICodec
{
public:
	CMP3HippCodec();
	~CMP3HippCodec();

	int Initialize(mem_buffer_t* pMemBuffer);
	int Uninitialize();
	int DecodeFrame(wave_buffer_t* pBuffer, unsigned long& SamplesPerChannel, unsigned long& TimePos);	
	int SetSong(CInputStream* pSongFile, song_info_t& info, bool bGetSongInfo);
	int Seek(unsigned long &secSeek);
	const char* GetCodecName() const
		{ return "MPEG-1 Layer 3"; }


	CInputStream*		m_pSongFile;  
#ifdef WRITE_WAVE_DATA
	CFileOutputStream	m_WaveFile;
#endif	// WRITE_WAVE_DATA
	char				m_pcEncodedData[DECODE_BUFLEN];
    tHippMPEGBitstream	m_sBS;					// The MP3 bitstream pointer.
	unsigned long		m_ulFileLength; // The length of the encoded MP3 file.
	unsigned long		m_ulFilePos;    // The current offset into the MP3 file, indicating the number of bytes
										// which have been read from the file into the encoded data buffer.
	float				m_TimePos;		// Position in the song in milliseconds
	unsigned long		m_ulDuration;	// The length of the file in seconds.
    unsigned long		m_ulSampleRate; // The sample rate of the decoded PCM stream.
		
	struct mpstr		m_mpstr;	// Info about the Hipp codec.

	unsigned long		m_ID3v2size;
	unsigned long		m_ID3v1size;
};


#endif // _IJAM_MP3_CODEC_HIPP_H__
