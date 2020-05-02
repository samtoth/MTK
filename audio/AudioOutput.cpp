
#include <cstdio>
#include <iostream>
#include "AudioOutput.h"

#define printErr(em) printf("PortAudio error: %s\n", Pa_GetErrorText(em))

AudioOutput::AudioOutput() {
    auto err = Pa_Initialize();
    if( err != paNoError ) {
        printErr(err);
    }
}

int AudioOutput::initialize(deviceSettings settings) {
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

int AudioOutput::terminate() {
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


int AudioOutput::callback(const void *inputBuffer, void *outputBuffer,
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
        *out++ = audioOutput->generator->output((audioOutput->counter+i)*(1000/audioOutput->devSettings.sampleRate));
    }
    audioOutput->counter += framesPerBuffer;
    return 0;
}

int AudioOutput::startStream() {
    //TODO: Assert callback function is set
    auto err = Pa_StartStream(stream);
    if(err!= paNoError){printErr(err); return 1;}
    return 0;
}

int AudioOutput::stopStream() {
    auto err = Pa_StopStream(stream);
    if(err!= paNoError){printErr(err); return 1;}
    return 0;
}

int AudioOutput::deviceCount() {
    int numDevices;
    numDevices = Pa_GetDeviceCount();
    if(numDevices<0){
        printErr(numDevices);
        return 0;
    }
    return numDevices;
}


std::optional<const PaDeviceInfo*> AudioOutput::getDeviceInfo(int i) {
    auto n = deviceCount();
    if(i<0 || i>n){return std::nullopt;}
    return Pa_GetDeviceInfo(i);
}

int AudioOutput::printDevices() {
    auto n = deviceCount();
    for(int i = 0; i<n; i++){
        std::cout << getDeviceInfo(i).value()->name << std::endl;
    }
    return 0;
}





