#ifndef __WAV_FMT_H__
#define __WAV_FMT_H__
#include "audio_fmt.h"
#include <vector>

/** wav format */
namespace wwist::wav {
	typedef std::vector<MY_WORD> BUFF_WAV;

#pragma pack(push, 1)	// padding blocker

	/** RIFF header */
	struct RIFFChunk {
		CHUNK_ID id;
		MY_DWORD size;
		MY_BYTE	 type[4];
	};

	/** FMT chunk */
	struct FMTChunk {
		CHUNK_ID id;			// "fmt " (0x666D7420)
		MY_DWORD size;			// linear PCM: (0x10000000), other: (16 + extension parameters)
		MY_WORD	 type;			// PCM: (0x0100), IEEE float: (0x0300)
		MY_WORD	 channel;		// mono: (0x0100), stereo: (0x0200)
		MY_DWORD sample_rate;	// 8kHz: (0x401F0000), 44.1kHz: (0x44AC0000)
		MY_DWORD byte;			// sample_rate * block_size
		MY_WORD	 block_size;	// channel * bit depth / 8
		MY_WORD	 bit_depth;		// bit depth (0x0800 or 0x1000)
	};

	/** Original header*/
	struct ChunkHeader {
		CHUNK_ID id;
		MY_DWORD size;
	};

	/** Extension chunk */
	struct ExtensionChunk {
		MY_DWORD size;

	};

#pragma pack(pop)

} // end wwist::wav

#endif //__WAV_FMT_H__