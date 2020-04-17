//
// Created by samt on 15/04/2020.
//

#include "LinearTuning.h"
namespace MTKCore {
    LinearTuning::LinearTuning(float period, float generator, float _fundamentalFrequency) {
        setFundamentalFrequency(_fundamentalFrequency);
    }

    std::string LinearTuning::getNoteName(float frequency) {
        return std::string();
    }

    std::string LinearTuning::getNoteName(Vector coordinate) {
        return std::string();
    }

    float LinearTuning::distanceFromNote(float frequency) {
        return 0;
    }

    Vector LinearTuning::getCoordinate(float frequency) {
        return Vector();
    }

    float LinearTuning::getFrequency(Vector coordinate) {
        return getFundamentalFrequency() * std::pow(period, coordinate[0]) * std::pow(generator, coordinate[1]);
    }
}