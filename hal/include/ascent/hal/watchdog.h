#pragma once

#include "ascent/hal/types.h"

/// @brief Watchdog timer with RAII lifecycle. \namespace ascent::hal
namespace ascent::hal
{
    /**
     * \class Watchdog
     * @brief Watchdog timer with RAII lifecycle.
     *
     * Initializes the hardware watchdog on construction.
     * Must be fed periodically to prevent system reset.
     */
    class Watchdog
    {
    public:
        /**
         * @brief Initialize watchdog with timeout.
         * @param timeout_ms Watchdog timeout in milliseconds.
         */
        explicit Watchdog(uint32_t timeout_ms) noexcept;
        ~Watchdog() noexcept;

        Watchdog(const Watchdog&) = delete;
        Watchdog& operator=(const Watchdog&) = delete;
        Watchdog(Watchdog&&) = delete;
        Watchdog& operator=(Watchdog&&) = delete;

        /**
         * @brief Feed the watchdog to prevent reset.
         */
        void feed() noexcept;

        /**
         * @brief Get configured timeout.
         * @return Watchdog timeout in milliseconds.
         */
        [[nodiscard]] uint32_t getTimeoutMs() const noexcept;

    private:
        uint32_t m_timeout_ms;
        bool m_initialized = false;
    };
} // namespace ascent::hal