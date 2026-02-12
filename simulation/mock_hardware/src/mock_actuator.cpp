#include "mock_actuator.h"

using namespace ascent::sim;
using namespace ascent::core;

MockActuator::MockActuator(const char* name) noexcept
    : ActuatorBase(name)
{
}

bool MockActuator::wasSafed() const noexcept
{
    return m_safe_count > 0;
}

uint32_t MockActuator::getSafeCount() const noexcept
{
    return m_safe_count;
}

StatusCode MockActuator::doInit() noexcept
{
    return StatusCode::Ok;
}

void MockActuator::doSafe() noexcept
{
    ++m_safe_count;
}
