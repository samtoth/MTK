//
// Created by samt on 28/04/2020.
//

#ifndef MUSICTOOLKIT_SINWAVE_H
#define MUSICTOOLKIT_SINWAVE_H


#include <IAudioUnit.h>

class SinWave : public IAudioUnit {
public:
    SinWave();
    float output(float delta) override;

    float getFrequency() const;

    void setFrequency(float frequency);

private:
    float frequency;
};


#endif //MUSICTOOLKIT_SINWAVE_H
