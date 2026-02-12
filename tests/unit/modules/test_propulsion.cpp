#include <gtest/gtest.h>
#include "ascent/propulsion/propulsion_controller.h"
#include "ascent/propulsion/ignition_sequence.h"

using namespace ascent::propulsion;
using namespace ascent::core;

class PropulsionTest : public ::testing::Test
{
protected:
    PropulsionController ctrl;
};

TEST_F(PropulsionTest, InitialStateSafe)
{
    EXPECT_EQ(ctrl.getState(), PropulsionState::Safe);
}

TEST_F(PropulsionTest, InitSucceeds)
{
    auto status = ctrl.init();
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST_F(PropulsionTest, ArmFromSafe)
{
    ctrl.init();
    auto status = ctrl.arm();
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(ctrl.getState(), PropulsionState::Armed);
}

TEST_F(PropulsionTest, DisarmFromArmed)
{
    ctrl.init();
    ctrl.arm();
    ctrl.disarm();
    EXPECT_EQ(ctrl.getState(), PropulsionState::Safe);
}

TEST_F(PropulsionTest, IgniteFromArmed)
{
    ctrl.init();
    ctrl.arm();
    auto status = ctrl.ignite();
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST_F(PropulsionTest, IgniteFromSafeFails)
{
    ctrl.init();
    auto status = ctrl.ignite();
    EXPECT_NE(status, StatusCode::Ok);
}

TEST_F(PropulsionTest, Abort)
{
    ctrl.init();
    ctrl.arm();
    ctrl.abort();
    EXPECT_EQ(ctrl.getState(), PropulsionState::Abort);
}

class IgnitionSeqTest : public ::testing::Test
{
protected:
    IgnitionSequence seq;
};

TEST_F(IgnitionSeqTest, InitiallyNotRunning)
{
    EXPECT_FALSE(seq.isRunning());
    EXPECT_FALSE(seq.isComplete());
}

TEST_F(IgnitionSeqTest, AddStep)
{
    auto status = seq.addStep("ignite", 100, 500);
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST_F(IgnitionSeqTest, StartSequence)
{
    seq.addStep("ignite", 0, 100);
    auto status = seq.start();
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_TRUE(seq.isRunning());
}

TEST_F(IgnitionSeqTest, AbortSequence)
{
    seq.addStep("ignite", 0, 100);
    seq.start();
    seq.abort();
    EXPECT_FALSE(seq.isRunning());
}

TEST_F(IgnitionSeqTest, OverflowSteps)
{
    for (uint32_t i = 0; i < IgnitionSequence::kMaxSteps; ++i)
    {
        EXPECT_EQ(seq.addStep("step", 10, 10), StatusCode::Ok);
    }
    EXPECT_NE(seq.addStep("overflow", 10, 10), StatusCode::Ok);
}
