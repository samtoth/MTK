#ifndef MUSICTOOLKIT_PERIODICSCALE_H
#define MUSICTOOLKIT_PERIODICSCALE_H

#include <cmath>
#include "IScale.h"
namespace MTK::Core {
	/// \brief A set of frequency ratios that repeat at a given period
    class PeriodicScale : public IScale {
    public:
        /// \param period The point at which the scale repeats itself (most often at the octave (2) but not necessarily)
        /// \param noteCollection A group of frequency ratios between but not including 1 and period. Note that the 0th element of periodic scale note collection is always 1. It is highly recommended that noteCollection[n]>noteCollection[n-1]
        /// \param referencePitch frequency at which Scale[{0,0}] will return
        PeriodicScale(float period, std::vector<float> noteCollection, float referencePitch);

        /// \returns the ratio between the given frequency and the frequency of the note to which it is closest
        float distanceFromNote(float frequency) override;

        struct accessIndex {
            unsigned int _period;
            unsigned int _degree;
        };

        float operator[](accessIndex i) {
            return frequencyCollection[i._degree] * pow(period, i._period);
        }

    private:
        float period;
        float referencePitch;
    };
}
#endif //MUSICTOOLKIT_PERIODICSCALE_H