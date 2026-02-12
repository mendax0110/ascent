#include "event_bus.h"
#include <algorithm>
#include <array>

using namespace ascent::core;

std::array<std::array<EventBus::Subscription, Config::kMaxEventSubscribers>, static_cast<size_t>(EventId::Count)> EventBus::s_subscribers = {};
std::array<uint8_t, static_cast<size_t>(EventId::Count)> EventBus::s_subscriber_count = {};

void EventBus::init() noexcept
{
    for (auto& row : s_subscribers)
    {
        for (auto& sub : row)
        {
            sub = Subscription{};
        }
    }
    s_subscriber_count.fill(0);
}

StatusCode EventBus::subscribe(EventId id, EventCallback callback) noexcept
{
    const auto idx = static_cast<size_t>(id);
    if (idx >= static_cast<size_t>(EventId::Count))
    {
        return StatusCode::InvalidParam;
    }
    if (callback == nullptr)
    {
        return StatusCode::InvalidParam;
    }
    if (s_subscriber_count[idx] >= Config::kMaxEventSubscribers)
    {
        return StatusCode::OutOfMemory;
    }

    s_subscribers[idx][s_subscriber_count[idx]].callback = callback;
    ++s_subscriber_count[idx];
    return StatusCode::Ok;
}

void EventBus::publish(const Event& event) noexcept
{
    const auto idx = static_cast<size_t>(event.id);
    if (idx >= static_cast<size_t>(EventId::Count))
    {
        return;
    }

    for (uint8_t i = 0; i < s_subscriber_count[idx]; ++i)
    {
        if (s_subscribers[idx][i].callback != nullptr)
        {
            s_subscribers[idx][i].callback(event);
        }
    }
}
