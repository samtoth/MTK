

#ifndef MUSICTOOLKIT_IINSTRUMENT_H
#define MUSICTOOLKIT_IINSTRUMENT_H

#include <cstdint>
#include <vector>
#include "IAudioUnit.h"
#include <map>

namespace MTK::Audio {
    /// Interface that defines an IAudioUnit that accepts control messages from an IAudioManager
    class IInstrument : public IAudioUnit {
    public:
        virtual void NoteOn(uint32_t voiceID, PARAM_t parameters) = 0;
        virtual void NoteChange(uint32_t voiceID, PARAM_t parameters) = 0;
        virtual void NoteOff(uint32_t voiceID, PARAM_t parameters) = 0;
        virtual void Panic() = 0;
    };
}
#endif //MUSICTOOLKIT_IINSTRUMENT_H
