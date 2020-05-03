
#include <iostream>
#include <AudioOutput.h>
#include <BasicAudioManager.h>
#include <cmath>
#include <AudioUnits/Beep.h>
#include <MuDaFilePlayer.h>

int main(int argc, char *argv[]){
    auto ao = AudioOutput::instance();
    ao.initialize({1, 44100, 0});
    int devices = ao.deviceCount();
    for(int i = 0; i < devices; i++){
        std::cout << "Device " << i << ": " << (*ao.getDeviceInfo(i))->name << std::endl;
    }
    auto *beep = new Beep(1);
    ao.setGenerator(beep);
    ao.startStream();

    auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(4000);
    beep->NoteOn(0, {{0, 440.f}});
    std::this_thread::sleep_until(x);
    beep->NoteOff(0, {});

    ao.stopStream();
    ao.terminate();
    delete beep;
    return 0;
}