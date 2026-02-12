#pragma once

#include "ascent/core/types.h"

/// @brief Attitude estimator using complementary filter. Fuses gyroscope and accelerometer data to estimate orientation. \namespace ascent::navigation
namespace ascent::navigation
{
    /**
     * \class AttitudeEstimator
     * @brief Complementary filter for attitude estimation.
     *
     * Fuses gyroscope and accelerometer data to estimate orientation.
     */
    class AttitudeEstimator
    {
    public:
        /**
         * @brief Construct estimator with filter coefficient.
         * @param alpha Complementary filter coefficient [0..1].
         *              Higher = more gyro trust.
         */
        explicit AttitudeEstimator(float alpha = 0.98f) noexcept;
        ~AttitudeEstimator() = default;

        /**
         * @brief Update attitude estimate.
         * @param gyro Angular rates [rad/s].
         * @param accel Acceleration [m/s^2].
         * @param dt Time step [s].
         */
        void update(const core::Vec3f& gyro, const core::Vec3f& accel, float dt) noexcept;

        /**
         * @brief Get estimated attitude quaternion.
         * @return Estimated attitude as a quaternion.
         */
        const core::Quaternion& getAttitude() const noexcept;

        /**
         * @brief Get Euler angles (roll, pitch, yaw) in degrees.
         * @return Euler angles in degrees.
         */
        core::Vec3f getEulerDeg() const noexcept;

        /**
         * @brief Reset to identity orientation.
         */
        void reset() noexcept;

    private:
        core::Quaternion m_attitude;
        float m_alpha;
    };
} // namespace ascent::navigation