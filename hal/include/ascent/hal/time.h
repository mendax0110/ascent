#pragma once

#include <cstdint>

/// @brief Time utility class. Provides system tick, timestamps, and blocking delays. Platform-specific implementation required. \namespace ascent::hal
namespace ascent::hal
{
    /**
     * \class Time
     * @brief Static time utility class.
     *
     * Provides system tick, timestamps, and blocking delays.
     * Platform-specific implementation required.
     */
    class Time
    {
    public:
        Time() = delete;
        ~Time() = delete;

        /**
         * @brief Initialize system timer.
         */
        static void init() noexcept;

        /**
         * @brief Get milliseconds since boot.
         * @return Milliseconds since boot.
         */
        static uint32_t millis() noexcept;

        /**
         * @brief Get microseconds since boot.
         * @return Microseconds since boot.
         */
        static uint64_t micros() noexcept;

        /**
         * @brief Blocking delay in milliseconds.
         * @param ms Milliseconds to delay.
         */
        static void delayMs(uint32_t ms) noexcept;

        /**
         * @brief Blocking delay in microseconds.
         * @param us Microseconds to delay.
         */
        static void delayUs(uint32_t us) noexcept;

    private:
        static volatile uint32_t s_tick_ms;
    };
} // namespace ascent::hal