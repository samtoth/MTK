add_library(audio SHARED IAudioManager.h IAudioUnit.h IInstrument.h AudioOutput.cpp AudioOutput.h BasicAudioManager.cpp BasicAudioManager.h)

target_link_libraries(audio portaudio)