//
// Created by sammy on 04/05/2020.
//

#include <Audio.h>

namespace audio {
    AudioOutput::AudioOutput(){
        auto err = Pa_Initialize();
        if( err != paNoError ) {
            printErr(err);
        }
    }


    int AudioOutput::setup(audioSettings settings){

        devSettings = settings;

        /* Open an audio I/O stream. */
        auto err = Pa_OpenDefaultStream( &stream,
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
                                         this ); /*This is a pointer that will be passed to
                                               your callback*/
        if( err != paNoError ) {printErr(err); return err;}

        return 0;
    }


    int AudioOutput::startStream() {
        //TODO: Assert callback function is set
        auto err = Pa_StartStream(stream);
        if(err!= paNoError){printErr(err); return err;}
        return 0;
    }

    int AudioOutput::stopStream(){
        auto err = Pa_StopStream(stream);
        if(err!= paNoError){printErr(err); return err;}
        return 0;
    }


    int AudioOutput::terminate() {
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
            *out++ = audioOutput->generator->output();
            audioOutput->delta++;
        }
        return 0;
    }

    std::unique_ptr<AudioOutput> audioInstance;
    std::mutex audioInstanceMutex;
    std::once_flag initFlag;
    std::once_flag delFlag;


#define LOCK_AUDIO const std::lock_guard<std::mutex> lock(audioInstanceMutex)

    int initialize(){
        std::call_once(initFlag, [](){ audioInstance = std::make_unique<AudioOutput>();});
        return 0;
    }

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