cmake_minimum_required(VERSION 3.12)
project(MusicToolkit VERSION 0.1.1)

add_definitions(-DMTK_VERSION="${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

MESSAGE(STATUS "Music ToolKit Version ${PROJECT_VERSION}")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

option(BUILD_EXAMPLES "Build the example projects" ON)
option(BUILD_PYAPI "Build Python bindings" OFF)
option(BUILD_TESTS "Build the tests" ON)
option(BUILD_DOCS "Build documentation" ON)

add_subdirectory(core)
include_directories(core)
add_subdirectory(audio)
include_directories(audio)
add_subdirectory(MuDa)
include_directories(MuDa)


if(BUILD_PYAPI)
    add_subdirectory(python)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
    include_directories(examples)
endif()

find_package(Threads REQUIRED)
if(BUILD_TESTS)
    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    enable_testing()
    include(GoogleTest)
    IF(CMAKE_COMPILER_IS_GNUCXX)
        include(CodeCoverage)
    ENDIF()
    add_subdirectory(tests)
endif()

if(BUILD_DOCS)
    add_subdirectory(docs)
ENDIF()