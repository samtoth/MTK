/**
 * \class LinearTuning
 * \brief A child of IRegularTuning. LinearTuning implements a Rank 2 Regular temperament as defined by https://en.xen.wiki/w/Tour_of_Regular_Temperaments#Rank-2_.28including_linear.29_temperaments
 */
#ifndef MUSICTOOLKIT_LINEARTUNING_H
#define MUSICTOOLKIT_LINEARTUNING_H

#include <IRegularTuning.h>
#define Vector Eigen::Vector2i
namespace MTKCore{
        class LinearTuning :
        public IRegularTuning<Vector> {
            public:
            LinearTuning(float period, float generator, float _fundamentalFrequency);

            std::string getNoteName(Vector coordinate) override;

            std::unique_ptr<IScale> generateScale(int notesPerPeriod) override;

            std::optional<Vector> getCoordinate(float frequency) override;

            float getFrequency(Vector coordinate) override;

            private:
            template<class T>
            typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
            static almost_equal(T x, T y, int ulp);

            float generator;
        };
}

#endif //MUSICTOOLKIT_LINEARTUNING_H
