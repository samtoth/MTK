add_library(MuDa SHARED MuDaIO.cpp IMuDaStream.cpp MuDaFormat.cpp MuDaFormat.h)
target_link_libraries(MuDa audio)