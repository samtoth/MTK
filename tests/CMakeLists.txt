ADD_EXECUTABLE(runTests PitchTest.cpp main.cpp)

TARGET_LINK_LIBRARIES(runTests MTKCore gtest gtest_main)

gtest_discover_tests(runTests)