
#include <iostream>
#include <Audio.h>
#include <BasicAudioManager.h>
#include <cmath>
#include <AudioUnits/Beep.h>
#include <MuDaFilePlayer.h>

int main(int argc, char *argv[]){
    audio::initialize();
    audio::setup({1, 44100, 0});
    int devices = audio::deviceCount();
    for(int i = 0; i < devices; i++){
        std::cout << "Device " << i << ": " << (*audio::getDeviceInfo(i))->name << std::endl;
    }
    auto *beep = new Beep(1);
    audio::setGenerator(beep);
    audio::startStream();

    auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(4000);
    beep->NoteOn(0, {{0, 440.f}});
    std::this_thread::sleep_until(x);
    x = std::chrono::steady_clock::now() + std::chrono::milliseconds(300);
    beep->NoteOff(0, {});
    std::this_thread::sleep_until(x);

    audio::stopStream();
    audio::terminate();
    delete beep;
    return 0;
}