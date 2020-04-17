/**
 * \class LinearTuning
 * \brief A child of IRegularTuning. LinearTuning implements a Rank 2 Regular temperament as defined by https://en.xen.wiki/w/Tour_of_Regular_Temperaments#Rank-2_.28including_linear.29_temperaments
 */
#ifndef MUSICTOOLKIT_LINEARTUNING_H
#define MUSICTOOLKIT_LINEARTUNING_H

#include <IRegularTuning.h>
namespace MTKCore{
#define Vector Eigen::Vector2i
        class LinearTuning :
        public IRegularTuning<Vector> {
            public:
            LinearTuning(float period, float generator, float _fundamentalFrequency);

            std::string getNoteName(float frequency) override;

            std::string getNoteName(Vector coordinate) override;

            float distanceFromNote(float frequency) override;

            Vector getCoordinate(float frequency) override;

            float getFrequency(Vector coordinate)
            override;

            private:
            float generator;
            float period;
        };
}

#endif //MUSICTOOLKIT_LINEARTUNING_H
