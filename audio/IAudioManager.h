//
// Created by samt on 15/04/2020.
//

#ifndef MUSICTOOLKIT_IAUDIOMANAGER_H
#define MUSICTOOLKIT_IAUDIOMANAGER_H
#include <cstdint>
#include <vector>

#define UINT32 uint32_t
#define PARAM_t std::vector<std::pair<UINT32 /*paramID*/, float /*value*/>>
class IAudioManager {

public:
    virtual void NoteOn(UINT32 chanel, UINT32 noParams, PARAM_t parameters) = 0;
    virtual void NoteChange(UINT32 chanel, UINT32 noParams, PARAM_t parameters) = 0;
    virtual void NoteOff(UINT32 chanel, UINT32 noParams, PARAM_t parameters) = 0;
    virtual void SystemParamChange(PARAM_t parameters) = 0;
    virtual void Panic(UINT32 channel) = 0;
};

#endif //MUSICTOOLKIT_IAUDIOMANAGER_H
