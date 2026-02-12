#pragma once

#include <cstdint>

/// @brief Telemetry configuration parameters. \namespace ascent::config
namespace ascent::config
{
    /// @brief Telemetry configuration parameters. \struct TelemetryConfig
    struct TelemetryConfig
    {
        // Telemetry transmission rates, packet sizes, and logging settings
        static constexpr uint32_t kTxRateHz = 10;
        static constexpr uint32_t kLogRateHz = 100;
        static constexpr uint32_t kMaxPacketSize = 256;
        static constexpr uint32_t kLogBufferSize = 4096;
        static constexpr bool kEnableLogging = true;
    };
} // namespace ascent::config