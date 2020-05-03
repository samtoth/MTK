
#include <stdexcept>
#include <map>
#include <math.h>
#include "BasicAudioManager.h"

#define CHECK_INDEX(i) if(i>=instruments.size()){/* TODO: Add logging functionality */ throw std::out_of_range("Channel number out of range"); }

int BasicAudioManager::addInstrument(IInstrument *instrument) {
    instruments.emplace_back(instrument, 0.f);
    return instruments.size();
}

void BasicAudioManager::setLevel(int i, float l) {
    instruments[i].second = l;
}

float BasicAudioManager::getLevel(int i) {
    return instruments[i].second;
}

IInstrument *BasicAudioManager::instrument(int i) {
    CHECK_INDEX(i)
    return instruments[i].first;
}

void BasicAudioManager::NoteOn(uint32_t chanel, uint32_t voiceID, std::map<uint32_t, float> parameters) {
    CHECK_INDEX(chanel)
    instruments[chanel].first->NoteOn(voiceID, parameters);
}

void BasicAudioManager::NoteChange(uint32_t chanel, uint32_t voiceID, std::map<uint32_t, float> parameters) {
    CHECK_INDEX(chanel)
    instruments[chanel].first->NoteChange(voiceID, parameters);
}

void BasicAudioManager::NoteOff(uint32_t chanel, uint32_t voiceID, std::map<uint32_t, float> parameters) {
    CHECK_INDEX(chanel)
    instruments[chanel].first->NoteOff(voiceID, parameters);
}

void BasicAudioManager::SystemParamChange(std::map<uint32_t, float> parameters) {

}

void BasicAudioManager::Panic(uint32_t chanel) {
    CHECK_INDEX(chanel)
    instruments[chanel].first->Panic();
}

float BasicAudioManager::output() {
    float result = 0;
    for(int i =0; i<instruments.size(); i++){
        result += instruments[i].first->output() * (1 / (2.f * instruments.size())) * powf(2, instruments[i].second);
    }
    return result;
}
