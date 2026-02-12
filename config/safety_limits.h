#pragma once

#include <cstdint>

/// @brief Safety limits for flight parameters. \namespace ascent::config
namespace ascent::config
{
    /// @brief Safety limits for flight parameters. \struct SafetyLimits
    struct SafetyLimits
    {
        // Altitude, range, speed, tilt, battery voltage, temperature, and communication timeouts
        static constexpr float kMaxAltitudeM = 10000.0f;
        static constexpr float kMaxRangeM = 5000.0f;
        static constexpr float kMaxSpeedMs = 400.0f;
        static constexpr float kMaxTiltDeg = 30.0f;
        static constexpr float kMinBatteryV = 3.0f;
        static constexpr float kWarnBatteryV = 3.3f;
        static constexpr float kMaxBoardTempC = 85.0f;
        static constexpr uint32_t kCommTimeoutMs = 5000;
        static constexpr uint32_t kArmTimeoutMs = 30000;
    };
} // namespace ascent::config