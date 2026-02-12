#pragma once

#include <cstdint>

/// @brief Sensor configuration parameters. \namespace ascent::config
namespace ascent::config
{
    /// @brief Sensor configuration parameters. \struct SensorConfig
    struct SensorConfig
    {
        // Sample rates
        static constexpr uint32_t kImuSampleRateHz = 1000;
        static constexpr uint32_t kBaroSampleRateHz = 100;
        static constexpr uint32_t kMagSampleRateHz = 100;
        static constexpr uint32_t kGpsSampleRateHz = 10;

        // Sensor ranges
        static constexpr float kAccelRangeG = 16.0f;
        static constexpr float kGyroRangeDps = 2000.0f;
        static constexpr float kMagRangeGauss = 4.0f;

        // Barometer settings
        static constexpr float kSeaLevelPressurePa = 101325.0f;
    };
} // namespace ascent::config