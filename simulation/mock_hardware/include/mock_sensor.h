#pragma once

#include "ascent/drivers/sensors/sensor_base.h"
#include "ascent/core/types.h"

/// @brief Mock sensor that returns configurable data. \namespace ascent::sim
namespace ascent::sim
{
    /**
     * @class MockSensor
     * @brief Mock sensor that returns configurable data.
     *
     * Used for desktop simulation and unit testing.
     */
    class MockSensor : public drivers::SensorBase
    {
    public:
        explicit MockSensor(const char* name = "MOCK_SENSOR") noexcept;
        ~MockSensor() override = default;

        /**
         * @brief Set the value to return on next update.
         * @param value Value to return on next update.
         */
        void setMockValue(float value) noexcept;

        /**
         * @brief Set whether init should succeed.
         * @param success If true, init() will return StatusCode::Ok. If false, init() will return StatusCode::Error.
         */
        void setInitSuccess(bool success) noexcept;

    protected:
        
        /**
         * @brief Initialize the mock sensor. Returns StatusCode::Ok or StatusCode::Error based on m_init_success.
         * @return ascent::core::StatusCode 
         */
        ascent::core::StatusCode doInit() noexcept override;

        /**
         * @brief Update the mock sensor. Sets m_data based on m_mock_value.
         * @return ascent::core::StatusCode 
         */
        ascent::core::StatusCode doUpdate() noexcept override;

    private:
        float m_mock_value = 0.0f;
        bool m_init_success = true;
    };
} // namespace ascent::sim
