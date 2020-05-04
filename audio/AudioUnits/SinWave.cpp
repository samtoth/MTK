//
// Created by samt on 28/04/2020.
//

#include <cmath>
#include <Audio.h>
#include "SinWave.h"

SinWave::SinWave() {
    frequency = 0;
    phase = 0;
    sample = 0;
}

float SinWave::output() {
    phase += (2*M_PI*frequency)/(float)audio::audioSettings().sampleRate;
    if(phase>=2*M_PI) {
        phase -= 2*M_PI;
    }
    return sin(phase);
}

float SinWave::getFrequency() const {
    return frequency;
}

void SinWave::setFrequency(float frequency) {
    SinWave::frequency = frequency;
}
