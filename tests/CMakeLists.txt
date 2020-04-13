
ADD_EXECUTABLE(runTests PitchTest.cpp main.cpp)

TARGET_LINK_LIBRARIES(runTests MTKCore gtest gtest_main)
gtest_discover_tests(runTests)

SETUP_TARGET_FOR_COVERAGE(
        coverage_runTests  # Name for custom target.
        runTests        # Name of the test driver executable that runs the tests.
        # NOTE! This should always have a ZERO as exit code
        # otherwise the coverage generation will not complete.
        coverage            # Name of output directory.
)
