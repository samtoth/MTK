//
// Created by samt on 28/04/2020.
//

#include <cmath>
#include <Audio.h>
#include "SinWave.h"

SinWave::SinWave() {
    frequency = 0;
}

float SinWave::output() {

    return sinf((float)(audio::delta() * M_2_PI * frequency)/(float)(audio::audioSettings().sampleRate));
}

float SinWave::getFrequency() const {
    return frequency;
}

void SinWave::setFrequency(float frequency) {
    SinWave::frequency = frequency;
}
