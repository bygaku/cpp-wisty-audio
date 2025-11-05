#ifndef __AUDIO_BUFFER_H__
#define __AUDIO_BUFFER_H__
#include <memory>
#include <cassert>
#include <vector>

namespace wwist {

	class AudioBuffer {
	public:
		AudioBuffer() = default;
		AudioBuffer(size_t channels, size_t samples)
			: num_channels_(channels)
			, num_samples_(samples) {
			data_ = std::make_unique<float[]>(channels * samples);
			std::fill_n(data_.get(), channels * samples, 0.0f);
		}

		// インターリーブデータアクセス
		float& At(size_t channel, size_t sample) {
			assert(channel < num_channels_ && sample < num_samples_);
			return data_[sample * num_channels_ + channel];
		}

		const float& At(size_t channel, size_t sample) const {
			assert(channel < num_channels_ && sample < num_samples_);
			return data_[sample * num_channels_ + channel];
		}

		std::vector<float> GetChannel(size_t channel) const {
			assert(channel < num_channels_);
			std::vector<float> channel_data(num_samples_);

			for (size_t i = 0; i < num_samples_; ++i) {
				channel_data[i] = At(channel, i);
			}

			return channel_data;
		}

		// メタデータ
		size_t GetNumChannels() const { return num_channels_; }
		size_t GetNumSamples() const { return num_samples_; }
		size_t GetTotalSamples() const { return num_channels_ * num_samples_; }

		// 生データアクセス（パフォーマンス最適化用）
		float* Data() { return data_.get(); }
		const float* Data() const { return data_.get(); }

	private:
		std::unique_ptr<float[]> data_;
		size_t num_channels_	= 0;
		size_t num_samples_		= 0;

	};


}


#endif //__AUDIO_BUFFER_H__