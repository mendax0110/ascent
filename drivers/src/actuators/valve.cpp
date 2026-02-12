#include "ascent/drivers/actuators/valve.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

Valve::Valve(const char* name, std::unique_ptr<Gpio> gpio, bool active_high) noexcept
    : ActuatorBase(name)
    , m_gpio(std::move(gpio))
    , m_active_high(active_high)
{
}

void Valve::open() noexcept
{
    if (m_state != ActuatorState::Ready && m_state != ActuatorState::Active)
    {
        return;
    }

    if (m_gpio)
    {
        m_gpio->write(m_active_high);
    }
    m_is_open = true;
    m_state = ActuatorState::Active;
}

void Valve::close() noexcept
{
    if (m_gpio)
    {
        m_gpio->write(!m_active_high);
    }
    m_is_open = false;
    m_state = ActuatorState::Ready;
}

bool Valve::isOpen() const noexcept
{
    return m_is_open;
}

StatusCode Valve::doInit() noexcept
{
    if (m_gpio)
    {
        close();
        return StatusCode::Ok;
    }
    return StatusCode::HardwareFault;
}

void Valve::doSafe() noexcept
{
    close();
}
