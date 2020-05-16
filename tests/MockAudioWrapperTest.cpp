//
// Created by samt on 16/05/2020.
//

#include <gtest/gtest.h>
#include <Audio.h>
#include <AudioUnits/MockAudioUnit.h>
#include <thread>

TEST(MockAudioWrapperTest, bufferTest){
	auto mockAUnit = std::make_shared<MTK::Audio::MockAudioUnit>();
	MTK::Audio::AudioSystem::getAudioSystem()->setGenerator(mockAUnit);

	MTK::Audio::AudioSystem::getAudioSystem()->startStream();
	auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000);
	std::this_thread::sleep_until(x);

	MTK::Audio::AudioSystem::getAudioSystem()->stopStream();
	auto buffer = MTK::Audio::AudioSystem::getAudioSystem()->getTestBuffer();
	if(!buffer){
		FAIL();
	}
	while(!(*buffer)->empty()){
		EXPECT_FLOAT_EQ((*buffer)->front(), 0.5f);
		(*buffer)->pop();
	}
}