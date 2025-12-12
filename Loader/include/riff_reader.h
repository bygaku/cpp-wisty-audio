#ifndef RIFF_READER_INCLUDE
#define RIFF_READER_INCLUDE

#include <map>
#include <vector>
#include <fstream>
#include "riff_fmt.h"

namespace wwist {
	/**
	 * @class RIFFReader
	 * @brief Provides read access to RIFF (Resource Interchange File Format) files.
	 *
	 * Opens a RIFF file and provides methods to query chunks by ID,
	 * including their count, size, and raw data.
	 *
	 * @code
	 *	RIFFReader ri( "test.wav" ); // file open and read.
	 * @endcode
	 */
	class RIFFReader {
	public:
		/**
	 	 * @brief Constructs a RIFFReader and opens the specified file.
	 	 *
	 	 * @param file_path Path to the RIFF file.
		 * @param is_big_endian Set to true if the file data should be interpreted
		 *                      as big-endian. Defaults to little-endian (false).
	 	 */
		explicit RIFFReader(const char file_path[], const bool is_big_endian = false)
			: file_size_(0x00)
			, is_big_endian_(is_big_endian) {
			Open(file_path);
		}

		/**
		 * @brief Destructor.
		 */
		~RIFFReader() = default;

		/**
		 * @brief Returns the total size of the file in bytes.
		 * @return File size in bytes.
		 */
		[[nodiscard]] MY_DWORD GetFileSize() const { return file_size_; }

		/**
	 	 * @brief Returns the number of chunks with the given ID.
	 	 *
	 	 * @param chunk_id Chunk identifier.
	 	 * @return Number of chunks that match the given ID.
	 	 */
		[[nodiscard]] MY_DWORD GetChunkNum (CHUNK_ID chunk_id													);

		/**
		 * @brief Returns the size of a specific chunk.
		 *
		 * @param chunk_id Chunk identifier.
		 * @param id Zero-based index of the chunk with the given ID (default is 0).
		 * @return Size of the chunk in bytes.
		 */
		[[nodiscard]] MY_DWORD GetChunkSize(CHUNK_ID chunk_id,									MY_DWORD id = 0	);

		/**
	 	 * @brief Reads the data of a specific chunk into the provided buffer.
	 	 *
	 	 * @param chunk_id Chunk identifier.
	 	 * @param data Pointer to the destination buffer.
	 	 * @param data_size Size of the buffer in bytes (maximum number of bytes to read).
	 	 * @param id Zero-based index of the chunk with the given ID (default is 0).
	 	 * @return Number of bytes actually read.
	 	 */
		[[nodiscard]] MY_DWORD GetChunkData(CHUNK_ID chunk_id, void* data, MY_DWORD	data_size,	MY_DWORD id = 0	);

	private:
		/**
	 	　* @brief Opens the file and initializes internal state.
	 	　*
	 	　* This function is called by the constructor and should not be used directly
	 	　* by clients of the class.
	 	　*
	 	　* @param file_path Path to the RIFF file.
	 	　*/
		void Open(const char file_path[]);

	private:
		std::ifstream fp_;
		MY_DWORD 	  file_size_;
		bool	 	  is_big_endian_;

		std::map<CHUNK_ID, std::vector<MY_DWORD>> chunk_map_;
	};
}

#endif // RIFF_READER_INCLUDE