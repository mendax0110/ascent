#pragma once

#include "ascent/drivers/sensors/sensor_base.h"

/// @brief Barometer driver interface. \namespace ascent::drivers
namespace ascent::drivers
{
    /// @brief Barometer data structure. \struct ascent::drivers::BarometerData
    struct BarometerData
    {
        float pressure_pa = 0;
        float temperature_c = 0;
        float altitude_m = 0;
    };

    /**
     * \class Barometer
     * @brief Abstract barometer driver.
     *
     * Concrete implementations: BarometerBmp388, BarometerMs5611.
     */
    class Barometer : public SensorBase
    {
    public:
        explicit Barometer(const char* name) noexcept;
        ~Barometer() override = default;

        /**
         * @brief Get latest barometer readings.
         * @return const BarometerData& 
         */
        [[nodiscard]] const BarometerData& getData() const noexcept;

        /**
         * @brief Set reference pressure for altitude calculation.
         * @param ref_pressure_pa Sea-level pressure in Pascals.
         */
        void setReferencePressure(float ref_pressure_pa) noexcept;

    protected:
        BarometerData m_data = {};
        float m_ref_pressure_pa = 101325.0f;
    };
} // namespace ascent::drivers