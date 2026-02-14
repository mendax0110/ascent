#pragma once

#include "gpio_interface.h"

/// @brief Mock GPIO pin for testing. \namespace ascent::sim
namespace ascent::sim
{
    /**
     * @class MockGpio
     * @brief Mock GPIO pin for testing.
     */
    class MockGpio : public hal::IGpio
    {
    public:
        MockGpio() noexcept = default;
        ~MockGpio() override = default;

        /**
         * @brief Set the pin high.
         */
        void setHigh() noexcept override;
        
        /**
         * @brief Set the pin low.
         */
        void setLow() noexcept override;
        
        /**
         * @brief Toggle the pin state (high to low, or low to high).
         */
        void toggle() noexcept override;
        
        /**
         * @brief Read the pin state (mocked). Returns the last state set by setHigh/setLow/toggle.
         * @return true If pin is high, false if low. Initial state is low (false).
         * @return false If pin is low.
         */
        [[nodiscard]] bool read() const noexcept override;

        /**
         * @brief Get current pin state.
         * @return true if pin is high, false if low.
         */
        [[nodiscard]] bool getState() const noexcept;

    private:
        bool m_state = false;
    };
} // namespace ascent::sim
