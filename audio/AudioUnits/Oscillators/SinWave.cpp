//
// Created by samt on 28/04/2020.
//

#include <cmath>
#include <Audio.h>
#include "SinWave.h"

namespace audio {
    SinWave::SinWave() : IOscillator(){
        frequency = 0;
        phase = 0;
    }

    float SinWave::output() {
        phase += (2 * M_PI * frequency) / (float) getAudioSettings().sampleRate;
        if (phase >= 2 * M_PI) {
            phase -= 2 * M_PI;
        }
        return sinf(phase);
    }
}