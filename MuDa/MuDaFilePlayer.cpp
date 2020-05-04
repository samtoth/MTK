//
// Created by samt on 15/04/2020.
//

#include "MuDaFilePlayer.h"

namespace MuDa {

    /// Starts the file player in new thread
    /// \returns success of start
    bool MuDaFilePlayer::startAsync() {
        parseHeader();
        int interval = 1000 / format->header.deltaPerSecond;
        if(format->messages.empty()){
            return false;
        }
        currentMessage = 0;
        delta = 0;
        timerStart(interval, &run);
        return true;
    }

    /// Starts the file player in the main thread
    /// \returns success of the file player
    bool MuDaFilePlayer::start() {
        parseHeader();
        int interval = 1000.f / (float)format->header.deltaPerSecond;
        if(format->messages.empty()){
            return false;
        }
        currentMessage = 0;
        delta = 0;
        run = true;
        while (run) {
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
            this->tick();
            std::this_thread::sleep_until(x);
        }
        return true;
    }

    void MuDaFilePlayer::timerStart(unsigned int interval, bool *_run) {
        *_run = true;
        std::thread([this, interval, _run]() {
            while (*_run) {
                auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
                this->tick();
                std::this_thread::sleep_until(x);
            }
        }).detach();
    }

    void MuDaFilePlayer::stop() {
        run = false;
    }

    void MuDaFilePlayer::tick() {
        if(currentMessage>=format->messages.size()){
            stop();
            std::cout << "Warning file might not have been correctly played";
            return;
        }
        //check if message delta is greater than current message delta
        if(delta>format->messages[currentMessage]->delta){
            currentMessage++;
        }
        while(delta==format->messages[currentMessage]->delta){
            switch (format->messages[currentMessage]->messageType) {
                case MessageCodes::start: {
                    //TODO: do something?? notify audio manager?
                    break;
                }
                case MessageCodes::end: {
                    stop();
                    //TODO: notify audio manager
                    std::cout << "End of file reached";
                    return;
                }
                case MessageCodes::noteOn: {
                    auto mDat = format->messages[currentMessage]->getNoteEventData();
                    audioManager->NoteOn((*mDat).channelId, (*mDat).voiceId, (*mDat).parameters);
                    break;
                }
                case MessageCodes::noteChange: {
                    auto mDat = format->messages[currentMessage]->getNoteEventData();
                    audioManager->NoteChange((*mDat).channelId, (*mDat).voiceId, (*mDat).parameters);
                    break;
                }
                case MessageCodes::noteOff: {
                    auto mDat = format->messages[currentMessage]->getNoteEventData();
                    audioManager->NoteOff((*mDat).channelId, (*mDat).voiceId, (*mDat).parameters);
                    break;
                }
                case MessageCodes::systemParamChange: {
                    auto mDat = format->messages[currentMessage]->getSystemParamData();
                    audioManager->SystemParamChange((*mDat));
                    break;
                }
                case MessageCodes::panic: {
                    auto mDat = format->messages[currentMessage]->getPanicData();
                    audioManager->Panic((*mDat));
                    break;
                }
            }
            currentMessage++;
        }
        delta++;
    }


    void MuDaFilePlayer::parseHeader() {

    }
}