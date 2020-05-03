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
#include <memory>
#include <mutex>
#include "IAudioUnit.h"

/// \brief data structure for setting up output device
struct audioSettings{
    int outputChannels;
    double sampleRate;
    int bufferSize; //!< bufferSize in ms. set to 0 to autocalculate optimum bufferSize
};

class AudioOutput {
public:

    AudioOutput();

    uint64_t delta = 0;

    virtual ~AudioOutput() = default;

    int initialize(audioSettings settings);
    int terminate();

    int startStream();
    int stopStream();

    int deviceCount();

    std::optional<const PaDeviceInfo*> getDeviceInfo(int i);
    int printDevices();

    audioSettings devSettings;
    IAudioUnit *generator;

private:
    PaStream *stream;


    static int callback( const void *input,
                          void *output,
                          unsigned long frameCount,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData ) ;

};



#endif //MUSICTOOLKIT_AUDIOOUTPUT_H
