#include "mock_sensor.h"

using namespace ascent::sim;
using namespace ascent::core;

MockSensor::MockSensor(const char* name) noexcept
    : SensorBase(name, 10)
{
}

void MockSensor::setMockValue(float value) noexcept
{
    m_mock_value = value;
}

void MockSensor::setInitSuccess(bool success) noexcept
{
    m_init_success = success;
}

StatusCode MockSensor::doInit() noexcept
{
    return m_init_success ? StatusCode::Ok : StatusCode::HardwareFault;
}

StatusCode MockSensor::doUpdate() noexcept
{
    return StatusCode::Ok;
}
