add_library(MuDa SHARED MuDaFilePlayer.cpp IMuDaStream.cpp MuDaFileFormat.h)
target_link_libraries(MuDa MTKAudio)