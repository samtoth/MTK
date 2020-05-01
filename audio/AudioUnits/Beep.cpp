//
// Created by samt on 28/04/2020.
//

#include <map>
#include "Beep.h"

float Beep::output(float delta) {
    return 0;
}

#define CHECK_VOICE_ID(id) if(id<generators.size()){throw std::out_of_range("Beep instrument does not contain enough voices");}id

void Beep::NoteOn(uint32_t voiceID, std::map<uint32_t, float> parameters) {
    CHECK_VOICE_ID(voiceID);
    if(parameters.find(0)!=parameters.end()){
        generators[voiceID].SinGen->setFrequency(parameters[0]);
    }
    generators[voiceID].adsr->NoteOn();
}

void Beep::NoteChange(uint32_t voiceID, std::map<uint32_t, float> parameters) {
    CHECK_VOICE_ID(voiceID);
}

void Beep::NoteOff(uint32_t voiceID, std::map<uint32_t, float> parameters) {
    CHECK_VOICE_ID(voiceID);
}

void Beep::Panic() {

}

Beep::Beep(int voices) {
    for(int i = 0; i<voices; i++){
        generators.emplace_back(std::make_shared<SinWave>(), std::make_shared<ADSR>());
    }
}
