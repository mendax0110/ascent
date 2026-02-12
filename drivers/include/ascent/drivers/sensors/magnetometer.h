#pragma once


#include "ascent/drivers/sensors/sensor_base.h"
#include "ascent/core/types.h"

/// @brief Magnetometer driver interface. \namespace ascent::drivers
namespace ascent::drivers
{
    /// @brief Magnetometer data structure. \struct ascent::drivers::MagnetometerData
    struct MagnetometerData
    {
        ascent::core::Vec3f field;
    };

    /**
     * \class Magnetometer
     * @brief Abstract magnetometer driver.
     *
     * Concrete implementation: MagnetometerLis3mdl.
     */
    class Magnetometer : public SensorBase
    {
    public:
        explicit Magnetometer(const char* name) noexcept;
        ~Magnetometer() override = default;

        /**
         * @brief Get latest magnetometer readings.
         * @return const MagnetometerData&
         */
        const MagnetometerData& getData() const noexcept;

    protected:
        MagnetometerData m_data = {};
    };
} // namespace ascent::drivers