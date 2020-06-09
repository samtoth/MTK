#include <gtest/gtest.h>
#include <VarLenSampleBuffer.h>

TEST(VarBufferTest, pushMax) {
    auto queue = MTK::Audio::VarLenSampleBuffer<int>(5, 10);
    for (int i = 0; i < 5; i++) {
        queue.push(i);
    }
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(queue.front(), i);
        queue.pop();
    }
}

TEST(VarBufferTest, pushWraparound) {
    auto queue = MTK::Audio::VarLenSampleBuffer<int>(5, 10);
    for (int i = 0; i < 10; i++) {
        queue.push(i);
    }
    for (int i = 5; i < 10; i++) {
        ASSERT_EQ(queue.front(), i);
        queue.pop();
    }
}

TEST(VarBufferTest, pushExpand) {
    auto queue = MTK::Audio::VarLenSampleBuffer<int>(5, 10);
    for (int i = 0; i < 10; i++) {
        queue.push(i);
    }
    queue.setLength(7);
    for (int i = 3; i < 10; i++) {
        ASSERT_EQ(queue.front(), i);
        queue.pop();
    }
}

TEST(VarBufferTest, pushShrink) {
    auto queue = MTK::Audio::VarLenSampleBuffer<int>(5, 10);
    for (int i = 0; i < 10; i++) {
        queue.push(i);
    }
    queue.setLength(2);
    for (int i = 8; i < 10; i++) {
        ASSERT_EQ(queue.front(), i);
        queue.pop();
    }
}