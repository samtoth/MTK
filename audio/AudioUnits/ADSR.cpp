//
// Created by samt on 28/04/2020.
//

#include <AudioOutput.h>
#include "ADSR.h"

ADSR::ADSR(){
    attackLevel = 1;
    attackTime = 1;
    decayTime = 1;
    sustainLevel = 1;
    releaseTime = 1;

    current = 0;
    state = NoState;
    stateStart = 0;
    stateEnd = 0;
    stateStartValue = 0;
}


float ADSR::output() {
    unsigned long delta = AudioOutput::instance().delta;
    switch(state){
        case NoState:
            break;
        case Attack:
            if(stateStart <= 0.0001f){
                stateStart = delta;
                stateEnd = delta+attackTime;
            }
            current = ((delta-stateStart)/stateEnd)*attackLevel;
            stateStartValue = current; //If released before attack is complete
            if(delta>=stateEnd){
                state = Decay;
                stateStart = delta;
                stateEnd = delta+decayTime;
                stateStartValue = attackLevel;
            }
            break;
        case Decay:
            current = attackLevel - ((delta-stateStart)/stateEnd) * (attackLevel-sustainLevel);
            stateStartValue = current;
            if(delta>=stateEnd){
                state = Sustain;
            }
            break;
        case Sustain:
            break;
        case Release:
            if(stateStart <= 0.0001f){
                stateStart = delta;
                stateEnd = delta+releaseTime;
            }
            current = (1-((delta-stateStart)/stateEnd)) * stateStartValue;
            if(delta>=stateEnd){
                state = NoState;
            }
            break;
    }

    return current;
}

void ADSR::NoteOn() {
    state = Attack;
    stateStart = 0;
    stateEnd = 0;
}

void ADSR::NoteOff() {
    state = Release;
    stateStart = 0;
    stateEnd = 0;
}

ADSR::ADSR(float aTime, float aLev, float dTime, float sLev, float rTime) : ADSR() {
    attackTime = aTime;
    attackLevel = aLev;
    decayTime  = dTime;
    sustainLevel = sLev;
    releaseTime = rTime;
}


