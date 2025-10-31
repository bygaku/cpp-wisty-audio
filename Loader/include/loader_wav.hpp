#ifndef __WAV_LOADER_H__
#define __WAV_LOADER_H__

#include "audio_fmt.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "audio_loader.h"


namespace wwist {

	namespace wav {
		/* Wav Format Loader */
		class LoaderWav : public IAudioLoader {
		public:
			~LoaderWav() override {};

			/** @brief Start loading from file_path
			 *  @param file_path audio file path name
			 *  @return true
			 */
			bool Load(const std::string& file_path) override;


			bool Delete(const std::string& file_path) override;
			/** @brief get audio file information
			 *  @param file_path audio file path name
			 *  @return Audio file information
			 */
			AudioMetaData GetInfo(const std::string& file_path) override;

		private:
			/* temporary data */
			struct Sound {

			};

		};

		// end wav
	}

	// end wwist
}


#endif // __WAV_LOADER_H__