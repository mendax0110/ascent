#include "ascent/drivers/actuators/actuator_base.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

ActuatorBase::ActuatorBase(const char* name) noexcept
    : m_name(name)
{
}

StatusCode ActuatorBase::init() noexcept
{
    const auto status = doInit();
    if (status == StatusCode::Ok)
    {
        m_state = ActuatorState::Ready;
    }
    else
    {
        m_state = ActuatorState::Error;
    }
    return status;
}

void ActuatorBase::safe() noexcept
{
    doSafe();
    m_state = ActuatorState::SafeState;
}

ActuatorState ActuatorBase::getState() const noexcept
{
    return m_state;
}

const char* ActuatorBase::getName() const noexcept
{
    return m_name;
}
