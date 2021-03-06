//
// Created by samt on 15/04/2020.
//

#ifndef MUSICTOOLKIT_IAUDIOMANAGER_H
#define MUSICTOOLKIT_IAUDIOMANAGER_H
#include <cstdint>
#include <vector>
#include <IAudioUnit.h>
#include <map>

namespace MTK::Audio {
    class IAudioManager : public IAudioUnit {
    public:
        IAudioManager() {}

        virtual void NoteOn(uint32_t chanel, uint32_t voiceID, PARAM_t parameters) = 0;

        virtual void NoteChange(uint32_t chanel, uint32_t voiceID, PARAM_t parameters) = 0;

        virtual void NoteOff(uint32_t chanel, uint32_t voiceID, PARAM_t parameters) = 0;

        virtual void SystemParamChange(PARAM_t parameters) = 0;

        virtual void Panic(uint32_t channel) = 0;

    private:
        float delta;
    };
}
#endif //MUSICTOOLKIT_IAUDIOMANAGER_H
