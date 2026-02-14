#include <gtest/gtest.h>
#include "system.h"

using namespace ascent::core;

class SystemTest : public ::testing::Test
{
protected:
    System system;
};

TEST_F(SystemTest, InitialStateBoot)
{
    EXPECT_EQ(system.getState(), SystemState::Boot);
}

TEST_F(SystemTest, InitSucceeds)
{
    const auto status = system.init();
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST_F(SystemTest, InitTransitionsToIdle)
{
    system.init();
    EXPECT_EQ(system.getState(), SystemState::Idle);
}

TEST_F(SystemTest, DoubleInitIsIdempotent)
{
    system.init();
    const auto status = system.init();
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(system.getState(), SystemState::Idle);
}

TEST_F(SystemTest, ValidTransitionIdleToArmed)
{
    system.init();
    const auto status = system.requestStateTransition(SystemState::Armed);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(system.getState(), SystemState::Armed);
}

TEST_F(SystemTest, InvalidTransitionBootToArmed)
{
    const auto status = system.requestStateTransition(SystemState::Armed);
    EXPECT_NE(status, StatusCode::Ok);
    EXPECT_EQ(system.getState(), SystemState::Boot);
}

TEST_F(SystemTest, AbortAlwaysAllowed)
{
    system.init();
    const auto status = system.requestStateTransition(SystemState::Abort);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(system.getState(), SystemState::Abort);
}

TEST_F(SystemTest, FaultAlwaysAllowed)
{
    system.init();
    const auto status = system.requestStateTransition(SystemState::Fault);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(system.getState(), SystemState::Fault);
}
