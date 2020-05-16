/**
 * \class MuDa
 * \brief MuDaFilePlayer takes a raw streambuffer derived IMuDaStream and interprets the data and sends appropriate calls to the audioManager class its given
 */

#ifndef MUSICTOOLKIT_MUDAFILEPLAYER_H
#define MUSICTOOLKIT_MUDAFILEPLAYER_H

#include <IAudioManager.h>
#include <IMuDaStream.h>
#include "MuDaFileFormat.h"
#include <thread>
#include <functional>
namespace MTK::MuDa {
    class MuDaFilePlayer {
    public:
        MuDaFilePlayer(std::shared_ptr<MuDaFileFormat> MuDaFile, Audio::IAudioManager *_audioManager) : audioManager(_audioManager) { format = MuDaFile;}

        bool start();
        bool startAsync();

        void stop();

    private:
        /// \returns milliseconds until next messages
        int tick();


        void timerStart(unsigned int interval, bool *run);

        int currentMessage;
        uint64_t delta;
        bool run;
        std::shared_ptr<MuDaFileFormat> format;
        Audio::IAudioManager *audioManager;
    };
}

#endif //MUSICTOOLKIT_MUDAFILEPLAYER_H
