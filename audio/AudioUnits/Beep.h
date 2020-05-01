//
// Created by samt on 28/04/2020.
//

#ifndef MUSICTOOLKIT_BEEP_H
#define MUSICTOOLKIT_BEEP_H


#include <IInstrument.h>
#include <AudioUnits/SinWave.h>
#include <AudioUnits/ADSR.h>
#include <memory>
#include <utility>

typedef struct voice{
    voice(std::shared_ptr<SinWave> sinGen, std::shared_ptr<ADSR> adsr) : SinGen(std::move(sinGen)), adsr(std::move(adsr)) {}

    std::shared_ptr<SinWave> SinGen;
    std::shared_ptr<ADSR> adsr;
};
class Beep : public IInstrument{
public:
    Beep(int voices);

    float output(float delta) override;

    void NoteOn(uint32_t voiceID, std::vector<std::pair<uint32_t, float>> parameters) override;
    void NoteChange(uint32_t voiceID, std::vector<std::pair<uint32_t, float>> parameters) override;
    void NoteOff(uint32_t voiceID, std::vector<std::pair<uint32_t, float>> parameters) override;
    void Panic() override;
private:
    std::vector<voice> generators;
};


#endif //MUSICTOOLKIT_BEEP_H
