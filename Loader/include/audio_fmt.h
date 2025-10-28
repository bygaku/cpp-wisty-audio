#ifndef __AUDIO_FMT_H__
#define __AUDIO_FMT_H__

namespace wwist {

	typedef unsigned char	uchar;	// unsigned char
	typedef unsigned short  ushort; // unsigned short
	typedef unsigned int	uint;	// unsigned int

    /* Audio File Information */
    struct AudioInfo {
        ushort sample_rate;
        uchar  channel;
        uchar  bit_depth;
    	uchar  flag;

    	AudioInfo(const uint& sample_rate
    			, const uchar& bit_depth
    			, const unsigned char& channel
    			, const unsigned char& flag)
    	{
    		this->sample_rate	= sample_rate;
    		this->bit_depth		= bit_depth;
    		this->channel		= channel;

    	}
    };


	//* wav format data
    namespace wav {

        /* RIFF Chunk */
		struct RIFF {
			char id[4];
			long size;
        	char type[4];
		};

        /* FMT Chunk */
		struct FMT {
			char  id[4];		// "fmt " (0x666D7420)
			long  size;			// linear PCM: (0x10000000), other: (16 + extension parameters)
			short type;
			short channel;		// mono: 1(0x0100), stereo: 2(0x0200)
			long  sample_rate;	// 8kHz: (0x401F0000), 44.1kHz: (0x44AC0000)
			long  byte;			// sample_rate * block_size
			short block_size;	// channel * bit depth / 8
			short bit_depth;	// bit depth (8: 0x0800 or 16: 0x1000)
		};

    	/* DATA Chunk */
		struct DATA {

		};

    	// end wav
    }

	// end wwist
}

#endif // __AUDIO_FMT_H__