#pragma once

#include "ascent/drivers/actuators/actuator_base.h"
#include "ascent/hal/gpio.h"
#include <memory>

/// @brief Pyrotechnic firing channel. Controls a pyrotechnic device (e-match, squib) with safety arming. Requires explicit arm before fire. Single-use. \namespace ascent::drivers
namespace ascent::drivers
{
    /**
    * \class PyroChannel
    * @brief Pyrotechnic firing channel.
    *
    * Controls a pyrotechnic device (e-match, squib) with safety arming.
    * Requires explicit arm before fire. Single-use.
    */
    class PyroChannel : public ActuatorBase
    {
    public:
        /**
         * @brief Construct pyro channel.
         * @param name Channel identifier.
         * @param fire_pin GPIO for firing (takes ownership).
         * @param arm_pin GPIO for arming (takes ownership).
         * @param continuity_pin GPIO for continuity check (takes ownership).
         */
        PyroChannel(const char* name,
                    std::unique_ptr<hal::Gpio> fire_pin,
                    std::unique_ptr<hal::Gpio> arm_pin,
                    std::unique_ptr<hal::Gpio> continuity_pin) noexcept;
        ~PyroChannel() override = default;

        /**
         * @brief Arm the pyro channel, allowing it to be fired. Checks continuity before arming.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode arm() noexcept;

        /**
         * @brief Fire the pyrotechnic device. Channel must be armed and not previously fired.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode fire() noexcept;

        /**
         * @brief Disarm the pyro channel.
         */
        void disarm() noexcept;

        /**
         * @brief Check continuity of the pyrotechnic device.
         * @return true if continuity is detected.
         */
        [[nodiscard]] bool checkContinuity() const noexcept;

        /**
         * @brief Check if the channel is currently armed.
         * @return true If the channel is armed.
         * @return false If the channel is not armed.
         */
        [[nodiscard]] bool isArmed() const noexcept;
        
        /**
         * @brief Check if the channel has been fired.
         * @return true If the channel has been fired.
         * @return false If the channel has not been fired.
         */
        [[nodiscard]] bool isFired() const noexcept;

    protected:

        /**
         * @brief Initialize the pyro channel hardware.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode doInit() noexcept override;
        
        /**
         * @brief Put the pyro channel in a safe state (disarmed).
         */
        void doSafe() noexcept override;

    private:
        std::unique_ptr<hal::Gpio> m_fire_pin;
        std::unique_ptr<hal::Gpio> m_arm_pin;
        std::unique_ptr<hal::Gpio> m_continuity_pin;
        bool m_armed = false;
        bool m_fired = false;
    };
} // namespace ascent::drivers