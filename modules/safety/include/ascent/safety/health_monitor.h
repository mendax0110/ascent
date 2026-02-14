#pragma once

#include "ascent/core/types.h"
#include <cstdint>

/// @brief System health monitoring. Monitors battery voltage, temperature, and sensor status. \namespace ascent::safety
namespace ascent::safety
{
    /// @brief Health status structure. \struct ascent::safety::HealthStatus
    struct HealthStatus
    {
        float battery_voltage = 0;
        float board_temperature = 0;
        uint8_t sensor_health = 0; //bitmask sensor status
        bool all_ok = false;
    };

    /**
     * \class HealthMonitor
     * @brief Monitors system health parameters.
     */
    class HealthMonitor
    {
    public:
        HealthMonitor() noexcept;
        ~HealthMonitor() = default;

        HealthMonitor(const HealthMonitor&) = delete;
        HealthMonitor& operator=(const HealthMonitor&) = delete;
        HealthMonitor(HealthMonitor&&) = default;
        HealthMonitor& operator=(HealthMonitor&&) = default;

        /**
         * @brief Run health check cycle.
         */
        void update() noexcept;

        /**
         * @brief Get current health status.
         * @return Current health status.
         */
        [[nodiscard]] const HealthStatus& getStatus() const noexcept;

        /**
         * @brief Set battery voltage thresholds.
         * @param min_v Minimum safe voltage.
         * @param warn_v Warning threshold voltage.
         */
        void setBatteryLimits(float min_v, float warn_v) noexcept;

    private:
        HealthStatus m_status;
        float m_min_battery_v = 3.0f;
        float m_warn_battery_v = 3.3f;
    };
} // namespace ascent::safety