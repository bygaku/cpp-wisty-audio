#ifndef WAV_LOADER_INCLUDE
#define WAV_LOADER_INCLUDE

#include "riff_reader.h"
#include "wave.h"
#include <chrono>

namespace wwist::wav {
	/**
	 *
	 */
	class WavLoader {
	public:
		explicit WavLoader(const char file_name[]);

		~WavLoader();

		// void GetMetaData();  // late


	private:
		bool Load(const char file_name[]);

	};

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

/**
 * @brief Loads a 16-bit PCM WAV file header and sample data (supports 44.1 kHz or 48 kHz).
 *
 * This function reads a WAV file from the specified file path and fills the given
 * `Wave` structure with format information and PCM data. It supports
 * only standard PCM (16-bit) mono and stereo WAV files.
 *
 * @param file_path Path to the WAV file to be loaded.
 * @param wav_data Pointer to a `wwist::wav::Wave` structure where the loaded data will be stored.
 * @return `true` if the WAV file was successfully loaded, otherwise `false`.
 *
 * @note
 * - Supported formats: 16-bit PCM, mono or stereo (44.1 kHz / 48 kHz).
 * - Unsupported formats (e.g., float PCM, etc.) will cause failure.
 * - The function allocates a temporary buffer internally for sample data.
 * - The caller does not need to free memory allocated inside `Wave`.
 *
 * @details
 * 1. Opens the WAV file using `RIFFReader`.
 * 2. Checks the RIFF and format chunks for PCM validity.
 * 3. Reads the "data" chunk and loads all PCM samples.
 * 4. Separates mono or stereo channels into `wav_header->data.ch`.
 *
 * Example usage:
 * @code
 * wwist::wav::Wave header;
 * if (!LoadWave("sound.wav", &header)) {
 *     // return false;
 * }
 * @endcode
 *
 * @remark change name wav_header to wav_data.
 */
inline bool LoadWave(const char file_path[], wwist::wav::Wave *wav_data) {
	using namespace wwist;
	using namespace wav;

	RIFFReader riff(file_path);
	if (riff.GetFileSize() == 0) return false;

	/** Standard PCM, mono or stereo. */
	if (riff.GetChunkSize(FMT_ID) != PCM) return false;
	if (!riff.GetChunkData(FMT_ID, &wav_data->fmt, PCM)) return false;

	/** dataChunk. */
	int data_size = static_cast<int>(riff.GetChunkSize(DATA_ID));
	if (!data_size) return false;

	// /** data size */
	// const int bytes			= wav_header->fmt.bit_depth / 8;	//  bytes per a sample. 16 pcm: 2 bytes, 32 pcm: 4 bytes;
	// const int total_samples	= data_size / bytes;				//	All samples, Data Size / a Sample Size.
	// auto*	  tmp_buff		= new short[total_samples];			//  Allocate buffer array for all samples.
	//
	// if (!riff.GetChunkData(DATA_ID, tmp_buff, data_size)) {
	// 	delete[] tmp_buff;
	// 	return false;
	// }
	//
	// const int ch_num = wav_header->fmt.channel_num;
	// /** monaural */
	// if (ch_num == 1) {
	// 	auto& mono = wav_header->data.ch[Channel::M];
	//
	// 	mono.clear();
	// 	mono.resize(total_samples);
	//
	// 	for (int i = 0; i < total_samples; ++i) {
	// 		mono[i] = tmp_buff[i];
	// 	}
	// }
	// /** stereo */
	// else if (ch_num == 2) {
	// 	const int frames = total_samples / ch_num;
	// 	auto& left  = wav_header->data.ch[Channel::L];
	// 	auto& right = wav_header->data.ch[Channel::R];
	//
	// 	left.clear();
	// 	right.clear();
	// 	left.resize(frames);
	// 	right.resize(frames);
	//
	// 	for (int i = 0; i < frames; i++) {
	// 		left[i]  = (tmp_buff[i * ch_num]);
	// 		right[i] = (tmp_buff[i * ch_num + 1]);
	// 	}
	// }
	//
	// delete[] tmp_buff;
	return true;
};
#endif // WAV_LOADER_INCLUDE
