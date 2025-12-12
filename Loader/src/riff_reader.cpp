#include <iostream>
#include "riff_reader.h"

namespace {
	using namespace wwist;
}

void RIFFReader::Open(const char file_path[]) {
	fp_.open(file_path, std::ios::binary);
	if (!fp_) {
		std::cerr << "open failed\n";
		return;
	}

	// Get a file size.
	fp_.seekg(0, std::ios::end);
	file_size_ = static_cast<MY_DWORD>(fp_.tellg());
	fp_.seekg(0, std::ios::beg);

	while (static_cast<MY_DWORD>(fp_.tellg()) < file_size_) {
		// Reading a file sequentially.
		MY_DWORD chunk_ID {};
		fp_.read(reinterpret_cast<char*>(&chunk_ID), sizeof(CHUNK_ID));

		MY_DWORD chunk_size {};
		fp_.read(reinterpret_cast<char*>(&chunk_size), sizeof(MY_DWORD));
		if (is_big_endian_) {
			Swap32Bit(chunk_size);
		}

		switch (chunk_ID) {
			case RIFF_ID:
			case LIST_ID:
				// Skip the first 4 bytes of the data section (chunk type).
				// Since the remaining data consists of subchunks, only the first 4 bytes are used.
				fp_.seekg(sizeof(MY_DWORD), std::ios::cur);
				break;
			default:
				// Save the current position (right after the size field)
				auto pos = fp_.tellg();
				chunk_map_[chunk_ID].push_back(
					static_cast<MY_DWORD>(pos) - sizeof(MY_DWORD)
				);

				// Skip the data section
				fp_.seekg(chunk_size, std::ios::cur);
				break;
		}
	}
}

MY_DWORD RIFFReader::GetChunkNum(CHUNK_ID chunk_id) {
	if (!chunk_map_.contains(chunk_id)) {
		return 0;
	}

	return chunk_map_[chunk_id].size();
}

MY_DWORD RIFFReader::GetChunkSize(CHUNK_ID chunk_id, MY_DWORD id) {
	if (!chunk_map_.contains(chunk_id)) return 0;
	if (chunk_map_[chunk_id].size() <= id) return 0;

	// Advance the file pointer to the chunk location and read
	MY_DWORD size = 0;
	fp_.clear();
	fp_.seekg(static_cast<std::streamoff>(chunk_map_[chunk_id][id]), std::ios::beg);
	fp_.read(reinterpret_cast<char*>(&size), sizeof(MY_DWORD));

	if (is_big_endian_) {
		Swap32Bit(size);
	}	// Endianness conversion process

	return size;
}

MY_DWORD RIFFReader::GetChunkData(CHUNK_ID chunk_id, void *data, MY_DWORD data_size, MY_DWORD id) {
	if (!chunk_map_.contains(chunk_id)) return 0;
	if (chunk_map_[chunk_id].size() <= id) return 0;

	// Advance the file pointer to the chunk location and read
	MY_DWORD size = 0;
	fp_.seekg(static_cast<std::streamoff>(chunk_map_[chunk_id][id]), std::ios::beg);
	fp_.read(reinterpret_cast<char*>(&size), sizeof(MY_DWORD));

	if (is_big_endian_) {
		Swap32Bit(size);
	}	// Endianness conversion process

	auto read_size = (data_size > size) ? size : data_size;
	fp_.read(static_cast<char*>(data), read_size);

	return read_size;
}
