#pragma once

#include "ascent/drivers/sensors/sensor_base.h"

/// @brief Temperature sensor driver interface. \namespace ascent::drivers
namespace ascent::drivers
{
    /// @brief Temperature data structure. \struct ascent::drivers::TemperatureData
    struct TemperatureData
    {
        float temperature_c = 0;
    };

    /**
     * \class Temperature
     * @brief Abstract temperature sensor driver.
     */
    class Temperature : public SensorBase
    {
    public:
        explicit Temperature(const char* name) noexcept;
        ~Temperature() override = default;

        /**
         * @brief Get latest temperature reading.
         * @return const TemperatureData& 
         */
        const TemperatureData& getData() const noexcept;

    protected:
        TemperatureData m_data = {};
    };
} // namespace ascent::drivers