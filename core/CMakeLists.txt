add_library(MTKCore SHARED Pitch.cpp IRegularTuning.h LinearTuning.cpp LinearTuning.h IScale.h PeriodicScale.cpp PeriodicScale.h)

#target_include_directories(MTKCore PRIVATE /include/Eigen)