add_library(MTKCore SHARED Pitch.cpp IRegularTuning.h LinearTuning.cpp LinearTuning.h IScale.h PeriodicScale.cpp PeriodicScale.h RhythmTree.cpp RhythmTree.h)

target_link_libraries(MTKCore PUBLIC CONAN_PKG::eigen)