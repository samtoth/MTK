//
// Created by samt on 14/04/2020.
//

#include <LinearTuning.h>
#include <gtest/gtest.h>

class LinearTuningTest : public ::testing::Test {

public:
    LinearTuning *t;
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
        t = new LinearTuning(2, std::pow(2, 7.f/12.f), 440.f);
    }

    // You can define per-test tear-down logic as usual.
    virtual void TearDown() {
        delete t;
    }

    // Some expensive resource shared by all tests.
};

TEST_F(LinearTuningTest, checkFundamentalFrequency){
    EXPECT_FLOAT_EQ(t->getFundamentalFrequency(), 440.f);
    EXPECT_FLOAT_EQ(t->getFrequency(Eigen::Vector2f(0,0)), t->getFundamentalFrequency());
}
