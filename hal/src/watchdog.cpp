#include "ascent/hal/watchdog.h"

using namespace ascent::hal;

Watchdog::Watchdog(const uint32_t timeout_ms) noexcept
    : m_timeout_ms(timeout_ms)
    , m_initialized(false)
{
    // Platform-specific watchdog initialization
    m_initialized = true;
}

Watchdog::~Watchdog() noexcept
{
    // Watchdog typically cannot be disabled once started
}

void Watchdog::feed() noexcept
{
    // Platform-specific watchdog feed
}

uint32_t Watchdog::getTimeoutMs() const noexcept
{
    return m_timeout_ms;
}
