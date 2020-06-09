//
// Created by sammy on 08/06/2020.
//

#include "WhiteNoise.h"
#include <ctime>

MTK::Audio::WhiteNoise::WhiteNoise() {
    srand(time(nullptr));
}

float MTK::Audio::WhiteNoise::output() {
    return 2.f*((std::rand()/(float)RAND_MAX)-0.5f);
}
