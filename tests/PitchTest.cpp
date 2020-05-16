//
// Created by Sam on 11/04/2020.
//

#include <Pitch.h>
#include <gtest/gtest.h>
namespace MTK::Tests {
    class PitchTest : public ::testing::Test {

    public:
        MTK::Core::Pitch *p;
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
            p = new Core::Pitch(440.f);
        }

        // You can define per-test tear-down logic as usual.
        virtual void TearDown() {
            delete p;
        }

        // Some expensive resource shared by all tests.
    };


    TEST_F(PitchTest, initialize) {
        EXPECT_FLOAT_EQ(p->getFrequency(), 440.f);
    }

    TEST_F(PitchTest, setFrequency) {
        EXPECT_FLOAT_EQ(p->getFrequency(), 440.f);
        p->setFrequency(356.7f);
        EXPECT_FLOAT_EQ(p->getFrequency(), 356.7f);
    }
}