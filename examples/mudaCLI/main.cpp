
#include <iostream>
#include <AudioOutput.h>
#include <BasicAudioManager.h>
#include <cmath>
#include <AudioUnits/Beep.h>
#include <MuDaFilePlayer.h>

int main(int argc, char *argv[]){
    if(argc<2){std::cout << "Must give argument: filename... exiting program."; return 1;}
    auto ao = AudioOutput::instance();
    ao.initialize({1, 44100, 0});
    auto *am = new BasicAudioManager();
    //setup AM
    Beep *instr = new Beep(3);
    auto i = am->addInstrument(instr);
    am->setLevel(i, 0.5f);
    ao.generator = am;
    auto fileData = MuDa::MuDaFileFormat::readFromFile(argv[1]);
    if(!fileData){std::cout<<"File read failed.... exiting program."; return 1;}
    auto *filePlayer = new MuDa::MuDaFilePlayer((*fileData), am);
    ao.startStream();

    filePlayer->start();

    ao.stopStream();
    ao.terminate();
    delete instr;
    delete filePlayer;
    return 0;
}