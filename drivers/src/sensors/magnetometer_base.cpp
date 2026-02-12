#include "ascent/drivers/sensors/magnetometer.h"

using namespace ascent::drivers;

Magnetometer::Magnetometer(const char* name) noexcept
    : SensorBase(name, 10)
{
}

const MagnetometerData& Magnetometer::getData() const noexcept
{
    return m_data;
}
