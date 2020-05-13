cmake_minimum_required(VERSION 3.12)
project(MusicToolkit VERSION 0.1.1)

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

include(FetchContent)

include_directories(include)

find_package(portaudio QUIET)
if(NOT portaudio_found)
    message(STATUS "portaudio not found... installing from https://git.assembla.com/portaudio.git")
    FetchContent_Declare(
            portaudio
            GIT_REPOSITORY https://git.assembla.com/portaudio.git
    )
    FetchContent_MakeAvailable(portaudio)
endif()


add_subdirectory(core)
include_directories(core)
add_subdirectory(audio)
include_directories(audio)
add_subdirectory(MuDa)
include_directories(MuDa)

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