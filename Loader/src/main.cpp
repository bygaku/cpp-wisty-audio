#include <iostream>
#include "loader_wav.h"

int main() {
	using namespace wwist;

	char file_path[] = "C:/Workspace/DevAudio/WistyAudio/Loader/resource/intuition.wav";
	char file_pat[]  = "C:/Workspace/DevAudio/WistyAudio/Loader/resource/wood.wav";
	wav::BUFF_WAV buf_l;
	wav::BUFF_WAV buf_r;

	short	channels	= 0;
	int		sample_rate = 0;

	wav::ReadWavFile(file_path, &buf_l, &buf_r, &channels, &sample_rate);

	std::vector<float> wav_l_float;
	std::vector<float> wav_r_float;

	for (int i = 0; i < buf_l.size(); i++) {
		wav_l_float.push_back(static_cast<float>(buf_l[i]) / static_cast<float>(SHRT_MAX));
		wav_r_float.push_back(static_cast<float>(buf_r[i]) / static_cast<float>(SHRT_MAX));
	}

	printf("WAV file name: %s\n",			reinterpret_cast<char *>(file_path));
	printf("WAV file size: %d\n",			static_cast<int>(buf_l.size()));
	printf("WAV file size: %d\n",			static_cast<int>(buf_r.size()));
	printf("WAV file channels: %d\n",		channels);
	printf("WAV file sample rate: %d\n",	sample_rate);

	return 0;
}