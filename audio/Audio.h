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
#include <iostream>

/// Collection of functions for configuring audio output
namespace audio{



    /// \brief data structure for setting up output device
    struct audioSettings{
        int outputChannels;
        double sampleRate;
        int bufferSize; //!< bufferSize in ms. set to 0 to autocalculate optimum bufferSize
    };

#define USE_PORTAUDIO
#ifdef USE_PORTAUDIO
    #define printErr(em) printf("PortAudio error: %s\n", Pa_GetErrorText(em)) //TODO: throw error

    class AudioOutput {
    public:

        AudioOutput();

        uint64_t delta = 0;

        ~AudioOutput() = default;

        int setup(audioSettings settings);

        int startStream();

        int stopStream();

        int terminate() ;

        audioSettings devSettings;
        IAudioUnit *generator;

    private:
        PaStream *stream;


        static int callback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData );
    };
#else
#endif


    int initialize();
    int terminate();
    int setup(audioSettings settings);
    int deviceCount();
    std::optional<const PaDeviceInfo*> getDeviceInfo(int i);
    int printDevices();
    int startStream();
    int stopStream();
    void setGenerator(IAudioUnit* generator);
    IAudioUnit *generator();
    audioSettings getAudioSettings();
    uint64_t delta();

    int abortStream();
}

#endif //MUSICTOOLKIT_AUDIO_H
