ADD_EXECUTABLE(runTests PitchTest.cpp main.cpp RegularTuningTest.cpp PeriodicScaleTest.cpp MuDaFileTest.cpp SampleBufferTest.cpp OscilatorTests.cpp MockAudioWrapperTest.cpp MTKTestEnvironment.h VarLenSampleBufferTest.cpp noiseTest.cpp)

TARGET_LINK_LIBRARIES(runTests MTKCore MTKAudio MuDa gtest gtest_main)
gtest_discover_tests(runTests)

SETUP_TARGET_FOR_COVERAGE(
        generateCoverage  # Name for custom target.
        runTests        # Name of the test driver executable that runs the tests.
        # NOTE! This should always have a ZERO as exit code
        # otherwise the coverage generation will not complete.
        coverage            # Name of output directory.
)
