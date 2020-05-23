cmake_minimum_required(VERSION 3.12)
project(MusicToolkit VERSION 0.1.1)
add_definitions(-DMTK_VERSION="${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

MESSAGE(STATUS "Music ToolKit Version ${PROJECT_VERSION}")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

OPTION(TARGET_WEB "Compile to WASM using emscripten" OFF)
if(TARGET_WEB)
    add_definitions(-DTARGET_WEB)
    if(NOT DEFINED ENV{EMSDK})
        MESSAGE(FATAL_ERROR "Cannot find EMSDK environment variable")
    endif()

    set(EMSDK_ROOT $ENV{EMSDK})
    set(EMSCRIPTEN_ROOT $ENV{EMSCRIPTEN_ROOT})
    MESSAGE(STATUS "Found emscripten at: ${EMSDK_ROOT}")
    include_directories(${EMSCRIPTEN_ROOT}/system/include)
    SET(CMAKE_TOOLCHAIN_FILE ${EMSDK_ROOT}/cmake/Modules/Platform/Emscripten.cmake)
    SET(CMAKE_CROSSCOMPILING_EMULATOR ${EMSDK_NODE})

    set(EMCC_LINKER_FLAGS "-o ${CMAKE_BINARY_DIR}/dist/HelloWorld.js -s WASM=1 -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH=1 --bind")

    MESSAGE(STATUS "Targeting WASM for Web assembly")
endif()

include(FetchContent)

include_directories(include)

if(NOT TARGET_WEB)
    find_package(portaudio QUIET)
    if(NOT portaudio_found)
        message(STATUS "portaudio not found... installing from https://git.assembla.com/portaudio.git")
        FetchContent_Declare(
                portaudio
                GIT_REPOSITORY https://git.assembla.com/portaudio.git
                GIT_TAG  pa_stable_v190600_20161030
        )
        FetchContent_MakeAvailable(portaudio)
    endif()
endif()

add_subdirectory(core)
include_directories(core)
add_subdirectory(audio)
include_directories(audio)
add_subdirectory(MuDa)
include_directories(MuDa)

if(TARGET_WEB)
    add_subdirectory(web)
endif()

option(BUILD_EXAMPLES "Build the example projects" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
    include_directories(examples)
endif()

find_package(Threads REQUIRED)
option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)
    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    enable_testing()
    find_package(googletest QUIET)
    if(NOT googletest_found)
        message(STATUS "gtest not found... installing from https://github.com/google/googletest.git")
        FetchContent_Declare(
                googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG        v1.10.x
        )
        FetchContent_MakeAvailable(googletest)
    endif()
    include(GoogleTest)
    include(CodeCoverage)
    add_subdirectory(tests)
endif()

option(BUILD_DOCS "Build documentation" ON)
if(BUILD_DOCS)
    add_subdirectory(docs)
ENDIF()