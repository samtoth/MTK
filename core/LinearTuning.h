//
// Created by samt on 15/04/2020.
//

#ifndef MUSICTOOLKIT_LINEARTUNING_H
#define MUSICTOOLKIT_LINEARTUNING_H

#include <IRegularTuning.h>

class LinearTuning : public IRegularTuning {
public:
    LinearTuning(float period, float generator, float _fundamentalFrequency);

    std::string getNoteName(float frequency) override;

    std::string getNoteName(Eigen::VectorXf coordinate) override;

    float distanceFromNote(float frequency) override;

    Eigen::VectorXf getCoordinate(float frequency) override;

    float getFrequency(Eigen::VectorXf coordinate) override;
};


#endif //MUSICTOOLKIT_LINEARTUNING_H
