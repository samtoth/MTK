//
// Created by samt on 28/04/2020.
//

#include "ADSR.h"
#include <Audio.h>

ADSR::ADSR(){
    attackLevel = 1;
    attackTime = 1;
    decayTime = 1;
    sustainLevel = 1;
    releaseTime = 1;

    current = 0;
    state = NoState;
}


float ADSR::output() {
    unsigned long delta = audio::delta();
    switch(state){
        case NoState:
            break;
        case Attack:
            current += 1/(attackTime* audio::getAudioSettings().sampleRate);
            if(current>=attackLevel){
                current = attackLevel;
                state = Decay;
            }
            break;
        case Decay:
            current -= 1/(decayTime* audio::getAudioSettings().sampleRate);
            if(current<=sustainLevel){
                current = sustainLevel;
                state = Sustain;
            }
            break;
        case Sustain:
            break;
        case Release:
            current -= 1/(releaseTime* audio::getAudioSettings().sampleRate);
            if(current<=0){
                current = 0;
                state = NoState;
            }
            break;
    }

    return current;
}

void ADSR::NoteOn() {
    state = Attack;
}

void ADSR::NoteOff() {
    state = Release;
}

ADSR::ADSR(float aTime, float aLev, float dTime, float sLev, float rTime) : ADSR() {
    attackTime = aTime;
    attackLevel = aLev;
    decayTime  = dTime;
    sustainLevel = sLev;
    releaseTime = rTime;
}


