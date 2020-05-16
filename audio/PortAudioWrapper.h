//
// Created by sammy on 14/05/2020.
//

#ifndef MUSICTOOLKIT_PORTAUDIOWRAPPER_H
#define MUSICTOOLKIT_PORTAUDIOWRAPPER_H

#include <portaudio.h>
#include <cstdint>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <iostream>
#include "IAudioUnit.h"
#include "Audio.h"
#include "IAudioWrapper.h"

namespace MTK::Audio {
    class PortAudioWrapper : public IAudioWrapper{

        PaStream *stream;

        static int callback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData );

    public:
        PortAudioWrapper();

        int setup(AudioSettings settings) override;
        ~PortAudioWrapper();

        int startStream() override;

        int stopStream() override;

        int terminate() override;
    };

}


#endif //MUSICTOOLKIT_PORTAUDIOWRAPPER_H
