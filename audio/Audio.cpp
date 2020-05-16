//
// Created by sammy on 04/05/2020.
//

#include <Audio.h>
#define LOCK_AUDIO const std::lock_guard<std::mutex> lock(audioInstanceMutex)

namespace MTK::Audio {

    int AudioSystem::terminate(){
        auto err = audioInstance->terminate();
        if(err==0) {
            std::call_once(delFlag, [this]() {
                delete audioInstance.release();
            });
            return 0;
        }else{
            return err;
        }
    }

    int AudioSystem::setup(AudioSettings settings){
        return audioInstance->setup(settings);
    }

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

    int AudioSystem::startStream(){
        LOCK_AUDIO;
        return audioInstance->startStream();
    }

    int AudioSystem::stopStream(){
        return audioInstance->stopStream();
    }

    void AudioSystem::setGenerator(IAudioUnit* generator){
        LOCK_AUDIO;
        audioInstance->generator = generator;
    }

    IAudioUnit *AudioSystem::generator(){
        LOCK_AUDIO;
        return audioInstance->generator;
    }

    AudioSettings AudioSystem::getAudioSettings(){
        LOCK_AUDIO;
        return audioInstance->devSettings;
    }

    uint64_t AudioSystem::delta(){
        LOCK_AUDIO;
        return audioInstance->delta;
    }


    std::atomic<AudioSystem*> AudioSystem::instance;
    std::mutex AudioSystem::instanceMutex;
}