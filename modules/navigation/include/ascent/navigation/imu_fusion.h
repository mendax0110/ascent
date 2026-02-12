#pragma once

#include "ascent/core/types.h"
#include "ascent/drivers/sensors/imu.h"

/// @brief IMU fusion for navigation. Applies calibration and filtering to raw IMU data. \namespace ascent::navigation
namespace ascent::navigation
{
    /// @brief IMU calibration parameters. \struct ascent::navigation::ImuCalibration
    struct ImuCalibration
    {
        core::Vec3f accel_bias;   // Accelerometer bias [m/s^2]
        core::Vec3f gyro_bias;    // Gyroscope bias [rad/s]
        core::Vec3f accel_scale;  // Accelerometer scale factor
        core::Vec3f gyro_scale;   // Gyroscope scale factor
    };

    /**
     * \class ImuFusion
     * @brief Applies calibration and filtering to raw IMU data.
     */
    class ImuFusion
    {
    public:
        ImuFusion() noexcept;
        ~ImuFusion() = default;

        /**
         * @brief Apply calibration to raw IMU data.
         * @param raw Raw IMU data.
         * @return Calibrated IMU data.
         */
        drivers::ImuData apply(const drivers::ImuData& raw) const noexcept;

        /**
         * @brief Set calibration parameters.
         * @param cal Calibration parameters.
         */
        void setCalibration(const ImuCalibration& cal) noexcept;

        /**
         * @brief Get current calibration.
         * @return Current calibration parameters.
         */
        const ImuCalibration& getCalibration() const noexcept;

    private:
        ImuCalibration m_calibration;
    };
} // namespace ascent::navigation