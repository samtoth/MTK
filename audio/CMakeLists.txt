include_directories(audioUnits)
include_directories(audioUnits/Filters)

add_library(MTKAudio SHARED IAudioManager.h
        IAudioUnit.h IInstrument.h
        BasicAudioManager.cpp BasicAudioManager.h
        AudioUnits/Beep.cpp AudioUnits/Beep.h
        AudioUnits/Oscillators/SinWave.cpp AudioUnits/Oscillators/SinWave.h
        AudioUnits/ADSR.cpp AudioUnits/ADSR.h
        Audio.h Audio.cpp
        AudioUnits/Oscillators/SawWave.cpp AudioUnits/Oscillators/SawWave.h
        AudioUnits/Oscillators/IOscillator.h
        AudioUnits/Filters/Delay.cpp AudioUnits/Filters/Delay.h
        Wrappers/PortAudioWrapper.cpp Wrappers/PortAudioWrapper.h
        Wrappers/IAudioWrapper.h Wrappers/MockAudioWrapper.cpp Wrappers/MockAudioWrapper.h
        AudioSampleBuffer.h
        AudioUnits/MockAudioUnit.cpp AudioUnits/MockAudioUnit.h
        AudioUnits/Filters/IFilter.h VarLenSampleBuffer.cpp VarLenSampleBuffer.h AudioUnits/PluckedString.cpp AudioUnits/PluckedString.h AudioUnits/WhiteNoise.cpp AudioUnits/WhiteNoise.h)

target_link_libraries(MTKAudio portaudio)