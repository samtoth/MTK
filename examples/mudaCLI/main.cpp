
#include <iostream>
#include <Audio.h>
#include <BasicAudioManager.h>
#include <utility>
#include <AudioUnits/Beep.h>
#include <MuDaFilePlayer.h>
#include <AudioUnits/Oscillators/SawWave.h>
#include <PortAudioWrapper.h>

#define fail() std::cout << "Usage: " << std::endl << "        MuDaCLI -e <file>    : writes the example file to file name" << std::endl << "        MuDaCLI -p <file>    : plays the given file" << std::endl; return 1

int playFile(const std::string& fileName ){
    MTK::Audio::AudioSystem::getAudioInstance()->initialize<MTK::Audio::PortAudioWrapper>();
    MTK::Audio::AudioSystem::getAudioInstance()->setup({1, 44100, 0});
    auto am = std::make_shared<MTK::Audio::BasicAudioManager>();
    //setup AM
    auto *instr = new MTK::Audio::Beep();
    instr->addVoices<MTK::Audio::SawWave>(3);
    auto i = am->addInstrument(instr);
    am->setLevel(i, 0.5f);
    MTK::Audio::AudioSystem::getAudioInstance()->setGenerator(am);
    auto fileData = MTK::MuDa::MuDaFileFormat::readFromFile(fileName);
    if(!fileData){std::cout<<"File read failed.... exiting program." << std::endl; return 1;}
    auto *filePlayer = new MTK::MuDa::MuDaFilePlayer((*fileData), am);
    MTK::Audio::AudioSystem::getAudioInstance()->startStream();

    filePlayer->start();

    MTK::Audio::AudioSystem::getAudioInstance()->stopStream();
    MTK::Audio::AudioSystem::getAudioInstance()->terminate();
    delete instr;
    delete filePlayer;
    return 0;
}

int writeFile(std::string fileName){
    auto Mf = std::make_shared<MTK::MuDa::MuDaFileFormat>(140);
    std::map<uint32_t, float> params = {{0, 525.f}};

    Mf->appendStartMessage();

    Mf->appendNoteMessage(0, MTK::MuDa::MessageCodes::noteOn, {0, 0, params});
    Mf->appendNoteMessage(30, MTK::MuDa::MessageCodes::noteOff, {0, 0, {}});

    Mf->appendNoteMessage(50, MTK::MuDa::MessageCodes::noteOn, {0, 0, params});
    Mf->appendNoteMessage(80, MTK::MuDa::MessageCodes::noteOff, {0, 0, {}});

    Mf->appendNoteMessage(100, MTK::MuDa::MessageCodes::noteOn, {0, 0, params});

    Mf->appendNoteMessage(150, MTK::MuDa::MessageCodes::noteChange, {0, 0, {{0, 440.f}}});
    Mf->appendNoteMessage(300, MTK::MuDa::MessageCodes::noteOff,{0, 0, {}});

    Mf->appendEndMessage(500);

    if(Mf->writeToFile(std::move(fileName))){
        return 0;
    }else{
        std::cout << "File writing failed" << std::endl;
        return 1;
    }
}


int main(int argc, char *argv[]){
    if(argc<3){fail();}
    if(std::string("-e")==argv[1]) {
        return writeFile(argv[2]);
    }else if(std::string("-p")==argv[1]){
        return playFile(argv[2]);
    }else {
        fail();
    }
}