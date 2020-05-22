add_executable(MTKWeb mtkWeb.cpp)

target_link_libraries(MTKWeb MTKCore MTKAudio)

set_target_properties(MTKWeb PROPERTIES LINK_FLAGS "${EMCC_LINKER_FLAGS}")