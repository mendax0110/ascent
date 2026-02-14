#include "ascent/hal/pwm.h"

using namespace ascent::hal;

Pwm::Pwm(const PwmChannel channel, const uint32_t frequency_hz) noexcept
    : m_channel(channel)
    , m_frequency_hz(frequency_hz)
    , m_enabled(false)
{
    // Platform-specific PWM initialization
}

Pwm::~Pwm() noexcept
{
    if (m_enabled)
    {
        disable();
    }
}

Pwm::Pwm(Pwm&& other) noexcept
    : m_channel(other.m_channel)
    , m_frequency_hz(other.m_frequency_hz)
    , m_enabled(other.m_enabled)
{
    other.m_enabled = false;
}

Pwm& Pwm::operator=(Pwm&& other) noexcept
{
    if (this != &other)
    {
        if (m_enabled)
        {
            disable();
        }
        m_channel = other.m_channel;
        m_frequency_hz = other.m_frequency_hz;
        m_enabled = other.m_enabled;
        other.m_enabled = false;
    }
    return *this;
}

void Pwm::setDuty(float duty_percent) noexcept
{
    // Platform-specific implementation
    (void)duty_percent;
}

void Pwm::setPulseWidth(uint32_t pulse_us) noexcept
{
    // Platform-specific implementation
    (void)pulse_us;
}

void Pwm::enable() noexcept
{
    // Platform-specific implementation
    m_enabled = true;
}

void Pwm::disable() noexcept
{
    // Platform-specific implementation
    m_enabled = false;
}
