//
// Created by sammy on 08/06/2020.
//

#ifndef MUSICTOOLKIT_PLUCKEDSTRING_H
#define MUSICTOOLKIT_PLUCKEDSTRING_H

#include <IInstrument.h>
#include "WhiteNoise.h"
#include "ADSR.h"
#include "Filters/Delay.h"

namespace MTK::Audio{
    class PluckedString : public IInstrument{
    public:
        PluckedString(float lowestPitch);

        void NoteOn(uint32_t voiceID, std::map<uint32_t, float> parameters) override;

        void NoteChange(uint32_t voiceID, std::map<uint32_t, float> parameters) override;

        void NoteOff(uint32_t voiceID, std::map<uint32_t, float> parameters) override;

        void Panic() override;

        float output() override;

    private:
        WhiteNoise noise;
        ADSR adsr;
        Delay delay;
    };
}

#endif //MUSICTOOLKIT_PLUCKEDSTRING_H
