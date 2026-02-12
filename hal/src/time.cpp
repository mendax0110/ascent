#include "ascent/hal/time.h"

using namespace ascent::hal;

volatile uint32_t Time::s_tick_ms = 0;

void Time::init() noexcept
{
    s_tick_ms = 0;
    // Platform-specific timer initialization
}

uint32_t Time::millis() noexcept
{
    return s_tick_ms;
}

uint64_t Time::micros() noexcept
{
    // Platform-specific microsecond counter
    return static_cast<uint64_t>(s_tick_ms) * 1000ULL;
}

void Time::delayMs(uint32_t ms) noexcept
{
    const uint32_t start = millis();
    while ((millis() - start) < ms)
    {
        // Busy wait - platform may override with sleep
    }
}

void Time::delayUs(uint32_t us) noexcept
{
    // Platform-specific microsecond delay
    (void)us;
}
