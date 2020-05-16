//
// Created by samt on 16/05/2020.
//

#include <gtest/gtest.h>
#include <Audio.h>
#include <AudioUnits/Oscillators/SinWave.h>
#include <AudioUnits/Oscillators/SawWave.h>
#include <thread>
#include <cmath>
template <typename T>
class OscilatorTests : public ::testing::Test {

public:
protected:
	// Per-test-suite set-up.
	// Called before the first test in this test suite.
	// Can be omitted if not needed.
	static void SetUpTestSuite() {
	}

	// Per-test-suite tear-down.
	// Called after the last test in this test suite.
	// Can be omitted if not needed.
	static void TearDownTestSuite() {
	}

	// You can define per-test set-up logic as usual.
	virtual void SetUp() {
	}

	// You can define per-test tear-down logic as usual.
	virtual void TearDown() {
	}

	// Some expensive resource shared by all tests.
};

using MyTypes = ::testing::Types<MTK::Audio::SinWave, MTK::Audio::SawWave>;
TYPED_TEST_SUITE(OscilatorTests, MyTypes);

TYPED_TEST(OscilatorTests, doesOutput) {
	auto osc = std::make_shared<TypeParam>();
	osc->setFrequency(440.f);
	MTK::Audio::AudioSystem::getAudioSystem()->setGenerator(osc);

	auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000);
	MTK::Audio::AudioSystem::getAudioSystem()->startStream();
	std::this_thread::sleep_until(x);

	MTK::Audio::AudioSystem::getAudioSystem()->stopStream();
	auto buffer = MTK::Audio::AudioSystem::getAudioSystem()->getTestBuffer();
	if(!buffer){
		FAIL();
	}
	int n = (*buffer)->size();
	float rootMeanSqr = 0;
	while(!(*buffer)->empty()){
		rootMeanSqr += powf((float)(*buffer)->front(), 2.f);
		(*buffer)->pop();
	}
	rootMeanSqr = powf(rootMeanSqr/(float)n, 0.5f);

	ASSERT_TRUE(rootMeanSqr > 0.f); // Assert that some output has happened
}