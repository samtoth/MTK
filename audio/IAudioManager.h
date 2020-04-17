//
// Created by samt on 15/04/2020.
//

#ifndef MUSICTOOLKIT_IAUDIOMANAGER_H
#define MUSICTOOLKIT_IAUDIOMANAGER_H
#include <cstdint>
#include <vector>

#define UINT16 uint16_t

class IAudioManager {

public:
    virtual void NoteOn(UINT16 chanel, UINT16 noParams, std::vector<std::pair<short /*paramID*/, float /*value*/>>) = 0;
    virtual void NoteChange(UINT16 chanel, UINT16 noParams, std::vector<std::pair<short /*paramID*/, float /*value*/>>) = 0;
    virtual void NoteOff(UINT16 chanel, UINT16 noParams, std::vector<std::pair<short /*paramID*/, float /*value*/>>) = 0;



};


#endif //MUSICTOOLKIT_IAUDIOMANAGER_H
