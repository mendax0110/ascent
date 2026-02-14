#pragma once

#include <cstdint>
#include "ascent/core/types.h"

/// @brief Sensor driver interface. \namespace ascent::hal
namespace ascent::hal
{
    /// @brief Sensor state enumeration. \enum class SensorState
    enum class SensorState : uint8_t
    {
        Uninitialized,
        Ready,
        Reading,
        Error,
        Calibrating
    };

    /**
     * \class ISensor
     * @brief Abstract sensor interface.
     *
     * All sensor drivers must implement this interface.
     */
    class ISensor
    {
    public:
        virtual ~ISensor() = default;

        /**
         * @brief Initialize the sensor hardware.
         * @return Ok on success.
         */
        virtual core::StatusCode init() noexcept = 0;

        /**
         * @brief Trigger a new reading.
         * @return Ok if reading started.
         */
        virtual core::StatusCode update() noexcept = 0;

        /**
         * @brief Check if new data is available.
         * @return true if new data is ready to be read.
         */
        [[nodiscard]] virtual bool isReady() const noexcept = 0;

        /**
         * @brief Get current sensor state.
         * @return SensorState
         */
        [[nodiscard]] virtual SensorState getState() const noexcept = 0;

        /**
         * @brief Get sensor name identifier.
         * @return pointer to null-terminated string.
         */
        [[nodiscard]] virtual const char* getName() const noexcept = 0;

    protected:
        ISensor() = default;
        ISensor(const ISensor&) = default;
        ISensor& operator=(const ISensor&) = default;
        ISensor(ISensor&&) = default;
        ISensor& operator=(ISensor&&) = default;
    };
} // namespace ascent::hal