#pragma once

#include "ascent/core/types.h"
#include <cstdint>

/// @brief Propulsion system controller. Coordinates ignition, valve control, and thrust monitoring. \namespace ascent::propulsion
namespace ascent::propulsion
{
    /**
     * \class ThrustMonitor
     * @brief Monitors thrust via acceleration data.
     */
    class ThrustMonitor
    {
    public:
        ThrustMonitor() noexcept;
        ~ThrustMonitor() = default;

        /**
         * @brief Update with current acceleration.
         * @param accel_ms2 Longitudinal acceleration [m/s^2].
         * @param dt Time step [s].
         */
        void update(float accel_ms2, float dt) noexcept;

        /**
         * @brief Check if burnout is detected.
         * @return true if burnout is detected.
         */
        bool isBurnoutDetected() const noexcept;

        /**
         * @brief Get estimated total impulse [N*s].
         * @return Total impulse.
         */
        float getTotalImpulse() const noexcept;

        /**
         * @brief Get burn duration [s].
         * @return Burn duration.
         */
        float getBurnDuration() const noexcept;

        /**
         * @brief Set burnout detection threshold.
         * @param threshold_ms2 Acceleration below this = burnout.
         */
        void setBurnoutThreshold(float threshold_ms2) noexcept;

    private:
        float m_total_impulse = 0.0f;
        float m_burn_duration = 0.0f;
        float m_burnout_threshold = 2.0f;
        bool m_burnout = false;
        bool m_burning = false;
    };
} // namespace ascent::propulsion