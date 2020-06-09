//
// Created by samt on 16/05/2020.
//

#include <AudioSampleBuffer.h>
#include <thread>
#include <iostream>
#include "MockAudioWrapper.h"

namespace MTK::Audio {

	int MockAudioWrapper::setup(AudioSettings settings) {
		devSettings = settings;
		run = false;
		if(devSettings.bufferSize==0){
			devSettings.bufferSize=devSettings.sampleRate/4.f;
		}
        buffer = std::make_unique<AudioSampleBuffer<float>>(devSettings.bufferSize);
		return 0;
	}

	int MockAudioWrapper::startStream() {
		run = true;
		bool *_run = &run;
		int interval = 1000*((float)devSettings.bufferSize/(float)devSettings.sampleRate);
		std::thread([this, interval, _run]() {
		  while (*_run) {
			  auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
			  this->tick();
			  std::this_thread::sleep_until(x);
		  }
		}).detach();
		return 0;
	}
	int MockAudioWrapper::stopStream() {
		run = false;
		return 0;
	}
	int MockAudioWrapper::terminate() {
		buffer = nullptr;
		return 0;
	}
	void MockAudioWrapper::tick() {
		for(int i = 0 ; i<devSettings.bufferSize; i++)
		{
			buffer->push(generator->output());
			delta ++;
		}
	}
	std::optional<AudioSampleBuffer<float>*> MockAudioWrapper::getBuffer() {
		if(!run)
		{
			return buffer.get();
		}else{
			std::cout << "Must stop stream before accessing buffer" << std::endl;
			return std::nullopt;
		}
	}
	AudioSampleBuffer<float> *MockAudioWrapper::generateBuffer() {
		this->tick();
		return buffer.get();
	}

}