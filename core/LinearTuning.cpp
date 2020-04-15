//
// Created by samt on 15/04/2020.
//

#include "LinearTuning.h"

LinearTuning::LinearTuning(float period, float generator, float _fundamentalFrequency) {
    setFundamentalFrequency(_fundamentalFrequency);
}

std::string LinearTuning::getNoteName(float frequency) {
    return std::string();
}

std::string LinearTuning::getNoteName(Eigen::VectorXf coordinate) {
    return std::string();
}

float LinearTuning::distanceFromNote(float frequency) {
    return 0;
}

Eigen::VectorXf LinearTuning::getCoordinate(float frequency) {
    return Eigen::VectorXf();
}

float LinearTuning::getFrequency(Eigen::VectorXf coordinate) {
    return 0;
}
