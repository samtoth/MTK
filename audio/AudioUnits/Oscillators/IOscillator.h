//
// Created by sammy on 13/05/2020.
//

#ifndef MUSICTOOLKIT_IOSCILLATOR_H
#define MUSICTOOLKIT_IOSCILLATOR_H

#include <IAudioUnit.h>
namespace MTK::Audio {
	/// An Audio unit that always outputs sound given a frequency.
    class IOscillator : public IAudioUnit {
    public:
        IOscillator(){ frequency=0;}

        float getFrequency() const{
            return frequency;
        }

        void setFrequency(float _frequency){
            frequency = _frequency;
        }

    protected:
        float frequency;
    };
}

#endif //MUSICTOOLKIT_IOSCILLATOR_H
