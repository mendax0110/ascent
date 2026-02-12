#include <gtest/gtest.h>
#include "scheduler.h"

using namespace ascent::core;

static uint32_t s_call_count = 0;

static void dummyTask() { ++s_call_count; }
static void anotherTask() { s_call_count += 10; }

class SchedulerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        s_call_count = 0;
    }

    Scheduler sched;
};

TEST_F(SchedulerTest, InitiallyEmpty)
{
    EXPECT_EQ(sched.getTaskCount(), 0u);
}

TEST_F(SchedulerTest, AddTask)
{
    auto status = sched.addTask("task1", dummyTask, 100);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(sched.getTaskCount(), 1u);
}

TEST_F(SchedulerTest, AddMultipleTasks)
{
    EXPECT_EQ(sched.addTask("t1", dummyTask, 100), StatusCode::Ok);
    EXPECT_EQ(sched.addTask("t2", anotherTask, 200), StatusCode::Ok);
    EXPECT_EQ(sched.getTaskCount(), 2u);
}

TEST_F(SchedulerTest, RejectsNullFunction)
{
    auto status = sched.addTask("null", nullptr, 100);
    EXPECT_EQ(status, StatusCode::InvalidParam);
    EXPECT_EQ(sched.getTaskCount(), 0u);
}

TEST_F(SchedulerTest, RejectsNullName)
{
    auto status = sched.addTask(nullptr, dummyTask, 100);
    EXPECT_EQ(status, StatusCode::InvalidParam);
}

TEST_F(SchedulerTest, TickExecutesDueTask)
{
    sched.addTask("task", dummyTask, 100);
    sched.tick(0);
    EXPECT_EQ(s_call_count, 1u);
}

TEST_F(SchedulerTest, TickRespectsperiod)
{
    sched.addTask("task", dummyTask, 100);
    sched.tick(0);
    EXPECT_EQ(s_call_count, 1u);

    sched.tick(50);
    EXPECT_EQ(s_call_count, 1u);

    sched.tick(100);
    EXPECT_EQ(s_call_count, 2u);
}

TEST_F(SchedulerTest, DisableTaskPreventsExecution)
{
    sched.addTask("task", dummyTask, 100);
    sched.setTaskEnabled("task", false);
    sched.tick(0);
    EXPECT_EQ(s_call_count, 0u);
}

TEST_F(SchedulerTest, ReenableTask)
{
    sched.addTask("task", dummyTask, 100);
    sched.setTaskEnabled("task", false);
    sched.tick(0);
    EXPECT_EQ(s_call_count, 0u);

    sched.setTaskEnabled("task", true);
    sched.tick(100);
    EXPECT_EQ(s_call_count, 1u);
}

TEST_F(SchedulerTest, SetEnabledUnknownTaskFails)
{
    sched.addTask("known", dummyTask, 100);
    auto status = sched.setTaskEnabled("unknown", false);
    EXPECT_EQ(status, StatusCode::InvalidParam);
}
