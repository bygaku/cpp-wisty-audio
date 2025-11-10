#ifndef WAV_FMT_INCLUDE
#define WAV_FMT_INCLUDE

#include "riff_fmt.h"
#include <vector>

/** wav format */
namespace wwist::wav {
	typedef std::vector<MY_WORD> BUFF_WAV;

	constexpr CHUNK_ID FMT_ID  = Chunk_ID('f', 'm', 't', ' ');
	constexpr CHUNK_ID DATA_ID = Chunk_ID('d', 'a', 't', 'a');

	struct FMTChunk {
		MY_WORD  format_type;	// PCM: (0x0100), IEEE float: (0x0300)
		MY_WORD  channel_num;	// mono: (0x0100), stereo: (0x0200)
		MY_DWORD sample_rate;	// 8kHz: (0x401F0000), 44.1kHz: (0x44AC0000)
		MY_DWORD data_rate;		// sample_rate * block_size
		MY_WORD  block_size;	// channel * bit depth / 8
		MY_WORD  bit_depth;		// bit depth (0x0800 or 0x1000)
	};

} // end wwist::wav

#endif // WAV_FMT_INCLUDE