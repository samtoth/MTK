//
// Created by Sam on 11/04/2020.
//

#include <gtest/gtest.h>
#include "MTKTestEnvironment.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(new MTKTestEnvironment);
    return RUN_ALL_TESTS();
}