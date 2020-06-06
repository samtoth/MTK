if(BUILD_PYAPI)
    add_subdirectory(pybind11)
endif()

include(FetchContent)

set(include_eigen "thirdparty/eigen" PARENT_SCOPE)

find_package(portaudio QUIET)
if(NOT portaudio_found)
    #message(STATUS "checking for portaudio... installing from https://git.assembla.com/portaudio.git")
    FetchContent_Declare(
            portaudio
            GIT_REPOSITORY https://git.assembla.com/portaudio.git
            GIT_TAG  pa_stable_v190600_20161030
    )
    FetchContent_MakeAvailable(portaudio)
endif()

if(BUILD_TESTS)
    find_package(googletest QUIET)
    if(NOT googletest_found)
        #message(STATUS "gtest not found... installing from https://github.com/google/googletest.git")
        FetchContent_Declare(
                googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG        v1.10.x
        )
        FetchContent_MakeAvailable(googletest)
    endif()
endif()