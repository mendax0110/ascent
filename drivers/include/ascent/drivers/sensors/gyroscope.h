#pragma once


#include "ascent/drivers/sensors/sensor_base.h"
#include "ascent/core/types.h"

/// @brief Gyroscope driver interface. \namespace ascent::drivers
namespace ascent::drivers
{
    /// @brief Gyroscope data structure. \struct ascent::drivers::GyroscopeData
    struct GyroscopeData
    {
        ascent::core::Vec3f angular_rate;  // Angular rate in rad/s
    };

    /**
     * \class Gyroscope
     * @brief Abstract gyroscope driver.
     */
    class Gyroscope : public SensorBase
    {
    public:
        explicit Gyroscope(const char* name) noexcept;
        ~Gyroscope() override = default;

        /**
         * @brief Get the Data object containing the latest gyroscope readings.
         * @return const GyroscopeData& 
         */
        const GyroscopeData& getData() const noexcept;

    protected:
        GyroscopeData m_data = {};
    };
} // namespace ascent::drivers