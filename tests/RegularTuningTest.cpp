//
// Created by samt on 14/04/2020.
//

#include <LinearTuning.h>
#include <gtest/gtest.h>
using namespace MTK::Core;

#define tuningPar std::tuple<float, float, float>

class LinearTuningTestP :public ::testing::TestWithParam<tuningPar> {
protected:
    LinearTuning *t;
};

#define TestCoord(value, expected) if(auto v = (t->getCoordinate(value))){EXPECT_TRUE((*v).isApprox(expected));}else{FAIL();}

TEST_P(LinearTuningTestP, LinearTuningTestCoordinateFromFrequency){
    float referencePitch = std::get<0>(GetParam());
    float period = std::get<1>(GetParam());
    float generator = std::get<2>(GetParam());

    t = new LinearTuning(period, generator, referencePitch);

    EXPECT_FALSE(t->getCoordinate(referencePitch + 0.6f));
    TestCoord(referencePitch * generator, Eigen::Vector2i(0,1))
    TestCoord(referencePitch * period * generator, Eigen::Vector2i(1,1))
    TestCoord(referencePitch * period * pow(generator, 7), Eigen::Vector2i(1,7))
    delete t;
}

INSTANTIATE_TEST_SUITE_P(LinearTuningTest, LinearTuningTestP, ::testing::Values(
        tuningPar(440.f, 2, powf(2, 7.f/12))
        ));

class LinearTuningTestF : public ::testing::Test {

public:
    LinearTuning *t;
    float gen;
    float period;
protected:

    // You can define per-test set-up logic as usual.
    virtual void SetUp() {
        period = 2;
        gen = 2*std::pow(5, 1.f/4);
        t = new LinearTuning(period, gen, 440.f);
    }

    // You can define per-test tear-down logic as usual.
    virtual void TearDown() {
        delete t;
    }

    // Some expensive resource shared by all tests.
};

TEST_F(LinearTuningTestF, checkFundamentalFrequency){
    EXPECT_FLOAT_EQ(t->getFundamentalFrequency(), 440.f);
    t->setFundamentalFrequency(441.f);
    EXPECT_FLOAT_EQ(t->getFundamentalFrequency(), 441.f);
}
TEST_F(LinearTuningTestF, checkCoordinate00){
    EXPECT_FLOAT_EQ(t->getFrequency(Eigen::Vector2i(0,0)), t->getFundamentalFrequency());
}

//Migrated to scale class!!
/*TEST_F(LinearTuningTestF, getDistanceFromNote){
    EXPECT_FLOAT_EQ(t->distanceFromNote(440.f), 1);
    EXPECT_FLOAT_EQ(t->distanceFromNote(440.f*1.005f), 1.005f);
    EXPECT_FLOAT_EQ(t->distanceFromNote(440.f*period*1.01f), 1.01f);
}*/

TEST_F(LinearTuningTestF, getCoordinateFromFreqFailCase){
    EXPECT_FALSE(t->getCoordinate(441.f));
}

TEST_F(LinearTuningTestF, getCoordinateFromFreq){
    EXPECT_TRUE((*(t->getCoordinate(440.f*gen))).isApprox(Eigen::Vector2i(0,1)));
    EXPECT_TRUE((*(t->getCoordinate(440.f*period*gen))).isApprox(Eigen::Vector2i(1,1)));
    EXPECT_TRUE((*(t->getCoordinate(440.f*period*pow(gen,7)))).isApprox(Eigen::Vector2i(1,7)));
}

TEST_F(LinearTuningTestF, getFrequency){
    EXPECT_EQ(t->getFrequency(Vector(0,1)),440.f*gen);
    EXPECT_EQ(t->getFrequency(Vector(1,0)),440.f*period);
}