#ifndef LOADER_WAV_INCLUDE
#define LOADER_WAV_INCLUDE

#include "wav_fmt.h"
#include "riff_reader.h"

namespace wwist::wav {

	struct MyWAVEHEADER {
		MY_WORD  format_id;
		MY_WORD  channel_num;
		MY_DWORD sample_rate;
		MY_DWORD data_rate;
		MY_WORD  block_size;
		MY_WORD  bit_rate;
	};

	/**
	 * @brief read a wav file.
	 * @param file_name
	 * @param wav_l
	 * @param wav_r
	 * @param channel_num
	 * @param sample_rate
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

		MyWAVEHEADER myWH{};
		if (riff_reader.GetChunkSize(FMT_ID) != 16) return false;
		if (riff_reader.GetChunkData(FMT_ID, &myWH, 16) == 0) return false;

		if (myWH.sample_rate != 44100							) return false;
		if (myWH.bit_rate	 != 16								) return false;
		if (myWH.channel_num != 1		&& myWH.channel_num != 2) return false;

		(*sample_rate) = static_cast<int>(myWH.sample_rate);
		(*channel_num) = static_cast<short>(myWH.channel_num);

		int data_size = static_cast<int>(riff_reader.GetChunkSize(DATA_ID));
		if (data_size == 0) return false;

		int		bytes	= myWH.bit_rate / 8;
		auto*	tmp_buf = new short[data_size / bytes];

		if (riff_reader.GetChunkData(DATA_ID, tmp_buf, data_size) == 0) {
			delete[] tmp_buf;
			return false;
		}

		wav_l->clear();
		wav_r->clear();

		int loops = (data_size / bytes) / myWH.channel_num;
		for (int i = 0; i < loops; i++) {
			if (myWH.channel_num == 1) {
				wav_l->push_back(tmp_buf[i]);
				wav_r->push_back(tmp_buf[i]);
			}
			else {
				wav_l->push_back(tmp_buf[i * myWH.channel_num]);
				wav_r->push_back(tmp_buf[i * myWH.channel_num + 1]);
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