//
// Created by sammy on 22/05/2020.
//

#include <emscripten/bind.h>
#include <string>
#include <Audio.h>
#include <Wrappers/WebAudioWrapper.h>

std::string getVersion(){
    return MTK_VERSION;
}

int initAudio(){
    MTK::Audio::AudioSystem::getAudioSystem()->initialize<MTK::Audio::WebAudioWrapper>();
}

EMSCRIPTEN_BINDINGS(MTK_module) {
        emscripten::function("getVersion", &getVersion);
        emscripten::function("initAudio", &initAudio);
}