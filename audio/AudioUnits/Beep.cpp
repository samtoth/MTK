//
// Created by samt on 28/04/2020.
//

#include <map>
#include "Beep.h"

namespace MTK::Audio {
    float Beep::output() {
        float result = 0;
        for (int i = 0; i < generators.size(); i++) {
            result += generators[i].Osc->output() * generators[i].adsr->output() * (float) (1.f / generators.size());
        }
        return result;
    }

#define CHECK_VOICE_ID(id) if(id>generators.size()){throw std::out_of_range("Beep instrument does not contain enough voices");}

    void Beep::NoteOn(uint32_t voiceID, std::map<uint32_t, float> parameters) {
        CHECK_VOICE_ID(voiceID)
        if (parameters.find(0) != parameters.end()) {
            generators[voiceID].Osc->setFrequency(parameters[0]);
        }
        generators[voiceID].adsr->NoteOn();
    }

    void Beep::NoteChange(uint32_t voiceID, std::map<uint32_t, float> parameters) {
        CHECK_VOICE_ID(voiceID)
        if (parameters.find(0) != parameters.end()) {
            generators[voiceID].Osc->setFrequency(parameters[0]);
        }
    }

    void Beep::NoteOff(uint32_t voiceID, std::map<uint32_t, float> parameters) {
        CHECK_VOICE_ID(voiceID)
        generators[voiceID].adsr->NoteOff();
    }

    void Beep::Panic() {

    }


    Beep::Beep() {
    }
}