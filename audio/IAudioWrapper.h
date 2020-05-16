//
// Created by sammy on 14/05/2020.
//

#ifndef MUSICTOOLKIT_IAUDIOWRAPPER_H
#define MUSICTOOLKIT_IAUDIOWRAPPER_H

#include <cstdint>
#include <utility>
#include "IAudioUnit.h"

namespace MTK::Audio {
    /// \brief data structure for setting up output device
    struct AudioSettings{
        int outputChannels;
        double sampleRate;
        int bufferSize; //!< bufferSize in ms. set to 0 to autocalculate optimum bufferSize
    };

    class IAudioWrapper {
    public:
        IAudioWrapper(){
            generator = nullptr;
        }

        virtual int setup(AudioSettings settings) = 0;

        uint64_t delta = 0;

        AudioSettings devSettings;

        virtual int startStream() = 0;

        virtual int stopStream() = 0;

        virtual int terminate() = 0;

        std::shared_ptr<IAudioUnit> generator;
    };
}
#endif //MUSICTOOLKIT_IAUDIOWRAPPER_H
