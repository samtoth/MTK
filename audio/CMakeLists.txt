add_library(audio SHARED IAudioManager.h IAudioUnit.h IInstrument.h AudioOutput.cpp AudioOutput.h BasicAudioManager.cpp BasicAudioManager.h AudioUnits/Beep.cpp AudioUnits/Beep.h AudioUnits/SinWave.cpp AudioUnits/SinWave.h AudioUnits/ADSR.cpp AudioUnits/ADSR.h Audio.h)

target_link_libraries(audio portaudio)