#ifndef WAVE_INCLUDE
#define WAVE_INCLUDE

#include "riff_fmt.h"
#include <vector>
#include <map>

/** wav header */
namespace wwist::wav {
	typedef std::vector<MY_WORD> BUFF_WAV;	// for 16bit data.
	typedef std::vector<MY_BYTE> CBUFF_WAV;	// for 8bit data.

	constexpr CHUNK_ID WAVE_ID = Chunk_ID('W', 'A', 'V', 'E');
	constexpr CHUNK_ID FMT_ID  = Chunk_ID('f', 'm', 't', ' ');
	constexpr CHUNK_ID DATA_ID = Chunk_ID('d', 'a', 't', 'a');
	constexpr MY_DWORD PCM     = 16;

	enum class Channel : int {
		M = 1,
		L = 2,
		R = 3
	};

	struct FMTChunk {
		MY_WORD  format_type;	// PCM: (0x0100), IEEE float: (0x0300)
		MY_WORD  channel_num;	// mono: (0x0100), stereo: (0x0200)
		MY_DWORD sample_rate;	// 8kHz: (0x401F0000), 44.1kHz: (0x44AC0000)
		MY_DWORD data_rate;		// sample_rate * block_size
		MY_WORD  block_size;	// channel * bit depth / 8
		MY_WORD  bit_depth;		// bit depth (0x0800 or 0x1000)
	};

	/**
 	 * TODO: LIST::INFOからコピーして保存.
 	 *
 	*/
	struct LISTChunk {

	};

	struct dataChunk {
		std::map<Channel, BUFF_WAV> ch;
	};

	struct Wave {
		MY_DWORD	length{};
		FMTChunk	fmt{};
		LISTChunk	list{};
		dataChunk	data{};
	};
} // end wwist::wav

#endif // WAVE_INCLUDE