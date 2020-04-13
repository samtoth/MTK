cmake_minimum_required(VERSION 3.11)
project(MusicToolkit VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

MESSAGE(STATUS "Music ToolKit Version ${PROJECT_VERSION}")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

add_subdirectory(core)
include_directories(core)

include(FetchContent)
find_package(Threads REQUIRED)
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        v1.10.x
    )
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
    include(CodeCoverage)
    add_subdirectory(tests)
endif()


add_subdirectory(docs)