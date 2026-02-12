#pragma once

#include "ascent/drivers/sensors/sensor_base.h"
#include "ascent/core/types.h"

/// @brief IMU driver interface. \namespace ascent::drivers
namespace ascent::drivers
{
    /// @brief IMU data structure. \struct ascent::drivers::ImuData
    struct ImuData
    {
        ascent::core::Vec3f accel;
        ascent::core::Vec3f gyro;
        float temperature = 0;
    };

    /**
     * \class Imu
     * @brief Abstract IMU driver.
     *
     * Concrete implementations: ImuBmi088, ImuMpu6050.
     */
    class Imu : public SensorBase
    {
    public:
        explicit Imu(const char* name) noexcept;
        ~Imu() override = default;

        /**
         * @brief Get latest IMU readings.
         * @return const ImuData&
         */
        const ImuData& getData() const noexcept;

    protected:
        ImuData m_data = {};
    };
} // namespace ascent::drivers