#pragma region Wav_Loading_Test
#include <iostream>
#include "wav_loader.h"
#include <chrono>

int main() {
	using namespace wwist;

	auto start = std::chrono::high_resolution_clock::now();

	char file_path[] = "C:/Workspace/DevAudio/WistyAudio/Loader/resource/intuition.wav";
	wav::BUFF_WAV buf_l;
	wav::BUFF_WAV buf_r;

	short	channels	= 0;
	int		sample_rate = 0;

	wav::Wave wave;
	if (!LoadWave(file_path, &wave)) {
		std::cerr << "LoadWavHeader ERROR!!" << std::endl;
		return 0;
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	std::cout << "processing time: " << time << std::endl;

	printf("WAV file name: %s nano_sec\n",	reinterpret_cast<char*>(file_path));
	printf("WAV file channels: %d\n",			wave.fmt.channel_num);
	printf("WAV file block size: %d\n",		wave.fmt.block_size);
	printf("WAV file sample rate: %d\n",		static_cast<int>(wave.fmt.sample_rate));
	// printf("WAV file size: %d\n",				static_cast<int>(wav_header.data.ch.at(wav::Channel::L).size()));
	// printf("WAV file size: %d\n",				static_cast<int>(wav_header.data.ch.at(wav::Channel::R).size()));

	return 0;
}
#pragma endregion
