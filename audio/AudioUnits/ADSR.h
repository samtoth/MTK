//
// Created by samt on 28/04/2020.
//

#ifndef MUSICTOOLKIT_ADSR_H
#define MUSICTOOLKIT_ADSR_H

#include <IAudioUnit.h>
namespace MTK::Audio {
    class ADSR : IAudioUnit {
    public:
        enum State {
            NoState,
            Attack,
            Decay,
            Sustain,
            Release
        };

        ADSR();

        ADSR(float aTime, float aLevel, float dTime, float sLev, float rTime);

        void NoteOn();

        void NoteOff();

        void setAttackTime(float _attackTime) { attackTime = _attackTime; }

        void setAttackLevel(float _attackLevel) { attackLevel = _attackLevel; }

        void setDecayTime(float _decayTime) { decayTime = _decayTime; }

        void setSustainLevel(float _sustainLevel) { sustainLevel = _sustainLevel; }

        void setReleaseTime(float _releaseTime) { releaseTime = _releaseTime; }

        State getState() const { return state; }

        float output() override;

    protected:
        State state;

        float attackTime;
        float attackLevel;
        float decayTime;
        float sustainLevel;
        float releaseTime;

        float current;
    };
}

#endif //MUSICTOOLKIT_ADSR_H
