//
// Created by samt on 03/05/2020.
//

#ifndef MUSICTOOLKIT_AUDIO_H
#define MUSICTOOLKIT_AUDIO_H

#include <AudioOutput.h>

std::unique_ptr<AudioOutput> audioInstance;
std::once_flag onceFlag;

namespace audio{
    void initialize(){
        std::call_once(onceFlag, [](){ audioInstance = std::make_unique<AudioOutput>();});
    }

    void cleanup

    void terminate(){}


}

#endif //MUSICTOOLKIT_AUDIO_H
