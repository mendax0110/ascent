#pragma once

#include "sensor_interface.h"
#include "ascent/core/types.h"
#include <cstdint>

/// @brief Base class for sensor drivers. Provides common state management, sample counting, and timing. Concrete sensors override doInit() and doUpdate(). \namespace ascent::drivers
namespace ascent::drivers
{
    /**
     * \class SensorBase
     * @brief Base class for sensor drivers.
     *
     * Provides common functionality: state tracking, sample counting,
     * and timing. Concrete sensors override doInit() and doUpdate().
     */
    class SensorBase : public ascent::hal::ISensor
    {
    public:
        /**
         * @brief Construct sensor with name.
         * @param name Sensor identifier string.
         * @param sample_period_ms Minimum sample period.
         */
        explicit SensorBase(const char* name, uint32_t sample_period_ms = 10) noexcept;
        ~SensorBase() override = default;

        SensorBase(const SensorBase&) = delete;
        SensorBase& operator=(const SensorBase&) = delete;
        SensorBase(SensorBase&&) = default;
        SensorBase& operator=(SensorBase&&) = default;

        /**
         * @brief Initialize the sensor.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode init() noexcept override;
        
        /**
         * @brief Read new data from the sensor if sample period has elapsed.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode update() noexcept override;
        
        /**
         * @brief Check if sensor is ready (initialized and sample period elapsed).
         * @return true if sensor is ready to update.
         */
        [[nodiscard]] bool isReady() const noexcept override;
        
        /**
         * @brief Get the State object
         * @return ascent::hal::SensorState 
         */
        [[nodiscard]] hal::SensorState getState() const noexcept override;
        
        /**
         * @brief Get the Name object
         * @return const char* 
         */
        [[nodiscard]] const char* getName() const noexcept override;

        /**
         * @brief Get total sample count since init.
         * @return Number of samples read.
         */
        [[nodiscard]] uint32_t getSampleCount() const noexcept;

    protected:
        /**
         * @brief Hardware-specific initialization. Override in concrete driver.
         */
        virtual core::StatusCode doInit() noexcept = 0;

        /**
         * @brief Hardware-specific read. Override in concrete driver.
         */
        virtual core::StatusCode doUpdate() noexcept = 0;

        hal::SensorState m_state = hal::SensorState::Uninitialized;
        uint32_t m_sample_count = 0;
        uint32_t m_last_sample_ms = 0;

    private:
        const char* m_name;
        uint32_t m_sample_period_ms;
    };
} // namespace ascent::drivers