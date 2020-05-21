add_executable(MTKWeb mtkWeb.cpp)

SET(testModIn ${CMAKE_CURRENT_SOURCE_DIR}/testModule.js)
SET(testMod ${CMAKE_BINARY_DIR}/lib/testModule.js)

add_custom_command(TARGET MTKWeb COMMAND ${CMAKE_COMMAND} -E copy ${testModIn} ${testMod} VERBATIM)

target_link_libraries(MTKWeb
        MTKCore
        #MTKAudio

        # Emscripten compiler options
        "-o ${CMAKE_BINARY_DIR}/lib/MTK.js"
        "--bind"
        "-s WASM=1"
        "-s MODULARIZE=1"
        "-s EXPORT_ES6=1"
        "-s DISABLE_EXCEPTION_CATCHING=0"
        "-s ALLOW_MEMORY_GROWTH=1"
        )