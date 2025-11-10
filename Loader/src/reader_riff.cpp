#include <fstream>
#include <iostream>
#include "wav_fmt.h"
#include "reader_riff.h"


void wwist::RIFFReader::Open(char file_path[])
{
	auto e = fopen_s(&fp_, file_path, "rb");
	if (e != 0) {
		printf("fopen_s failed: errno = %d, message = %s\n", e, strerror(e));
		return;
	}
	//if (e) return;
	if (fp_ == nullptr) {
		return;
	}

	struct stat f_stat{};
	if (fstat(_fileno(fp_), &f_stat) == 0) {
		file_size_ = f_stat.st_size;
	}

	while (static_cast<MY_DWORD>(ftell(fp_)) < file_size_) {	// reading a file sequentially.
		MY_DWORD chunk_ID;
		fread(&chunk_ID, sizeof(CHUNK_ID), 1, fp_);

		MY_DWORD chunk_size;
		fread(&chunk_size, sizeof(MY_DWORD), 1, fp_);
		if (is_big_endian_) {
			Swap32Bit(chunk_size);
		}

		switch (chunk_ID) {
			case RIFF_ID:
			case LIST_ID:
				// データ部分の最初 4byte(チャンクタイプ)をスキップ
				// 残りのデータ部分はサブチャンクなので最初 4byteのみとする
				fseek(fp_, sizeof(MY_DWORD), SEEK_CUR);

				break;
			default:
				// ファイルポインタの位置を保存しておく
				// (該当するチャンクのサイズの位置)
				chunk_map_[chunk_ID].push_back(static_cast<MY_DWORD>(ftell(fp_)) - sizeof(MY_DWORD));

				// データ部分はスキップする
				fseek(fp_, chunk_size, SEEK_CUR);

				break;
		}
	}

}

wwist::MY_DWORD wwist::RIFFReader::GetChunkNum(CHUNK_ID chunk_id)
{
	if (chunk_map_.count(chunk_id) == 0) {
		return 0;
	}

	return chunk_map_[chunk_id].size();
}

wwist::MY_DWORD wwist::RIFFReader::GetChunkSize(CHUNK_ID chunk_id, MY_DWORD id)
{
	if (chunk_map_.count(chunk_id) == 0) { return 0; }
	if (chunk_map_[chunk_id].size() <= id) { return 0; }

	// ファイルポインタの位置をチャンクの場所まで進めて読み込み
	MY_DWORD size = 0;
	fseek(fp_, chunk_map_[chunk_id][id], SEEK_SET);
	fread(&size, sizeof(MY_DWORD), 1, fp_);

	if (is_big_endian_) {
		Swap32Bit(size);
	} // エンディアンの変換

	return size;
}

wwist::MY_DWORD wwist::RIFFReader::GetChunkData(CHUNK_ID chunk_id, void* data, MY_DWORD data_size, MY_DWORD id)
{
	if (chunk_map_.count(chunk_id) == 0) {	return 0; }
	if (chunk_map_[chunk_id].size() <= id) { return 0; }

	// ファイルポインタの位置をチャンクの場所まで進めて読み込み
	MY_DWORD size = 0;
	fseek(fp_, chunk_map_[chunk_id][id], SEEK_SET);
	fread(&size, sizeof(MY_DWORD), 1, fp_);

	if (is_big_endian_) {
		Swap32Bit(size);
	} // エンディアンの変換

	size = (data_size > size) ? (size) : (data_size);

	fread(data, size, 1, fp_);

	return 1;
}