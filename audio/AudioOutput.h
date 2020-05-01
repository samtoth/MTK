/**
 * \class AudioOutput
 * \brief A wrapper around PortAudio to send audio streams to devices on any platform
 */
#ifndef MUSICTOOLKIT_AUDIOOUTPUT_H
#define MUSICTOOLKIT_AUDIOOUTPUT_H


#include <portaudio.h>
#include <cstdint>
#include <vector>
#include <optional>
#include "IAudioUnit.h"

/// \brief data structure for setting up output device
struct deviceSettings{
    int outputChannels;
    double sampleRate;
    int bufferSize; //!< bufferSize in ms. set to 0 to autocalculate optimum bufferSize
};

class AudioOutput {
public:
    AudioOutput();

    int initialize(deviceSettings settings);
    int terminate();

    int startStream();
    int stopStream();


    IAudioUnit *generator;

    int deviceCount();

    std::optional<const PaDeviceInfo*> getDeviceInfo(int i);
    int printDevices();

private:
    PaStream *stream;

    deviceSettings devSettings;

    static int callback( const void *input,
                          void *output,
                          unsigned long frameCount,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData ) ;

};


#endif //MUSICTOOLKIT_AUDIOOUTPUT_H
