//
// Created by sammy on 08/06/2020.
//

#ifndef MUSICTOOLKIT_WHITENOISE_H
#define MUSICTOOLKIT_WHITENOISE_H

#include <IAudioUnit.h>
#include <random>

namespace MTK::Audio {
    class WhiteNoise : public IAudioUnit {
    public:
        WhiteNoise();

        float output() override;
    };
}

#endif //MUSICTOOLKIT_WHITENOISE_H
