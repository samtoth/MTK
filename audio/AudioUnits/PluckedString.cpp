//
// Created by sammy on 08/06/2020.
//

#include "PluckedString.h"
#include <Audio.h>

#define SAMPLE_RATE MTK::Audio::AUDIO_SYSTEM->getAudioSettings().sampleRate

MTK::Audio::PluckedString::PluckedString(float lowestPitch) : adsr(0.05f, 1.f, 0.01f, 0, 1), delay(SAMPLE_RATE/(lowestPitch*2), SAMPLE_RATE/lowestPitch){
}

float MTK::Audio::PluckedString::output() {
    float feedback = (adsr.output() * noise.output()) + (delay.front() * 0.977f);
    return delay.output(feedback);
}

void MTK::Audio::PluckedString::NoteOn(uint32_t voiceID, std::map<uint32_t, float> parameters) {
    delay.setDelay(SAMPLE_RATE/parameters[0]);
    adsr.NoteOn();
}

void MTK::Audio::PluckedString::NoteChange(uint32_t voiceID, std::map<uint32_t, float> parameters) {
    delay.setDelay(SAMPLE_RATE/parameters[0]);
}

void MTK::Audio::PluckedString::NoteOff(uint32_t voiceID, std::map<uint32_t, float> parameters) {
    adsr.NoteOff();
}

void MTK::Audio::PluckedString::Panic() {

}
