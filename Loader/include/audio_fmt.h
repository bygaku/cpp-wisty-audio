#ifndef __AUDIO_FMT_H__
#define __AUDIO_FMT_H__
#include <cstdint>

namespace wwist {

	typedef unsigned char	BYTE;	// 1 byte
	typedef unsigned short  WORD;	// 2 bytes
	typedef unsigned long	DWORD;	// 4 bytes

    /* Audio File Information */
    struct AudioMetaData {
        WORD sample_rate;
        BYTE channel;
        BYTE bit_depth;

    	AudioMetaData(const WORD& sample_rate
    				, const BYTE& bit_depth
    				, const BYTE& channel)
    	{
    		this->sample_rate	= sample_rate;
    		this->bit_depth		= bit_depth;
    		this->channel		= channel;

    	}
    };


	//* wav format data
    namespace wav {

		// padding blocker
		#pragma pack(push, 1)

        /* RIFF Header */
		struct RIFFChunk {
			BYTE	 id[4];
        	BYTE	 type[4];
			uint32_t size;
		};

        /* FMT SubChunk */
		struct FMTChunk {
			BYTE	 id[4];			// "fmt " (0x666D7420)
			uint32_t size;			// linear PCM: (0x10000000), other: (16 + extension parameters)
			uint16_t type;			// PCM: (0x0100), IEEE float: (0x0300)
			uint16_t channel;		// mono: (0x0100), stereo: (0x0200)
			uint32_t sample_rate;	// 8kHz: (0x401F0000), 44.1kHz: (0x44AC0000)
			uint32_t byte;			// sample_rate * block_size
			uint16_t block_size;	// channel * bit depth / 8
			uint16_t bit_depth;		// bit depth (0x0800 or 0x1000)
		};

    	/* Chunk Header*/
    	struct ChunkHeader {
    		BYTE	 id[4];
    		uint32_t size;
    	};

    	/* WAV Extension Chunk */
		struct ExtensionChunk {
			uint16_t size;

		};

		#pragma pack(pop)
    	// end wav
    }

	// end wwist
}

#endif // __AUDIO_FMT_H__