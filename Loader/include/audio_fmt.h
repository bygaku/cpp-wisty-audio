#ifndef AUDIO_FMT_INCLUDE
#define AUDIO_FMT_INCLUDE

namespace wwist {

	typedef unsigned char	MY_BYTE;	// for 1 byte data.
	typedef unsigned short  MY_WORD;	// for 2 bytes data.
	typedef unsigned long	MY_DWORD;	// for 4 bytes data.
	typedef MY_DWORD		CHUNK_ID;	// FOURcc

	/**
	 * @brief creates a new 4-character code from four characters.
	 * @code
	 *  constexpr CHUNK_ID YOU_ID = CHUNK_ID('Y', 'O', 'U', ' ');
	 * @endcode
	*/
	#define Chunk_ID(a, b, c, d) (a + (b << 8) + (c << 16) + (d << 24))
	constexpr CHUNK_ID RIFF_ID = Chunk_ID('R', 'I', 'F', 'F');
	constexpr CHUNK_ID LIST_ID = Chunk_ID('L', 'I', 'S', 'T');
	constexpr CHUNK_ID FMT_ID  = Chunk_ID('f', 'm', 't', ' ');
	constexpr CHUNK_ID DATA_ID = Chunk_ID('d', 'a', 't', 'a');

	/**
	 * @brief swaps the byte order of a 32-bit data value.
	 * @param data reference to the 32-bit data (DWORD) whose byte order will be swapped.
	 * @details
	 *	this function reverses the byte order by shifting each byte to its
	 *	opposite position:
	 *	the lowest 8 bits are shifted to the highest 8 bits position.
	 *	the second lowest 8 bits are shifted to the second highest position.
	 *	the second highest 8 bits are shifted to the second lowest position.
	 *	the highest 8 bits are shifted to the lowest position.
	 *	this effectively converts between little-endian and big-endian formats,
	 *	commonly used for endian conversion in data processing.
	*/
	inline void Swap32Bit(MY_DWORD& data) {
		data = ((data & 0x000000FF) << 24)
			 + ((data & 0x0000FF00) << 8)
			 + ((data & 0x00FF0000) >> 8)
			 + ((data & 0xFF000000) >> 24);
	};

	/**
	 * @brief swaps the byte order of a 16-bit data value.
	 * @param data reference to the 16-bit data (WORD) whose byte order will be swapped.
	 * @details
	 * 	this function reverses the byte order by shifting the lower 8 bits
	 * 	to the upper 8 bits and the upper 8 bits to the lower 8 bits,
	 * 	effectively converting between little-endian and big-endian formats.
	 * 	It is commonly used for endian conversion in data processing.
	*/
	inline void Swap16Bit(MY_WORD& data) {
		data = ((data & 0x00FF) << 8)
			 + ((data & 0xFF00) >> 8);
	};


    /** Audio File Information */
    struct AudioMetaData {
        MY_WORD sample_rate;
        MY_BYTE channel;
        MY_BYTE bit_depth;

    	AudioMetaData(const MY_WORD& sample_rate
    				, const MY_BYTE& bit_depth
    				, const MY_BYTE& channel)
    	{
    		this->sample_rate	= sample_rate;
    		this->bit_depth		= bit_depth;
    		this->channel		= channel;

    	}
    };


	/** wav format data */
    namespace wav {
    }

	// end wwist
}

#endif // AUDIO_FMT_INCLUDE