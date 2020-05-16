//
// Created by samt on 16/05/2020.
//

#ifndef MUSICTOOLKIT_MTKTESTENVIRONMENT_H
#define MUSICTOOLKIT_MTKTESTENVIRONMENT_H

#include <gtest/gtest.h>
#include <Audio.h>

class MTKTestEnvironment : public ::testing::Environment {
 public:

  // Override this to define how to set up the environment.
  void SetUp() override {
	  MTK::Audio::AudioSystem::getAudioSystem()->initialize<MTK::Audio::MockAudioWrapper>();
	  MTK::Audio::AudioSystem::getAudioSystem()->setup({ 1, 18000, 4500});
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
  }
};

#endif //MUSICTOOLKIT_MTKTESTENVIRONMENT_H
