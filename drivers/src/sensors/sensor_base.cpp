#include "ascent/drivers/sensors/sensor_base.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

SensorBase::SensorBase(const char* name, uint32_t sample_period_ms) noexcept
    : m_name(name)
    , m_sample_period_ms(sample_period_ms)
{
}

StatusCode SensorBase::init() noexcept
{
    auto status = doInit();
    if (status == StatusCode::Ok)
    {
        m_state = SensorState::Ready;
        m_sample_count = 0;
    }
    else
    {
        m_state = SensorState::Error;
    }
    return status;
}

StatusCode SensorBase::update() noexcept
{
    if (m_state == SensorState::Uninitialized)
    {
        return StatusCode::NotInitialized;
    }

    m_state = SensorState::Reading;
    auto status = doUpdate();

    if (status == StatusCode::Ok)
    {
        ++m_sample_count;
        m_state = SensorState::Ready;
    }
    else
    {
        m_state = SensorState::Error;
    }

    return status;
}

bool SensorBase::isReady() const noexcept
{
    return m_state == SensorState::Ready;
}

SensorState SensorBase::getState() const noexcept
{
    return m_state;
}

const char* SensorBase::getName() const noexcept
{
    return m_name;
}

uint32_t SensorBase::getSampleCount() const noexcept
{
    return m_sample_count;
}
