add_library(audio SHARED test.cpp IAudioManager.h IGenerator.h IInstrument.h)

target_link_libraries(audio)