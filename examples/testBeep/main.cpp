
#include <iostream>
#include <Audio.h>
#include <cmath>
#include <AudioUnits/Beep.h>
#include <thread>
#include <AudioUnits/Oscilators/SawWave.h>
#include <AudioUnits/Oscilators/SinWave.h>

int main(int argc, char *argv[]){
    audio::initialize();
    audio::setup({1, 44100, 0});
    /*int devices = audio::deviceCount();
    for(int i = 0; i < devices; i++){
        std::cout << "Device " << i << ": " << (*audio::getDeviceInfo(i))->name << std::endl;
    }*/
    auto *beep = new audio::Beep();
    beep->addVoices<audio::SawWave>(1);
    audio::setGenerator(beep);
    audio::startStream();

    beep->NoteOn(0, {{0, 500.f}});
    auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(4000);
    std::this_thread::sleep_until(x);
    beep->NoteOff(0, {});
    x = std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
    std::this_thread::sleep_until(x);


    if(auto err = audio::stopStream()!=0) {
        std::cout << "stream may not have stopped correctly";
    }
    std::cout << "Stream stopped" << std::endl;

    audio::terminate();

    std::cout << "Pa terminated";
    delete beep;
    return 0;
}