//
// Created by samt on 15/04/2020.
//

#include "MuDaIO.h"

namespace MuDa {

/// Starts the thread
///
    void MuDaIO::start() {
        parseHeader();
        int interval = 1000 / format->header.deltaPerSecond;
        timerStart(interval, &run);
    }

    void MuDaIO::timerStart(unsigned int interval, bool *run) {
        *run = true;
        std::thread([this, interval, run]() {
            while (*run) {
                auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
                this->tick();
                std::this_thread::sleep_until(x);
            }
        }).detach();
    }

    void MuDaIO::stop() {
        run = false;
    }

    void MuDaIO::tick() {

    }


    void MuDaIO::parseHeader() {

    }
}