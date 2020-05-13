//
// Created by samt on 28/04/2020.
//

#ifndef MUSICTOOLKIT_SINWAVE_H
#define MUSICTOOLKIT_SINWAVE_H

#include "IOscillator.h"

namespace audio {
    class SinWave : public IOscillator {
    public:
        SinWave();
        float output() override;

    private:
        float phase;
    };
}
#endif //MUSICTOOLKIT_SINWAVE_H
