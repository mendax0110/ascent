#include <gtest/gtest.h>
#include "event_bus.h"

using namespace ascent::core;

static EventId s_received_id = EventId::None;
static uint32_t s_received_param = 0;
static uint32_t s_callback_count = 0;

static void testCallback(const Event& e)
{
    s_received_id = e.id;
    s_received_param = e.param;
    ++s_callback_count;
}

static void anotherCallback(const Event&)
{
    s_callback_count += 100;
}

class EventBusTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        EventBus::init();
        s_received_id = EventId::None;
        s_received_param = 0;
        s_callback_count = 0;
    }
};

TEST_F(EventBusTest, SubscribeSucceeds)
{
    const auto status = EventBus::subscribe(EventId::SystemInit, testCallback);
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST_F(EventBusTest, SubscribeNullCallbackFails)
{
    const auto status = EventBus::subscribe(EventId::SystemInit, nullptr);
    EXPECT_EQ(status, StatusCode::InvalidParam);
}

TEST_F(EventBusTest, PublishInvokesSubscriber)
{
    EventBus::subscribe(EventId::SystemInit, testCallback);
    const Event evt{EventId::SystemInit, 1234, 42};
    EventBus::publish(evt);

    EXPECT_EQ(s_received_id, EventId::SystemInit);
    EXPECT_EQ(s_received_param, 42u);
    EXPECT_EQ(s_callback_count, 1u);
}

TEST_F(EventBusTest, OnlyMatchingEventInvokesSubscriber)
{
    EventBus::subscribe(EventId::SystemInit, testCallback);
    const Event evt{EventId::AbortRequested, 0, 0};
    EventBus::publish(evt);

    EXPECT_EQ(s_received_id, EventId::None);
    EXPECT_EQ(s_callback_count, 0u);
}

TEST_F(EventBusTest, MultipleSubscribers)
{
    EventBus::subscribe(EventId::SystemInit, testCallback);
    EventBus::subscribe(EventId::SystemInit, anotherCallback);
    const Event evt{EventId::SystemInit, 0, 0};
    EventBus::publish(evt);

    EXPECT_EQ(s_callback_count, 101u);
}

TEST_F(EventBusTest, InitClearsSubscriptions)
{
    EventBus::subscribe(EventId::SystemInit, testCallback);
    EventBus::init();

    const Event evt{EventId::SystemInit, 0, 0};
    EventBus::publish(evt);

    EXPECT_EQ(s_callback_count, 0u);
}
