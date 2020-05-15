//
// Created by sammy on 13/05/2020.
//

#include "SawWave.h"
#include <Audio.h>
#include <cmath>

namespace MTK::Audio {
    SawWave::SawWave() : IOscillator(){
        phase = 0;
    }

    float SawWave::output() {
        phase += (2 * frequency) / (float) Audio::getAudioSettings().sampleRate;
        if (phase >= 1) {
            phase -= 2;
        }
        return phase;
    }
}