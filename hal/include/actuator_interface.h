#pragma once

#include <cstdint>
#include "ascent/core/types.h"

/// @brief Actuator driver interface. \namespace ascent::hal
namespace ascent::hal
{
    /// @brief Actuator state enumeration. \enum class ActuatorState
    enum class ActuatorState : uint8_t
    {
        Uninitialized,
        Ready,
        Active,
        Error,
        SafeState
    };

    /**
     * \class IActuator
     * @brief Abstract actuator interface.
     *
     * All actuator drivers must implement this interface.
     */
    class IActuator
    {
    public:
        virtual ~IActuator() = default;

        /**
         * @brief Initialize the actuator hardware.
         * @return Ok on success.
         */
        virtual core::StatusCode init() noexcept = 0;

        /**
         * @brief Command the actuator to a safe/default state.
         */
        virtual void safe() noexcept = 0;

        /**
         * @brief Get current actuator state.
         */
        [[nodiscard]] virtual ActuatorState getState() const noexcept = 0;

        /**
         * @brief Get actuator name identifier.
         */
        [[nodiscard]] virtual const char* getName() const noexcept = 0;

    protected:
        IActuator() = default;
        IActuator(const IActuator&) = default;
        IActuator& operator=(const IActuator&) = default;
        IActuator(IActuator&&) = default;
        IActuator& operator=(IActuator&&) = default;
    };
} // namespace ascent::hal