//
// Created by sammy on 13/05/2020.
//

#ifndef MUSICTOOLKIT_SAWWAVE_H
#define MUSICTOOLKIT_SAWWAVE_H

#include <AudioUnits/Oscillators/IOscillator.h>

namespace audio {
    class SawWave : public IOscillator {
    public:
        SawWave();
        float output() override;

    private:
        float phase;
    };
}

#endif //MUSICTOOLKIT_SAWWAVE_H
