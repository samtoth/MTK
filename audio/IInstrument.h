///
/// \class IInstrument
///

#ifndef MUSICTOOLKIT_IINSTRUMENT_H
#define MUSICTOOLKIT_IINSTRUMENT_H

#include <cstdint>
#include <vector>
#include "IGenerator.h"

#define PARAM_t std::vector<std::pair<uint32_t /*paramID*/, float /*value*/>>

class IInstrument : public IGenerator{

    virtual void NoteOn(uint32_t chanel, uint32_t noParams, PARAM_t parameters) = 0;
    virtual void NoteChange(uint32_t chanel, uint32_t noParams, PARAM_t parameters) = 0;
    virtual void NoteOff(uint32_t chanel, uint32_t noParams, PARAM_t parameters) = 0;
    virtual void SystemParamChange(PARAM_t parameters) = 0;
    virtual void Panic(uint32_t channel) = 0;
};

#endif //MUSICTOOLKIT_IINSTRUMENT_H
