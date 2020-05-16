
#include "PeriodicScale.h"
namespace MTK::Core {
    float PeriodicScale::distanceFromNote(float frequency) {
        //TODO: Implement this function

        return 0;
    }

    PeriodicScale::PeriodicScale(float _period, std::vector<float> noteCollection, float _referencePitch) {
        period = _period;
        referencePitch = _referencePitch;
    }
}