//
// Created by samt on 16/05/2020.
//

#ifndef MUSICTOOLKIT_MOCKAUDIOWRAPPER_H
#define MUSICTOOLKIT_MOCKAUDIOWRAPPER_H

#include <stack>
#include <memory>
#include <AudioSampleBuffer.h>
#include <optional>
#include "IAudioWrapper.h"

namespace MTK::Audio {
	class MockAudioWrapper : public IAudioWrapper {
	public:
		int setup(AudioSettings settings) override;
		int startStream() override;
		int stopStream() override;
		std::optional<AudioSampleBuffer<float>*> getBuffer();
		int terminate() override;
		AudioSampleBuffer<float> *generateBuffer();
	private:
		std::unique_ptr<AudioSampleBuffer<float>> buffer;
		bool run;

		void tick();
	};
}
#endif //MUSICTOOLKIT_MOCKAUDIOWRAPPER_H