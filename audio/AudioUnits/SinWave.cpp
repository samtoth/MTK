//
// Created by samt on 28/04/2020.
//

#include <cmath>
#include "SinWave.h"

SinWave::SinWave() {
    frequency = 0;
}

float SinWave::output(float delta) {
    return sinf(delta * M_2_PI * frequency);
}

float SinWave::getFrequency() const {
    return frequency;
}

void SinWave::setFrequency(float frequency) {
    SinWave::frequency = frequency;
}
