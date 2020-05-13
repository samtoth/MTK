//
// Created by samt on 28/04/2020.
//

#ifndef MUSICTOOLKIT_BEEP_H
#define MUSICTOOLKIT_BEEP_H


#include <IInstrument.h>
#include <AudioUnits/Oscilators/IOscilator.h>
#include <AudioUnits/ADSR.h>
#include <memory>
#include <utility>
namespace audio {

    class Beep : public IInstrument {
    public:
        Beep();

        template <typename T>
        void addVoices(int voices){
            for (int i = 0; i < voices; i++) {
                generators.emplace_back(std::make_shared<T>(), std::make_shared<ADSR>(0.1f, 0.7, 0.09f, 0.6f, 0.1f));
            }
        }

        float output() override;

        void NoteOn(uint32_t voiceID, std::map<uint32_t, float> parameters) override;

        void NoteChange(uint32_t voiceID, std::map<uint32_t, float> parameters) override;

        void NoteOff(uint32_t voiceID, std::map<uint32_t, float> parameters) override;

        void Panic() override;

    private:
        struct voice {
            voice(std::shared_ptr<IOscilator> sinGen, std::shared_ptr<ADSR> adsr) : Osc(std::move(sinGen)),
                                                                                    adsr(std::move(adsr)) {}

            std::shared_ptr<IOscilator> Osc;
            std::shared_ptr<ADSR> adsr;
        };

        std::vector<voice> generators;
    };
}

#endif //MUSICTOOLKIT_BEEP_H
