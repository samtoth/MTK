//
// Created by samt on 28/04/2020.
//

#include "SinWave.h"

SinWave::SinWave() {}

float SinWave::output(float delta) {
    return 0;
}

float SinWave::getFrequency() const {
    return frequency;
}

void SinWave::setFrequency(float frequency) {
    SinWave::frequency = frequency;
}
