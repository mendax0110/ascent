#pragma once

#include "ascent/hal/types.h"

/// @brief GPIO pin abstraction. \namespace ascent::hal
namespace ascent::hal
{
    /**
     * \class Gpio
     * @brief GPIO pin abstraction.
     *
     * RAII wrapper around a single GPIO pin. Configures the pin on
     * construction, resets on destruction.
     */
    class Gpio
    {
    public:
        /**
         * @brief Construct and configure a GPIO pin.
         * @param id Pin identifier (port + pin number).
         * @param direction Pin direction.
         * @param pull Pull-up/pull-down configuration.
         */
        explicit Gpio(PinId id, PinDirection direction = PinDirection::Input, PullMode pull = PullMode::None) noexcept;
        ~Gpio() noexcept;

        Gpio(const Gpio&) = delete;
        Gpio& operator=(const Gpio&) = delete;
        Gpio(Gpio&& other) noexcept;
        Gpio& operator=(Gpio&& other) noexcept;

        /**
         * @brief Set the pin high.
         */
        void setHigh() noexcept;

        /**
         * @brief Set the pin low.
         */
        void setLow() noexcept;

        /**
         * @brief Toggle pin state.
         */
        void toggle() noexcept;

        /**
         * @brief Read pin state.
         * @return true if pin is high.
         */
        [[nodiscard]] bool read() const noexcept;

        /**
         * @brief Write a value to the pin.
         * @param high true for high, false for low.
         */
        void write(bool high) noexcept;

        /**
         * @brief Get the pin identifier.
         */
        [[nodiscard]] PinId getId() const noexcept;

    private:
        PinId m_id;
        PinDirection m_direction;
        bool m_initialized = false;
    };
} // namespace ascent::hal