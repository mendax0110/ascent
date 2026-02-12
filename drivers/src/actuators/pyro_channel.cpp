#include "ascent/drivers/actuators/pyro_channel.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

PyroChannel::PyroChannel(const char* name,
                         std::unique_ptr<Gpio> fire_pin,
                         std::unique_ptr<Gpio> arm_pin,
                         std::unique_ptr<Gpio> continuity_pin) noexcept
    : ActuatorBase(name)
    , m_fire_pin(std::move(fire_pin))
    , m_arm_pin(std::move(arm_pin))
    , m_continuity_pin(std::move(continuity_pin))
{
}

StatusCode PyroChannel::arm() noexcept
{
    if (m_state != ActuatorState::Ready)
    {
        return StatusCode::InvalidParam;
    }
    if (m_fired)
    {
        return StatusCode::InvalidParam;
    }

    if (m_arm_pin)
    {
        m_arm_pin->setHigh();
    }
    m_armed = true;
    m_state = ActuatorState::Active;
    return StatusCode::Ok;
}

StatusCode PyroChannel::fire() noexcept
{
    if (!m_armed || m_fired)
    {
        return StatusCode::InvalidParam;
    }

    if (m_fire_pin)
    {
        m_fire_pin->setHigh();
    }
    m_fired = true;
    return StatusCode::Ok;
}

void PyroChannel::disarm() noexcept
{
    if (m_arm_pin)
    {
        m_arm_pin->setLow();
    }
    if (m_fire_pin)
    {
        m_fire_pin->setLow();
    }
    m_armed = false;
    m_state = ActuatorState::Ready;
}

bool PyroChannel::checkContinuity() const noexcept
{
    if (m_continuity_pin)
    {
        return m_continuity_pin->read();
    }
    return false;
}

bool PyroChannel::isArmed() const noexcept
{
    return m_armed;
}

bool PyroChannel::isFired() const noexcept
{
    return m_fired;
}

StatusCode PyroChannel::doInit() noexcept
{
    disarm();
    return StatusCode::Ok;
}

void PyroChannel::doSafe() noexcept
{
    disarm();
}
