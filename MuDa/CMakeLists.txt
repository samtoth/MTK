add_library(MuDa SHARED MuDaIO.cpp IMuDaStream.cpp MuDaFileFormat.h)
target_link_libraries(MuDa audio)