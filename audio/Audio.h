//
// Created by samt on 03/05/2020.
//

#ifndef MUSICTOOLKIT_AUDIO_H
#define MUSICTOOLKIT_AUDIO_H

#include <portaudio.h>
#include <cstdint>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include "IAudioUnit.h"
#include "IAudioAPI.h"
#include <iostream>
/// Collection of functions for configuring audio output
    namespace MTK::Audio {

#define printErr(em) printf("PortAudio error: %s\n", Pa_GetErrorText(em)) //TODO: throw error


        template<typename T>
        int initialize() {
            setInstance();
        }

        namespace {
            void setInstance(std::unique_ptr<Audio::IAudioAPI> aApi);
        }

        int terminate();

        int setup(AudioSettings settings);

        int deviceCount();

        std::optional<const PaDeviceInfo *> getDeviceInfo(int i);

        int printDevices();

        int startStream();

        int stopStream();

        void setGenerator(IAudioUnit *generator);

        IAudioUnit *generator();

        AudioSettings getAudioSettings();

        uint64_t delta();
    }
}

#endif //MUSICTOOLKIT_AUDIO_H