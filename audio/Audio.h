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

namespace audio{

    /// \brief data structure for setting up output device
    struct audioSettings{
        int outputChannels;
        double sampleRate;
        int bufferSize; //!< bufferSize in ms. set to 0 to autocalculate optimum bufferSize
    };

    #define printErr(em) printf("PortAudio error: %s\n", Pa_GetErrorText(em))

    class AudioOutput {
    public:

        AudioOutput(){
            auto err = Pa_Initialize();
            if( err != paNoError ) {
                printErr(err);
            }
        }

        uint64_t delta = 0;

        virtual ~AudioOutput() = default;

        int setup(audioSettings settings){
            int framesPerBuffer;
            if(settings.bufferSize==0){
                framesPerBuffer = paFramesPerBufferUnspecified;
            }else {
                framesPerBuffer = 1000 / settings.bufferSize;
            }

            devSettings = settings;

            /* Open an audio I/O stream. */
            auto err = Pa_OpenDefaultStream( &stream,
                                             0,          /* no input channels */
                                             1,          /* stereo output FOR NOW */
                                             paFloat32,  /* 32 bit floating point output */
                                             devSettings.sampleRate,
                                             framesPerBuffer,        /* frames per buffer, i.e. the number
                                               of sample frames that PortAudio will
                                               request from the callback. Many apps
                                               may want to use
                                               paFramesPerBufferUnspecified, which
                                               tells PortAudio to pick the best,
                                               possibly changing, buffer size.*/
                                             callback, /* this is your callback function */
                                             this ); /*This is a pointer that will be passed to
                                               your callback*/
            if( err != paNoError ) {printErr(err); return err;}

            return 0;
        }

        int terminate(){
            auto err = Pa_IsStreamStopped(stream);
            //if not stopped: stop it
            if(err == 0) {
                auto err = Pa_CloseStream(stream);
                if (err != paNoError) {
                    printErr(err);
                    return err;
                }
            }

            err = Pa_Terminate();
            if( err != paNoError ) {
                printErr(err);
                return err;
            }
            return 0;
        }

        int startStream() {
            //TODO: Assert callback function is set
            auto err = Pa_StartStream(stream);
            if(err!= paNoError){printErr(err); return 1;}
            return 0;
        }

        int stopStream(){
            auto err = Pa_StopStream(stream);
            if(err!= paNoError){printErr(err); return 1;}
            return 0;
        }





        audioSettings devSettings;
        IAudioUnit *generator;

    private:
        PaStream *stream;


        static int callback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData ) {
            auto *out = (float*)outputBuffer;
            unsigned int i;
            (void) inputBuffer; /* Prevent unused variable warning. */

            auto *audioOutput = (AudioOutput*)userData;

            for( i=0; i<framesPerBuffer; i++ )
            {
                *out++ = audioOutput->generator->output();
                audioOutput->delta++;
            }
            return 0;
        }

    };

    inline std::unique_ptr<AudioOutput> audioInstance;
    inline std::once_flag initFlag;
    inline std::once_flag delFlag;

    inline void initialize(){
        std::call_once(initFlag, [](){ audioInstance = std::make_unique<AudioOutput>();});
    }

    inline void terminate(){
        std::call_once(delFlag, [](){
            auto err = audioInstance->terminate();
            if(err!=paNoError){
                throw std::runtime_error("terminate failed");
            }
            audioInstance.release();
        });
    }

    inline int setup(audioSettings settings){
        return audioInstance->setup(settings);
    }

    inline int deviceCount(){
        int numDevices;
        numDevices = Pa_GetDeviceCount();
        if(numDevices<0){
            printErr(numDevices);
            return 0;
        }
        return numDevices;
    }

    inline std::optional<const PaDeviceInfo*> getDeviceInfo(int i){
        auto n = deviceCount();
        if(i<0 || i>n){return std::nullopt;}
        return Pa_GetDeviceInfo(i);
    }

    inline int printDevices(){
        auto n = deviceCount();
        for(int i = 0; i<n; i++){
            std::cout << getDeviceInfo(i).value()->name << std::endl;
        }
        return 0;
    }

    inline int startStream(){
        return audioInstance->startStream();
    }

    inline int stopStream(){
        return audioInstance->stopStream();
    }

    inline void setGenerator(IAudioUnit* generator){
        audioInstance->generator = generator;
    }

    inline IAudioUnit *generator(){
        return audioInstance->generator;
    }

    inline audioSettings audioSettings(){
        return audioInstance->devSettings;
    }

    inline uint64_t delta(){
        return audioInstance->delta;
    }
}

#endif //MUSICTOOLKIT_AUDIO_H
