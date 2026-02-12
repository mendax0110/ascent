#pragma once

#include "actuator_interface.h"
#include "ascent/core/types.h"
#include <cstdint>

/// @brief Base class for actuator drivers. Provides common state management. Concrete actuators override doInit() and doSafe(). \namespace ascent::drivers
namespace ascent::drivers
{
    /**
     * \class ActuatorBase
     * @brief Base class for actuator drivers.
     *
     * Provides common state management. Concrete actuators
     * override doInit() and doSafe().
     */
    class ActuatorBase : public ascent::hal::IActuator
    {
    public:
        /**
         * @brief Construct actuator with name.
         * @param name Actuator identifier string.
         */
        explicit ActuatorBase(const char* name) noexcept;
        ~ActuatorBase() override = default;

        ActuatorBase(const ActuatorBase&) = delete;
        ActuatorBase& operator=(const ActuatorBase&) = delete;
        ActuatorBase(ActuatorBase&&) = default;
        ActuatorBase& operator=(ActuatorBase&&) = default;

        /**
         * @brief Initialize the actuator.
         * @return ascent::core::StatusCode 
         */
        ascent::core::StatusCode init() noexcept override;

        /**
         * @brief Put the actuator in a safe state.
         */
        void safe() noexcept override;
        
        /**
         * @brief Get the State object
         * @return ascent::hal::ActuatorState 
         */
        ascent::hal::ActuatorState getState() const noexcept override;
        
        /**
         * @brief Get the Name object
         * @return const char* 
         */
        const char* getName() const noexcept override;

    protected:
        /**
         * @brief Initialize the actuator.
         * @return ascent::core::StatusCode 
         */
        virtual ascent::core::StatusCode doInit() noexcept = 0;

        /**
         * @brief Put the actuator in a safe state.
         * 
         */
        virtual void doSafe() noexcept = 0;

        ascent::hal::ActuatorState m_state = ascent::hal::ActuatorState::Uninitialized;

    private:
        const char* m_name;
    };
} // namespace ascent::drivers