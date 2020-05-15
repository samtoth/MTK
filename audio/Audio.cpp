//
// Created by sammy on 04/05/2020.
//

#include <Audio.h>

namespace MTK::Audio {
    std::unique_ptr<IAudioAPI> audioInstance;
    std::once_flag initFlag;
    std::mutex audioInstanceMutex;
    std::once_flag delFlag;


#define LOCK_AUDIO const std::lock_guard<std::mutex> lock(audioInstanceMutex)

    int terminate(){
        auto err = audioInstance->terminate();
        if(err==0) {
            std::call_once(delFlag, []() {
                delete audioInstance.release();
            });
            return 0;
        }else{
            return err;
        }
    }

    int setup(AudioSettings settings){
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

    AudioSettings getAudioSettings(){
        LOCK_AUDIO;
        return audioInstance->devSettings;
    }

    uint64_t delta(){
        LOCK_AUDIO;
        return audioInstance->delta;
    }


    void setInstance(std::unique_ptr<IAudioAPI> aApi){
        auto *api = aApi.release();
        std::call_once(initFlag, [api](){ audioInstance = std::unique_ptr<IAudioAPI>(api);});
   }
}