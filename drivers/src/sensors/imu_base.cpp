#include "ascent/drivers/sensors/imu.h"

using namespace ascent::drivers;

Imu::Imu(const char* name) noexcept
    : SensorBase(name, 1)
{
}

const ImuData& Imu::getData() const noexcept
{
    return m_data;
}
