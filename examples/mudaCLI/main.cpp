
#include <iostream>
#include <AudioOutput.h>
#include <BasicAudioManager.h>
#include <cmath>
#include <AudioUnits/Beep.h>

int main(){
    auto ao = AudioOutput();
    /*int devices = ao.deviceCount();
    for(int i = 0; i < devices; i++){
        std::cout << "Device " << i << ": " << (*ao.getDeviceInfo(i))->name << std::endl;
    }*/
    ao.initialize({1, 44100, 0});
    auto *am = new BasicAudioManager();
    //setup AM
    Beep *instr = new Beep(3);
    auto i = am->addInstrument(instr);
    ao.generator = am;
    ao.startStream();

    ao.stopStream();
    ao.terminate();
    delete am;
    delete instr;
    return 0;
}