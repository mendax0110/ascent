#pragma once

#include "ascent/navigation/kalman_filter.h"

/// @brief Altitude estimator using Kalman-filtered barometer data. \namespace ascent::navigation
namespace ascent::navigation
{
    /**
     * \class AltitudeEstimator
     * @brief Altitude estimator using Kalman-filtered barometer data.
     */
    class AltitudeEstimator
    {
    public:
        AltitudeEstimator() noexcept;
        ~AltitudeEstimator() = default;

        /**
         * @brief Update with barometric altitude.
         * @param baro_alt_m Barometric altitude [m].
         * @param dt Time step [s].
         */
        void updateBarometer(float baro_alt_m, float dt) noexcept;

        /**
         * @brief Update with vertical acceleration.
         * @param accel_z_ms2 Vertical acceleration [m/s^2].
         * @param dt Time step [s].
         */
        void updateAccelerometer(float accel_z_ms2, float dt) noexcept;

        /**
         * @brief Get estimated altitude [m].
         * @return Estimated altitude in meters.
         */
        [[nodiscard]] float getAltitude() const noexcept;

        /**
         * @brief Get estimated vertical velocity [m/s].
         * @return Estimated vertical velocity in m/s.
         */
        [[nodiscard]] float getVerticalVelocity() const noexcept;

        /**
         * @brief Set ground-level reference.
         * @param alt_m Altitude of ground level in meters.
         */
        void setGroundLevel(float alt_m) noexcept;

    private:
        KalmanFilter1D m_altitude_filter;
        float m_vertical_velocity = 0.0f;
        float m_ground_level = 0.0f;
    };
} // namespace ascent::navigation