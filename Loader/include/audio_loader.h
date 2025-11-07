#ifndef AUDIO_LOADER_INCLUDE
#define AUDIO_LOADER_INCLUDE
#include "singleton.h"
//#include "wav_fmt.h"

	// namespace wwist {
	//
	// 	class IAudioLoader : public Singleton<IAudioLoader> {
	// 	public:
	//
	// 		/**
	// 		 * @brief start loading from file_path
	// 		 * @param file_path audio file path name
	// 		 * @return true: completion
	// 		 */
	// 		virtual bool Load(const std::string& file_path) abstract;
	//
	// 		/**
	// 		 * @brief delete loaded file from file_path.
	// 		 * @param file_path audio file path name
	// 		 * @return true: completion
	// 		 */
	// 		virtual bool Delete(const std::string& file_path) abstract;
	//
	// 		/**
	// 		 * @brief get audio file information
	// 		 * @param file_path audio file path name
	// 		 * @return Audio file information
	// 		 */
	// 		virtual AudioMetaData GetInfo(const std::string& file_path) abstract;
	//
	// 	private:
	// 		IAudioLoader()			= default;
	// 		virtual ~IAudioLoader() = default;
	//
	// 		friend class Singleton<IAudioLoader>;
	//
	// 		/** Audio Info */
	// 		struct Audio {
	// 		};
	//
	// 	};
	// }


#endif // AUDIO_LOADER_INCLUDE