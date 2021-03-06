//
// Created by samt on 16/05/2020.
//

#include <gtest/gtest.h>
#include <AudioSampleBuffer.h>

#include <memory>

TEST(SampleBufferTest, pushMax){
	auto queue = MTK::Audio::AudioSampleBuffer<int>(10);
	for(int i = 0; i<10; i++){
		queue.push(i);
	}
	for(int i = 0; i<10; i++){
		ASSERT_EQ(queue.front(), i);
		queue.pop();
	}
}

TEST(SampleBufferTest, pushWraparound){
    auto queue = MTK::Audio::AudioSampleBuffer<int>(10);
	for(int i = 0; i<12; i++){
		queue.push(i);
	}
	for(int i = 2; i<12; i++){
		ASSERT_EQ(queue.front(), i);
		queue.pop();
	}
}