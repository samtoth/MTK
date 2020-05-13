//
// Created by sammy on 13/05/2020.
//

#ifndef MUSICTOOLKIT_SAWWAVE_H
#define MUSICTOOLKIT_SAWWAVE_H

#include <AudioUnits/Oscilators/IOscilator.h>

namespace audio {
    class SawWave : public IOscilator {
    public:
        SawWave();
        float output() override;

    private:
        float phase;
    };
}

#endif //MUSICTOOLKIT_SAWWAVE_H
