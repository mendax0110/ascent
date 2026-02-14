#include "ascent/hal/gpio.h"

using namespace ascent::hal;

Gpio::Gpio(const PinId id, const PinDirection direction, PullMode pull) noexcept
    : m_id(id)
    , m_direction(direction)
    , m_initialized(false)
{
    // Platform-specific GPIO initialization
    m_initialized = true;
}

Gpio::~Gpio() noexcept
{
    if (m_initialized)
    {
        // Platform-specific GPIO deinitialization
        m_initialized = false;
    }
}

Gpio::Gpio(Gpio&& other) noexcept
    : m_id(other.m_id)
    , m_direction(other.m_direction)
    , m_initialized(other.m_initialized)
{
    other.m_initialized = false;
}

Gpio& Gpio::operator=(Gpio&& other) noexcept
{
    if (this != &other)
    {
        if (m_initialized)
        {
            // Release current pin
        }
        m_id = other.m_id;
        m_direction = other.m_direction;
        m_initialized = other.m_initialized;
        other.m_initialized = false;
    }
    return *this;
}

void Gpio::setHigh() noexcept
{
    // Platform-specific implementation
}

void Gpio::setLow() noexcept
{
    // Platform-specific implementation
}

void Gpio::toggle() noexcept
{
    // Platform-specific implementation
}

bool Gpio::read() const noexcept
{
    // Platform-specific implementation
    return false;
}

void Gpio::write(bool high) noexcept
{
    if (high)
    {
        setHigh();
    }
    else
    {
        setLow();
    }
}

PinId Gpio::getId() const noexcept
{
    return m_id;
}
