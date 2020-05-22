add_library(MTKAudio SHARED IAudioManager.h
        IAudioUnit.h IInstrument.h
        BasicAudioManager.cpp BasicAudioManager.h
        AudioUnits/Beep.cpp AudioUnits/Beep.h
        AudioUnits/Oscillators/SinWave.cpp AudioUnits/Oscillators/SinWave.h
        AudioUnits/ADSR.cpp AudioUnits/ADSR.h
        Audio.h Audio.cpp
        AudioUnits/Oscillators/SawWave.cpp AudioUnits/Oscillators/SawWave.h
        AudioUnits/Oscillators/IOscillator.h AudioUnits/Delay.cpp AudioUnits/Delay.h
        Wrappers/PortAudioWrapper.cpp Wrappers/PortAudioWrapper.h
        Wrappers/IAudioWrapper.h Wrappers/MockAudioWrapper.cpp Wrappers/MockAudioWrapper.h
        AudioSampleBuffer.h
        AudioUnits/MockAudioUnit.cpp AudioUnits/MockAudioUnit.h
        Wrappers/WebAudioWrapper.cpp Wrappers/WebAudioWrapper.h)
if(NOT TARGET_WEB)
    target_link_libraries(MTKAudio portaudio)
endif()