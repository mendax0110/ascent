#include <gtest/gtest.h>
#include "system.h"
#include "ascent/propulsion/propulsion_controller.h"
#include "ascent/safety/safety_monitor.h"
#include "ascent/navigation/navigation_system.h"

using namespace ascent;
using namespace ascent::core;

class FlightSequenceTest : public ::testing::Test
{
protected:
    System system;
    propulsion::PropulsionController propulsion;
    safety::SafetyMonitor safety;
    navigation::NavigationSystem nav;

    void SetUp() override
    {
        system.init();
        propulsion.init();
        safety.init();
        nav.init();
    }
};

TEST_F(FlightSequenceTest, SystemStartsIdle)
{
    EXPECT_EQ(system.getState(), SystemState::Idle);
}

TEST_F(FlightSequenceTest, TransitionToArmed)
{
    auto status = system.requestStateTransition(SystemState::Armed);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(system.getState(), SystemState::Armed);
}

TEST_F(FlightSequenceTest, ArmPropulsionWithSystem)
{
    system.requestStateTransition(SystemState::Armed);
    auto status = propulsion.arm();
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(propulsion.getState(), propulsion::PropulsionState::Armed);
}

TEST_F(FlightSequenceTest, FullSequenceIdleToLaunch)
{
    EXPECT_EQ(system.requestStateTransition(SystemState::Armed), StatusCode::Ok);
    EXPECT_EQ(system.requestStateTransition(SystemState::Launch), StatusCode::Ok);
    EXPECT_EQ(system.getState(), SystemState::Launch);
}

TEST_F(FlightSequenceTest, AbortFromAnyState)
{
    system.requestStateTransition(SystemState::Armed);
    system.requestStateTransition(SystemState::Launch);

    auto status = system.requestStateTransition(SystemState::Abort);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(system.getState(), SystemState::Abort);
}

TEST_F(FlightSequenceTest, SafetyNoAbortInitially)
{
    EXPECT_FALSE(safety.isAbortRequired());
}

TEST_F(FlightSequenceTest, PropulsionAbortSetsState)
{
    propulsion.arm();
    propulsion.abort();
    EXPECT_EQ(propulsion.getState(), propulsion::PropulsionState::Abort);
}
