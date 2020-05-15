//
// Created by sammy on 14/05/2020.
//

#include <Audio.h>
#include "PortAudioWrapper.h"

namespace MTK::Audio {
    PortAudioWrapper::PortAudioWrapper() {
        auto err = Pa_Initialize();
        if (err != paNoError) {
            printErr(err);
        }
    }

    int PortAudioWrapper::setup(AudioSettings settings) {

        devSettings = settings;

        /* Open an audio I/O stream. */
        auto err = Pa_OpenDefaultStream(&stream,
                                        0,          /* no input channels */
                                        1,          /* stereo output FOR NOW */
                                        paFloat32,  /* 32 bit floating point output */
                                        devSettings.sampleRate,
                                        devSettings.bufferSize,        /* frames per buffer, i.e. the number
                                           of sample frames that PortAudio will
                                           request from the callback. Many apps
                                           may want to use
                                           paFramesPerBufferUnspecified, which
                                           tells PortAudio to pick the best,
                                           possibly changing, buffer size.*/
                                        callback, /* this is your callback function */
                                        this); /*This is a pointer that will be passed to
                                           your callback*/
        if (err != paNoError) {
            printErr(err);
            return err;
        }

        return 0;
    }

    int PortAudioWrapper::startStream() {
        //TODO: Assert callback function is set
        auto err = Pa_StartStream(stream);
        if (err != paNoError) {
            printErr(err);
            return err;
        }
        return 0;
    }

    int PortAudioWrapper::stopStream() {
        auto err = Pa_StopStream(stream);
        if (err != paNoError) {
            printErr(err);
            return err;
        }
        return 0;
    }

    int PortAudioWrapper::terminate() {
        auto err = Pa_CloseStream(stream);
        if (err != paNoError) {
            printErr(err);
            return err;
        }

        err = Pa_Terminate();
        if (err != paNoError) {
            printErr(err);
            return err;
        }
        return 0;
    }

    int PortAudioWrapper::callback(const void *inputBuffer, void *outputBuffer,
                                          unsigned long framesPerBuffer,
                                          const PaStreamCallbackTimeInfo *timeInfo,
                                          PaStreamCallbackFlags statusFlags,
                                          void *userData) {
        auto *out = (float *) outputBuffer;
        unsigned int i;
        (void) inputBuffer; /* Prevent unused variable warning. */

        auto *audioOutput = (PortAudioWrapper *) userData;

        for (i = 0; i < framesPerBuffer; i++) {
            *out++ = audioOutput->generator->output();
            audioOutput->delta++;
        }
        return 0;
    }
}