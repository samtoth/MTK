//
// Created by sammy on 08/06/2020.
//


#include <gtest/gtest.h>
#include <AudioUnits/WhiteNoise.h>
#include <Audio.h>

TEST(NoiseTest, average) {
    auto osc = std::make_shared<MTK::Audio::WhiteNoise>();
    MTK::Audio::AUDIO_SYSTEM->setGenerator(osc);

    auto buffer = MTK::Audio::AUDIO_SYSTEM->getAudioWrapper<MTK::Audio::MockAudioWrapper>()->generateBuffer();

    int n = (buffer)->size();
    float mean = 0;
    while(!(buffer->empty())){
        mean += (float)buffer->front();
        (buffer)->pop();
    }
    mean = mean/(float)n;

    ASSERT_LE(std::abs(mean), 0.1f); // Assert that some output has happened
}