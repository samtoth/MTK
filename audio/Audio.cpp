//
// Created by sammy on 04/05/2020.
//

#include <Audio.h>

#include <utility>

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

	std::unique_ptr<AudioSystem> AudioSystem::instanceSystem;
    std::once_flag AudioSystem::aSInitFlag;
}