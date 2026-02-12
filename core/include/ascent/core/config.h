#pragma once

#include <cstdint>
#include <cstddef>

/// @brief Core system configuration parameters. \namespace ascent::core
namespace ascent::core
{
    /// @brief Core system configuration parameters. \struct Config
    struct Config
    {
        static constexpr uint32_t kMaxTasks = 16;
        static constexpr uint32_t kMaxEventSubscribers = 32;
        static constexpr uint32_t kMaxEventTypes = 16;
        static constexpr uint32_t kLogBufferSize = 512;
        static constexpr uint32_t kSchedulerTickRate_hz = 1000;
        static constexpr uint32_t kWatchdogTimeout_ms = 2000;
        static constexpr uint32_t kMainLoopRate_hz = 100;
        static constexpr size_t kMaxLogMessageLength = 128;
    };
} // namespace ascent::core
