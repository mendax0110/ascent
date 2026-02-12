#pragma once

#include "ascent/hal/types.h"

/// @brief PWM output channel with RAII lifecycle. \namespace ascent::hal
namespace ascent::hal
{
    /**
     * \class Pwm
     * @brief PWM output channel with RAII lifecycle.
     */
    class Pwm
    {
    public:
        /**
         * @brief Construct and initialize PWM channel.
         * @param channel PWM timer/channel identifier.
         * @param frequency_hz PWM frequency in Hz.
         */
        explicit Pwm(PwmChannel channel, uint32_t frequency_hz = 50) noexcept;
        ~Pwm() noexcept;

        Pwm(const Pwm&) = delete;
        Pwm& operator=(const Pwm&) = delete;
        Pwm(Pwm&& other) noexcept;
        Pwm& operator=(Pwm&& other) noexcept;

        /**
         * @brief Set duty cycle.
         * @param duty_percent Duty cycle 0.0 to 100.0.
         */
        void setDuty(float duty_percent) noexcept;

        /**
         * @brief Set pulse width in microseconds.
         * @param pulse_us Pulse width.
         */
        void setPulseWidth(uint32_t pulse_us) noexcept;

        /**
         * @brief Enable PWM output.
         */
        void enable() noexcept;

        /**
         * @brief Disable PWM output.
         */
        void disable() noexcept;

    private:
        PwmChannel m_channel;
        uint32_t m_frequency_hz;
        bool m_enabled = false;
    };
} // namespace ascent::hal