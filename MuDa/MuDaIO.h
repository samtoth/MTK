/**
 * \class MuDa
 * \brief MuDaIO takes a raw streambuffer derived IMuDaStream and interprets the data and sends appropriate calls to the audioManager class its given
 */

#ifndef MUSICTOOLKIT_MUDAIO_H
#define MUSICTOOLKIT_MUDAIO_H

#include <IAudioManager.h>
#include <IMuDaStream.h>
#include "MuDaFileFormat.h"
#include <thread>
#include <functional>

class MuDaIO {
public:
    MuDaIO(IMuDaStream* _muDaStream, IAudioManager* _audioManager) : muDaStream(_muDaStream), audioManager(_audioManager){}

    void start();
    void stop();

private:
    void tick();
    void parseHeader();

    void timerStart(unsigned int interval, bool* run);

    bool run;
    MuDaFileFormat* format;
    IMuDaStream* muDaStream;
    IAudioManager* audioManager;
};


#endif //MUSICTOOLKIT_MUDAIO_H
