#pragma once

#include "ascent/drivers/actuators/actuator_base.h"
#include "ascent/hal/pwm.h"
#include <memory>

/// @brief PWM-based servo driver. Controls a standard RC servo via PWM pulse width. Typical range: 1000us (min) to 2000us (max). \namespace ascent::drivers
namespace ascent::drivers
{
    /**
     * \class Servo
     * @brief PWM-based servo driver.
     *
     * Controls a standard RC servo via PWM pulse width.
     * Typical range: 1000us (min) to 2000us (max).
     */
    class Servo : public ActuatorBase
    {
    public:
        /**
         * @brief Construct servo driver.
         * @param name Servo identifier.
         * @param pwm PWM channel (takes ownership).
         * @param min_pulse_us Minimum pulse width in microseconds.
         * @param max_pulse_us Maximum pulse width in microseconds.
         */
        Servo(const char* name, std::unique_ptr<hal::Pwm> pwm, uint32_t min_pulse_us = 1000, uint32_t max_pulse_us = 2000) noexcept;
        ~Servo() override = default;

        /**
         * @brief Set servo position.
         * @param angle_deg Angle in degrees (0 to 180).
         */
        void setAngle(float angle_deg) noexcept;

        /**
         * @brief Get current commanded angle.
         */
        [[nodiscard]] float getAngle() const noexcept;

    protected:

        /**
         * @brief Initialize the servo hardware.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode doInit() noexcept override;
        
        /**
         * @brief Put the servo in a safe state (e.g. 0 degrees).
         */
        void doSafe() noexcept override;

    private:
        std::unique_ptr<hal::Pwm> m_pwm;
        uint32_t m_min_pulse_us;
        uint32_t m_max_pulse_us;
        float m_current_angle = 0.0f;
    };
} // namespace ascent::drivers