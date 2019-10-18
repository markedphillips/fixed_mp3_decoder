//........................................................................................
//........................................................................................
//.. File Name: mp3_codec_hipp.cpp														..
//.. Date: 7/17/2000																	..
//.. Author(s): Eric Gibbs, Mark Phillips												..
//.. Description of content: implementation of the CPCMCodec class			 			..
//.. Usage: This is a part of the IObjects Direct Streaming Services Library 			..
//.. Last Modified By: Ed Miller
//.. 																					.
//.. Modification date: 10/24/2000														..
//........................................................................................
//.. Copyright:(c) 1995-2000 Interactive Objects Inc.  									..
//..	 All rights reserved. This code may not be redistributed in source or linkable  ..
//.. 	 object form without the express written consent of Interactive Objects.        ..
//.. Contact Information: Removed											..
//.. Assets of Interactive Objects acquired by Mark Phillips							..
//........................................................................................
//........................................................................................

#include <cyg/kernel/kapi.h>
#include <string.h>
#include <debug.h>
#include "mp3_codec_hipp.h"

extern "C" void swap_bytes(void *buf, int n);

inline void *operator new(size_t size, void *ptr)
{
	CYG_CHECK_DATA_PTR(ptr, "Bad pointer");
	return ptr;
}

static bool FindID3Headers(CInputStream &file, unsigned long &ID3v1Size, unsigned long &ID3v2Size);

//////////////////////////////////////////////////////////////////////
//
//  CMP3HippCodec implementation
//
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMP3HippCodec::CMP3HippCodec()
{
	//Initialize MPEG Instance information
	dsp_InitMP3(&m_mpstr);

	// Determine the pointer to the MP3 decoder library's persistent
	// state.  This pointer must be aligned on a 2K byte boundary.
	//	m_pMPEGInstance = (tMPEGInstance*)(((unsigned long)m_MPEGInstanceData + 2047) & 0xfffff800);
}

CMP3HippCodec::~CMP3HippCodec()
{
	dsp_ExitMP3(&m_mpstr);
}

int CMP3HippCodec::SetSong(CInputStream *pSongFile, song_info_t &info, bool bGetSongInfo)
{
	m_pSongFile = pSongFile;
#if 0
	//Double check input stream to be correct content
	//Initialize the MP3 library
    (*InitMP3Audio)( m_pMPEGInstance );
#endif

	// Get the length of the MP3 bitstream.
	m_ulFileLength = m_pSongFile->Length();

	if (bGetSongInfo)
	{
		//Initialize offsets into file to ignore id3v1 and id3v2 data
		FindID3Headers(*m_pSongFile, m_ID3v1size, m_ID3v2size);

		//Set ID3Info
		if (m_ID3v1size || m_ID3v2size)
		{
			if (m_ID3v1size)
			{
				m_pSongFile->Seek(-128, CInputStream::EndOfFile);
				id3tag tag;
				m_pSongFile->Read((unsigned char *)&tag, 128);
				if (tag.tag[0] == 'T' && tag.tag[1] == 'A' && tag.tag[2] == 'G')
				{
					//We've got an ID3v1 tag
					int i;
					char *src, *dst;
					//copy title
					src = tag.title;
					dst = info.szTitle;
					for (i = 0; i < 30; i++)
						*dst++ = *src++;
					*dst = 0;
					// copy artist
					src = tag.artist;
					dst = info.szArtist;
					for (i = 0; i < 30; i++)
						*dst++ = *src++;
					*dst = 0;
					//copy year
					src = tag.year;
					dst = info.szCopyright;
					for (i = 0; i < 4; i++)
						*dst++ = *src++;
					*dst = 0;
					// copy genre index to be used by jukebox
					//				info.Genre = tag.genre;
					info.szGenre[0] = '\0';
				}
			}
			//PopulateID3Info(*m_pSongFile,info);
		}
	}
	else
	{
		m_ID3v1size = 0;
		m_ID3v2size = 0;

		// (epg,8/3/2000): avoid id3v2 crash
		unsigned char buf[128];
		long lValid = m_pSongFile->Read(buf, 10);
		if (lValid < 0)
			return CODEC_FAIL;

		if (buf[0] == 0x49 && buf[1] == 0x44 && buf[2] == 0x33)
		{
			m_ID3v2size = (static_cast<unsigned long>(buf[6]) << 21) |
						  (static_cast<unsigned long>(buf[7]) << 14) |
						  (static_cast<unsigned long>(buf[8]) << 7) |
						  static_cast<unsigned long>(buf[9]);
			m_ID3v2size += 10;
		}
	}

	// Read the first four pages of the file.
	m_pSongFile->Seek(0 + m_ID3v2size, CInputStream::StartOfFile);

	// Since we've just read the first four pages of the file, the next
	// read will occur at location 2048 into the file.
	m_ulFilePos = m_ID3v2size + m_pSongFile->Read((unsigned char *)m_pcEncodedData, DECODE_BUFLEN);

	// Initialize the bitstream pointer structure.
	m_sBS.bufptr = m_pcEncodedData;
	m_sBS.bytesleft = m_ulFilePos;

	// Find the first sync word in the stream.
	if (dsp_SynchMP3(&m_sBS) != MP3_OK)
	{
		//We could not find a sync word, so return an error.
		//Invalid File Type?
		return CODEC_FILE_WRONG_FORMAT;
	}

	// Decode the header.
	if (dsp_DecodeHeader(&m_mpstr, &m_sBS, &(info.SamplingFrequency), &(info.Channels), &(info.BitRate)) != MP3_OK)
	{
		// The header wasn't decoded properly, so this may be an unsupported layer or format.
		return CODEC_FILE_UNSUPPORTED_ENCODING;
	}

	m_ulSampleRate = info.SamplingFrequency;
	info.HasDRM = false;

	//	dsp_ExitMP3(&m_mpstr);
	dsp_InitMP3(&m_mpstr);

	// Re-initialize the bitstream pointer structure.
	m_sBS.bufptr = m_pcEncodedData;
	m_sBS.bytesleft = m_ulFilePos;

	// Re-synch.
	dsp_SynchMP3(&m_sBS);

	// Get the length of the file in seconds.
	m_ulDuration = (((m_ulFileLength - m_ID3v1size - m_ID3v2size) * 8) / info.BitRate);
	info.Duration = m_ulDuration;

	// The time position is zero.
	m_TimePos = 0.0f;

#ifdef WRITE_WAVE_DATA
	char szOutfileName[512];
	strcpy(szOutfileName, szFileName);
	int len = strlen(szFileName);
	szOutfileName[len - 3] = 'r';
	szOutfileName[len - 2] = 'a';
	szOutfileName[len - 1] = 'w';
	DEBUG("Creating file %s", szOutfileName);
	m_WaveFile.Close();
	m_WaveFile.Open(szOutfileName);
#endif // WRITE_WAVE_DATA

	return CODEC_SUCCESS;
	//	return CODEC_FAIL;
}

int CMP3HippCodec::DecodeFrame(wave_buffer_t *pBuffer, unsigned long &SamplesPerChannel, unsigned long &TimePos)
{

#if 0
    // If the bitstream pointer is not at the beginning of the local
    // bitstream buffer, then copy the remaining data back to the
    // beginning.
    if((int)m_sBS.bufptr != (int)m_pcEncodedData)
    {
        //
        // Copy the remainder of the data from the end of the local
        // bitstream buffer to the beginning.
        //
        memcpy(m_pcEncodedData, m_sBS.bufptr, m_sBS.bytesleft);

        //
        // Update the count of valid bytes in the local bitstream
        // buffer.
        //
        m_ulValid -= (int)m_sBS.bufptr - (int)m_pcEncodedData;

        //
        // Update the bitstream pointer structure.
        //
        m_sBS.bufptr = m_pcEncodedData;
    }
#endif

	//
	// See if there is any additional MP3 data that we can copy into
	// the local bitstream buffer.
	//
	bool bNearEOF = false;
	if ((m_sBS.bytesleft <= 0) &&
		(m_ulFilePos < (m_ulFileLength - m_ID3v1size)))
	{
#if 0
		//
		// Compute the number of bytes to read.
		//
		unsigned long ulToRead = DECODE_BUFLEN - m_ulValid;
		if(ulToRead > (m_ulFileLength - m_ID3v1size - m_ulFilePos))
		{
			ulToRead = m_ulFileLength - m_ID3v1size - m_ulFilePos;
			m_bNearEOF = true;
		}
		else
			ulToRead &= ~511;
		
		//
		// Read MP3 data to the end of the local bitstream buffer.
		// Since the ARM MP3 decoder needs the bytes within each word
		// swapped
		//
		unsigned char* pBuffer = (unsigned char*)(m_pcEncodedData+m_ulValid);
		unsigned long ulRead = m_pSongFile->Read(pBuffer, ulToRead);
#else
		unsigned long ulToRead = DECODE_BUFLEN;
		if (ulToRead > (m_ulFileLength - m_ID3v1size - m_ulFilePos))
		{
			ulToRead = m_ulFileLength - m_ID3v1size - m_ulFilePos;
			bNearEOF = true;
		}
		unsigned long ulRead = m_pSongFile->Read((unsigned char *)m_pcEncodedData, ulToRead);
		m_sBS.bufptr = m_pcEncodedData;
#endif

		if (ulRead)
		{
			if (ulRead & 0x3)
				ulRead = (ulRead & ~3) + 4;

#if 0				
			// Update the count of valid bytes.
			//
			m_ulValid += ulRead;
			m_sBS.bytesleft += ulRead;
#endif
			m_sBS.bytesleft = ulRead;

			//
			// Update the offset into the MP3 file.
			//
			m_ulFilePos += ulRead;
		}
	}

	pBuffer->is_interleaved = false;
	int iTotalBytesWritten = 0;
	int iRet;

	do
	{

		int iBytesWritten;
		iRet = dsp_DecodeMP3(&m_mpstr,
							 &m_sBS,
							 (unsigned char *)(pBuffer->buf_un.non_interleaved.left) + iTotalBytesWritten,
							 (unsigned char *)(pBuffer->buf_un.non_interleaved.right) + iTotalBytesWritten,
							 WAVEBUFFER_SIZE - iTotalBytesWritten,
							 &iBytesWritten);

		iTotalBytesWritten += iBytesWritten;

	} while (iRet == MP3_OK);

#ifdef WRITE_WAVE_DATA
	m_WaveFile.Write((unsigned char *)(pBuffer->buf_un.non_interleaved.left), iTotalBytesWritten);
#endif // WRITE_WAVE_DATA

	switch (iRet)
	{
	case MP3_OK:
	case MP3_NEED_MORE:
	case MP3_BUFFER_FULL:
		SamplesPerChannel = iTotalBytesWritten / 2;
		//
		// Increment the time based on the number of samples.
		//
		m_TimePos += 1000.0f * static_cast<float>(SamplesPerChannel) / static_cast<float>(m_ulSampleRate);
		TimePos = static_cast<unsigned long>(m_TimePos / 1000.0f);

		//			if (m_ulFilePos >= m_ulFileLength)
		if (bNearEOF)
			return CODEC_END_OF_FILE;
		else
			return CODEC_SUCCESS;
	case MP3_EXIT:
		return CODEC_END_OF_FILE;
	case MP3_ERR:
		DEBUG("Error decoding mp3 frame\n");
		return CODEC_FAIL;
	default:
		DEBUG("Unknown return value while decoding mp3 frame: %d\n", iRet);
		return CODEC_FAIL;
	};
}

int CMP3HippCodec::Seek(unsigned long &secSeek)
{
	if (secSeek > m_ulDuration)
		return CODEC_FAIL;

	long mpegdata = m_ulFileLength - m_ID3v2size - m_ID3v1size;
	long Offset = m_ID3v2size + (long)(float(mpegdata) * (float(secSeek) / float(m_ulDuration)));

	// Make Offset aligned with the length of the encoded data buffer.
	long iPageNum = Offset / DECODE_BUFLEN;
	Offset = iPageNum * DECODE_BUFLEN;

	m_pSongFile->Seek(Offset, CInputStream::StartOfFile);

	m_ulFilePos = Offset;

	//Must loop until both MP3SearchForSyncword and MP3DecodeInfo are happy
	//with the bitstream

	int Res = CODEC_FAIL; // generic error
	unsigned long ulRead;
	//	int index;

	// Read the first four pages of the file.
	ulRead = m_pSongFile->Read((unsigned char *)m_pcEncodedData, DECODE_BUFLEN);
	m_sBS.bufptr = m_pcEncodedData;
	m_sBS.bytesleft = DECODE_BUFLEN;
	m_ulFilePos += ulRead;

	do
	{
		if (dsp_SynchMP3(&m_sBS) != MP3_OK)
		{
			Res = CODEC_FILE_WRONG_FORMAT;
			break;
		}
		else
		{
			unsigned long dummy;
			if (dsp_DecodeHeader(&m_mpstr, &m_sBS, &dummy, &dummy, &dummy) == MP3_OK)
			{
				// A good header was found, so exit the search loop.
				Res = CODEC_SUCCESS;
				//				m_pSongFile->Seek(Offset + index,CInputStream::StartOfFile);
				//				m_ulFilePos = Offset + index;
				// Rewind to the start of the header.
				m_sBS.bufptr -= 4;
				m_sBS.bytesleft += 4;

				// Reset the hipp codec.
				//				dsp_ExitMP3(&m_mpstr);
				dsp_InitMP3(&m_mpstr);

				break;
			}
			else
			{
				// Rewind to one byte after the start of the header.
				m_sBS.bufptr -= 3;
				m_sBS.bytesleft += 3;
			}
		}
	} while (1);

#if 0

	// Initialize the bitstream pointer structure.
	m_sBS.bufptr = (unsigned int *)(m_pcEncodedData);
	
	// Initially, the 2048 bytes previously read into the buffer are
	// valid.
	m_ulValid = ulRead;

	while(m_ulFilePos < (m_ulFileLength - m_ID3v1size))
	{
		
		(*InitMP3Audio)( m_pMPEGInstance );

		// Find the first sync word in the stream.
		if((*MP3SearchForSyncword)(m_pMPEGInstance, &m_sBS, m_ulValid * 8) != eNoErr)
		{
			//We could not find a sync word, so return an error.
			//Invalid File Type?
			Res =  CODEC_FILE_WRONG_FORMAT;
			break;
		}
		
		tMPEGHeader sHdr;
		if(eNoErr == (*MP3DecodeInfo)(m_pMPEGInstance, &m_sBS, &sHdr))
		{
			//We could decode the header, so setup the bitstream accordingly
			//and break
			--m_sBS.bufptr;

			Res = CODEC_SUCCESS;

			break;
		}
		//At this point, we found a syncword, but couldn't decode the header,
		//so we need to setup the bitstream accordingly and continue

        memcpy(m_pcEncodedData, m_sBS.bufptr,
               DECODE_BUFLEN - ((int)m_sBS.bufptr - (int)m_pcEncodedData));

        //
        // Update the count of valid bytes in the local bitstream
        // buffer.
        //
        m_ulValid -= (int)m_sBS.bufptr - (int)m_pcEncodedData;

		m_sBS.bufptr = (unsigned int*)m_pcEncodedData;

		if((m_ulValid <= (DECODE_BUFLEN - 512)) &&
			(m_ulFilePos < (m_ulFileLength - m_ID3v1size)))
		{
			//
			// Compute the number of bytes to read.
			//
			ulRead = DECODE_BUFLEN - m_ulValid;
			if(ulRead > (m_ulFileLength - m_ID3v1size - m_ulFilePos))
			{
				ulRead = m_ulFileLength - m_ID3v1size - m_ulFilePos;
			}
			ulRead &= ~511;
			
			//
			// Read MP3 data to the end of the local bitstream buffer.
			// Since the ARM MP3 decoder needs the bytes within each word
			// swapped
			//
			unsigned char* pBuffer = (unsigned char*)(m_pcEncodedData+m_ulValid);
			m_pSongFile->Read(pBuffer, ulRead);
			
			swap_bytes(pBuffer,ulRead);
			
			// Update the count of valid bytes.
			//
			m_ulValid += ulRead;
			
			//
			// Update the offset into the MP3 file.
			//
			m_ulFilePos += ulRead;
		}

	}
	
	m_bNearEOF = false;

	//Set Time Pos
	m_TimePos = 1000.0f * float(m_ulDuration) * 
					   float(m_ulFilePos - m_ID3v2size) / float(mpegdata);
	
	secSeek = (unsigned long)(m_TimePos / 1000.0f);

	return Res;

#else

	//Set Time Pos
	m_TimePos = 1000.0f * float(m_ulDuration) *
				float(m_ulFilePos - m_ID3v2size) / float(mpegdata);

	secSeek = (unsigned long)(m_TimePos / 1000.0f);

	return Res;

#endif
}

/////////////////////////////////////
//
// Helper functions
//

static bool FindID3Headers(CInputStream &file, unsigned long &ID3v1Size, unsigned long &ID3v2Size)
{
	//Check for ID3v2 tag
	unsigned char buf[10];

	file.Seek(0, CInputStream::StartOfFile);
	file.Read(buf, 10);

	if (buf[0] == 0x49 && buf[1] == 0x44 && buf[2] == 0x33)
	{
		ID3v2Size = (static_cast<unsigned long>(buf[6]) << 21) |
					(static_cast<unsigned long>(buf[7]) << 14) |
					(static_cast<unsigned long>(buf[8]) << 7) |
					static_cast<unsigned long>(buf[9]);
		ID3v2Size += 10;
	}
	else
		ID3v2Size = 0;

	file.Seek(-128, CInputStream::EndOfFile);
	file.Read(buf, 3);
	if (buf[0] == 'T' && buf[1] == 'A' && buf[2] == 'G')
		ID3v1Size = 128;
	else
		ID3v1Size = 0;

	return true;
}
