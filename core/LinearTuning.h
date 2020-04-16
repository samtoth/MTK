/**
 * \class LinearTuning
 * \brief A child of IRegularTuning. LinearTuning implements a Rank 2 Regular temperament as defined by https://en.xen.wiki/w/Tour_of_Regular_Temperaments#Rank-2_.28including_linear.29_temperaments
 */
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
