/**
 * \class BasicAudioManager
 * \brief A basic implementation of IAudioManager that has a list of instruments and a basic mixer
 * \author Sam
 */
#ifndef MUSICTOOLKIT_BASICAUDIOMANAGER_H
#define MUSICTOOLKIT_BASICAUDIOMANAGER_H


#include "IAudioManager.h"
#include <IInstrument.h>

class BasicAudioManager : public IAudioManager{
public:
    /// \Returns index of instrument or -1 if there is an error
    int addInstrument(IInstrument *instrument);
    /// \brief set the level of the instrument. 0 represents 1/(2*number of instruments) * 2^(level)
    void setLevel(int i, float l);

    float getLevel(int i);

    IInstrument *instrument(int i);
private:
    std::vector<std::pair<IInstrument*, float>> instruments;
};


#endif //MUSICTOOLKIT_BASICAUDIOMANAGER_H
