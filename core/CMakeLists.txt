add_library(MTKCore SHARED Pitch.cpp IRegularTuning.h LinearTuning.cpp LinearTuning.h)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries(MTKCore Eigen3::Eigen)