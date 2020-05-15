
#include <iostream>
#include <Audio.h>
#include <cmath>
#include <AudioUnits/Beep.h>
#include <thread>
#include <AudioUnits/Oscillators/SawWave.h>
#include <AudioUnits/Oscillators/SinWave.h>

int main(int argc, char *argv[]){
    Audio::initialize();
    Audio::setup({1, 44100, 0});
    auto *beep = new Audio::Beep();
    beep->addVoices<Audio::SawWave>(1);
    Audio::setGenerator(beep);
    Audio::startStream();

    beep->NoteOn(0, {{0, 500.f}});
    auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(4000);
    std::this_thread::sleep_until(x);
    beep->NoteOff(0, {});
    x = std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
    std::this_thread::sleep_until(x);


    if(auto err = Audio::stopStream() != 0) {
        std::cout << "stream may not have stopped correctly";
    }
    std::cout << "Stream stopped" << std::endl;

    Audio::terminate();

    std::cout << "Pa terminated";
    delete beep;
    return 0;
}