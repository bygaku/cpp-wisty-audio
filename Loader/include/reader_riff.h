#ifndef READER_RIFF_INCLUDE
#define READER_RIFF_INCLUDE

#include <map>

namespace wwist {
	/** @brief open and read riff chunk of file.
	 *
	 *	@code
	 *		RIFFReader ri( "test.wav" ); // open file
	 *	@endcode
	 */
	class RIFFReader {
	public:
		explicit RIFFReader(char file_path[], const bool is_big_endian = false)
			: fp_(nullptr)
			, is_big_endian_(is_big_endian)
			, file_size_(0x00) {
			Open(file_path);
		}

		~RIFFReader() {
			if (fp_) fclose(fp_);
		}

		[[nodiscard]] MY_DWORD GetFileSize() const { return file_size_; }

		[[nodiscard]] MY_DWORD GetChunkNum (CHUNK_ID chunk_id													);
		[[nodiscard]] MY_DWORD GetChunkSize(CHUNK_ID chunk_id,									MY_DWORD id = 0	);
		[[nodiscard]] MY_DWORD GetChunkData(CHUNK_ID chunk_id, void* data, MY_DWORD	data_size,	MY_DWORD id = 0	);

	private:
		void Open(char file_path[]);

	private:
		FILE*	 fp_;
		bool	 is_big_endian_;
		MY_DWORD file_size_;

		std::map<CHUNK_ID, std::vector<MY_DWORD>> chunk_map_;
	};
}

#endif // READER_RIFF_INCLUDE