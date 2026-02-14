#pragma once

#include "ascent/drivers/actuators/actuator_base.h"
#include "ascent/hal/gpio.h"
#include <memory>

/// @brief GPIO-controlled solenoid valve driver. Controls a normally-closed solenoid valve via digital output. \namespace ascent::drivers
namespace ascent::drivers
{
    /**
     * \class Valve
     * @brief GPIO-controlled solenoid valve driver.
     *
     * Controls a normally-closed solenoid valve via digital output.
     */
    class Valve : public ActuatorBase
    {
    public:
        /**
         * @brief Construct valve driver.
         * @param name Valve identifier.
         * @param gpio GPIO pin controlling the valve (takes ownership).
         * @param active_high true if high = open.
         */
        Valve(const char* name, std::unique_ptr<hal::Gpio> gpio, bool active_high = true) noexcept;
        ~Valve() override = default;

        /**
         * @brief Open the valve.
         */
        void open() noexcept;

        /**
         * @brief Close the valve.
         */
        void close() noexcept;

        /**
         * @brief Check if valve is currently open.
         */
        [[nodiscard]] bool isOpen() const noexcept;

    protected:
        /**
         * @brief Initialize the valve hardware.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode doInit() noexcept override;
        
        /**
         * @brief Put the valve in a safe state (closed).
         */
        void doSafe() noexcept override;

    private:
        std::unique_ptr<hal::Gpio> m_gpio;
        bool m_active_high;
        bool m_is_open = false;
    };
} // namespace ascent::drivers