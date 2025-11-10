#ifndef LOADER_WAV_INCLUDE
#define LOADER_WAV_INCLUDE

#include "wav_fmt.h"
#include "reader_riff.h"

namespace wwist::wav {
	/**
	 * @brief read a wav file.
	 * @retval <false> failure reading
	 * @retval <true> success reading
	 */
	inline bool ReadWavFile(char			file_name[],
							wav::BUFF_WAV*	wav_l,
							wav::BUFF_WAV*	wav_r,
							short*			channel_num,
							int*			sample_rate
							)
	{
		RIFFReader riff_reader(file_name);
		if (riff_reader.GetFileSize() == 0) return false;

		FMTChunk fmt_chunk{};
		if (riff_reader.GetChunkSize(FMT_ID) != 16)						  return false;
		if (riff_reader.GetChunkData(FMT_ID, &fmt_chunk, 16) == 0) return false;

		if (fmt_chunk.sample_rate != 44100							) return false;
		if (fmt_chunk.bit_depth	  != 16								) return false;
		if (fmt_chunk.channel_num != 1 && fmt_chunk.channel_num != 2) return false;

		(*sample_rate) = static_cast<int>(fmt_chunk.sample_rate);
		(*channel_num) = static_cast<short>(fmt_chunk.channel_num);

		int data_size = static_cast<int>(riff_reader.GetChunkSize(DATA_ID));
		if (data_size == 0) return false;

		int		bytes	= fmt_chunk.bit_depth / 8;
		auto*	tmp_buf = new short[data_size / bytes];

		if (riff_reader.GetChunkData(DATA_ID, tmp_buf, data_size) == 0) {
			delete[] tmp_buf;
			return false;
		}

		wav_l->clear();
		wav_r->clear();

		int loops = (data_size / bytes) / fmt_chunk.channel_num;
		for (int i = 0; i < loops; i++) {
			if (fmt_chunk.channel_num == 1) {
				wav_l->push_back(tmp_buf[i]);
				wav_r->push_back(tmp_buf[i]);
			}
			else {
				wav_l->push_back(tmp_buf[i * fmt_chunk.channel_num]);
				wav_r->push_back(tmp_buf[i * fmt_chunk.channel_num + 1]);
			}
		}

		delete[] tmp_buf;

		return true;
	}

	/* Wav Format Loader */
	// class LoaderWav {
	// 	/* result data */
	// 	struct AudioData {
	// 	};
	//
	// public:
	// 	~LoaderWav() {
	// 	};
	//
	// 	/**
	// 	 * @brief loading from file_path and return AudioData.
	// 	 * @param file_path audio file path name
	// 	 * @retval AudioData: Loaded successfully.
	// 	*/
	// 	static AudioData Load(const std::string &file_path);
	//
	// 	/**
	// 	 * @brief get audio file information
	// 	 * @param file_path audio file path name
	// 	*/
	// 	AudioMetaData GetInfo(const std::string &file_path);
	// };

} // end wwist::wav


#endif // LOADER_WAV_INCLUDE