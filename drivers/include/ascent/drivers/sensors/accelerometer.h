#pragma once

#include "ascent/drivers/sensors/sensor_base.h"
#include "ascent/core/types.h"

/// @brief Accelerometer driver interface. \namespace ascent::drivers
namespace ascent::drivers
{
    /// @brief Accelerometer data structure. \struct ascent::drivers::AccelerometerData
    struct AccelerometerData
    {
        ascent::core::Vec3f accel;  // acc in m/s^2
    };

    /**
     * \class Accelerometer
     * @brief Abstract accelerometer driver.
     */
    class Accelerometer : public SensorBase
    {
    public:
        explicit Accelerometer(const char* name) noexcept;
        ~Accelerometer() override = default;

        /**
         * @brief Get the latest accelerometer data.
         * @return const AccelerometerData& 
         */
        const AccelerometerData& getData() const noexcept;

    protected:
        AccelerometerData m_data = {};
    };
} // namespace ascent::drivers