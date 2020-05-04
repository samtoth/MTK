//
// Created by sammy on 04/05/2020.
//

#include <Audio.h>

namespace audio {

    std::unique_ptr<AudioOutput> audioInstance;
    std::mutex audioInstanceMutex;
    std::once_flag initFlag;
    std::once_flag delFlag;



#define LOCK_AUDIO const std::lock_guard<std::mutex> lock(audioInstanceMutex)

    void initialize(){
        std::call_once(initFlag, [](){ audioInstance = std::make_unique<AudioOutput>();});
    }

    void terminate(){
        LOCK_AUDIO;
        std::call_once(delFlag, [](){
            audioInstance.release();
        });
    }

    int setup(audioSettings settings){
        return audioInstance->setup(settings);
    }

    int deviceCount(){
        int numDevices;
        numDevices = Pa_GetDeviceCount();
        if(numDevices<0){
            printErr(numDevices);
            return 0;
        }
        return numDevices;
    }

    std::optional<const PaDeviceInfo*> getDeviceInfo(int i){
        auto n = deviceCount();
        if(i<0 || i>n){return std::nullopt;}
        return Pa_GetDeviceInfo(i);
    }

    int printDevices(){
        auto n = deviceCount();
        for(int i = 0; i<n; i++){
            std::cout << getDeviceInfo(i).value()->name << std::endl;
        }
        return 0;
    }

    int startStream(){
        LOCK_AUDIO;
        return audioInstance->startStream();
    }

    int stopStream(){
        LOCK_AUDIO;
        return audioInstance->stopStream();
    }

    void setGenerator(IAudioUnit* generator){
        LOCK_AUDIO;
        audioInstance->generator = generator;
    }

    IAudioUnit *generator(){
        LOCK_AUDIO;
        return audioInstance->generator;
    }

    audioSettings getAudioSettings(){
        LOCK_AUDIO;
        return audioInstance->devSettings;
    }

    uint64_t delta(){
        LOCK_AUDIO;
        return audioInstance->delta;
    }

}