
#include <gtest/gtest.h>
#include <AudioOutput.h>
#include <thread>

TEST(AudioIOTest, testInitAndTerminate){
    auto aio = AudioOutput();
    EXPECT_EQ(aio.initialize({1, 44100, 0}), 0);
    EXPECT_EQ(aio.terminate(), 0);
}

TEST(AudioIOTest, numDevices){
    auto aio = AudioOutput();
    int numDevices = aio.deviceCount();
    EXPECT_TRUE(numDevices>0);
}

TEST(AudioIOTest, printDevices){
    auto aio = AudioOutput();
    auto err = aio.printDevices();
    EXPECT_EQ(err, 0);
}

TEST(AudioIOTest, StartStopStream){
    auto aio = AudioOutput();
    auto err = aio.initialize({1, 44100, 25});
    EXPECT_EQ(err, 0);

    err = aio.startStream();
    EXPECT_EQ(err, 0);
    err = aio.stopStream();
    EXPECT_EQ(err, 0);
    err = aio.terminate();
    EXPECT_EQ(err, 0);
}

TEST(AudioIOTest, NotStopedStream){
    auto aio = AudioOutput();
    auto err = aio.initialize({1, 44100, 25});
    EXPECT_EQ(err, 0);

    err = aio.startStream();
    EXPECT_EQ(err, 0);
    err = aio.terminate();
    EXPECT_EQ(err, 0);
}