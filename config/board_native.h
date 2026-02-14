#pragma once

#include <cstdint>

/// @brief Board configuration for native simulation environment. \namespace ascent::config
namespace ascent::config
{
    /// @brief Configuration parameters for native simulation environment. \struct BoardNative
    struct BoardNative
    {
        static constexpr uint32_t kSystemClockHz = 0;
        static constexpr uint32_t kUartBaud = 115200;
        static constexpr bool kHasHardwareWatchdog = false;
        static constexpr bool kHasRealHardware = false;
    };
} // namespace ascent::config