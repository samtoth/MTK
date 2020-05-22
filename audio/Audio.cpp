//
// Created by sammy on 04/05/2020.
//

#include <Audio.h>

#include <utility>
#define LOCK_AUDIO const std::lock_guard<std::mutex> lock(audioInstanceMutex)

namespace MTK::Audio {

    int AudioSystem::terminate(){
        auto err = audioInstance->terminate();
        if(err==0) {
            std::call_once(delFlag, [this]() {
                audioInstance = nullptr;
            });
            return 0;
        }else{
            return err;
        }
    }

    int AudioSystem::setup(AudioSettings settings){
        return audioInstance->setup(settings);
    }

#ifndef TARGET_WEB
    int AudioSystem::deviceCount(){
        int numDevices;
        numDevices = Pa_GetDeviceCount();
        if(numDevices<0){
            printErr(numDevices);
            return 0;
        }
        return numDevices;
    }
    std::optional<const PaDeviceInfo*> AudioSystem::getDeviceInfo(int i){
        auto n = deviceCount();
        if(i<0 || i>n){return std::nullopt;}
        return Pa_GetDeviceInfo(i);
    }

    int AudioSystem::printDevices(){
        auto n = deviceCount();
        for(int i = 0; i<n; i++){
            std::cout << getDeviceInfo(i).value()->name << std::endl;
        }
        return 0;
    }
#endif

    int AudioSystem::startStream(){
        return audioInstance->startStream();
    }

    int AudioSystem::stopStream(){
        return audioInstance->stopStream();
    }

    void AudioSystem::setGenerator(std::shared_ptr<IAudioUnit> generator){
        audioInstance->generator = std::move(generator);
    }

    std::shared_ptr<IAudioUnit> AudioSystem::generator(){
        return audioInstance->generator;
    }

    AudioSettings AudioSystem::getAudioSettings(){
        return audioInstance->devSettings;
    }

    uint64_t AudioSystem::delta(){
        return audioInstance->delta;
    }
	std::optional<AudioSampleBuffer<float>*> AudioSystem::getTestBuffer() {
		try {
			IAudioWrapper* tempBase = audioInstance.get();
			auto* tempDerived = dynamic_cast<MockAudioWrapper*>(tempBase);
			return tempDerived->getBuffer();
		}catch (std::exception &e){
			return std::nullopt;
		}
	}

	std::unique_ptr<AudioSystem> AudioSystem::instanceSystem;
    std::once_flag AudioSystem::aSInitFlag;
}