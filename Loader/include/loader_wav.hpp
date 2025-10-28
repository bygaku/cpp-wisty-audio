#ifndef __WAV_LOADER_H__
#define __WAV_LOADER_H__

#include "audio_fmt.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace wwist {
	/* Wav Format Loader */
	class LoaderWav {
	private:
		struct Sound {

		};

	public:
		~LoaderWav() {};

		/** @brief Start loading from file_path
		 *  @param file_path audio file path name
		 *  @return true
		 */
		int Load(const std::string& file_path);

		/** @brief get audio file information
		 *  @param file_path audio file path name
		 *  @return Audio file information
		 */
		AudioInfo GetInfo(const std::string& file_path);



	};

	// end wwist
}


#endif // __WAV_LOADER_H__