#pragma once

#include <cstdint>
#include <cstddef>
#include <functional>
#include <array>
#include "ascent/core/types.h"
#include "ascent/core/config.h"

/// @brief Publish-subscribe event bus for inter-component communication. \namespace ascent::core
namespace ascent::core
{
    /// @brief Publish-subscribe event bus for inter-component communication. \enum EventId
    enum class EventId : uint16_t
    {
        None = 0,
        SystemInit,
        SystemReady,
        SensorDataReady,
        NavigationUpdate,
        TelemetryTick,
        CommandReceived,
        ArmRequested,
        LaunchRequested,
        AbortRequested,
        ApogeeDetected,
        LandingDetected,
        LowBattery,
        HardwareFault,
        Count
    };

    /// @brief Event structure for passing information to subscribers. \struct Event
    struct Event
    {
        EventId id = EventId::None;
        uint32_t timestamp_ms = 0;
        uint32_t param = 0;
    };

    using EventCallback = void(*)(const Event&);

    /**
     * \class EventBus
     * @brief Static publish-subscribe event bus.
     *
     * Fixed-capacity, no heap allocation. Supports up to
     * Config::kMaxEventSubscribers subscribers per event type.
     */
    class EventBus
    {
    public:
        EventBus() = delete;
        ~EventBus() = delete;

        /**
         * @brief Initialize the event bus.
         */
        static void init() noexcept;

        /**
         * @brief Subscribe to an event type.
         * @param id Event type to subscribe to.
         * @param callback Function to call on event.
         * @return Ok if subscribed, error if subscriber limit reached.
         */
        static StatusCode subscribe(EventId id, EventCallback callback) noexcept;

        /**
         * @brief Publish an event to all subscribers.
         * @param event Event to publish.
         */
        static void publish(const Event& event) noexcept;

    private:
        /// @brief Internal structure to track subscribers for each event type. \struct Subscription
        struct Subscription
        {
            EventCallback callback = nullptr;
        };

        static std::array<std::array<Subscription, Config::kMaxEventSubscribers>, static_cast<size_t>(EventId::Count)> s_subscribers;
        static std::array<uint8_t, static_cast<size_t>(EventId::Count)> s_subscriber_count;
    };
} // namespace ascent::core
