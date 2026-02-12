#include "ascent/drivers/sensors/gps.h"

using namespace ascent::drivers;

Gps::Gps(const char* name) noexcept
    : SensorBase(name, 100)
{
}

const GpsData& Gps::getData() const noexcept
{
    return m_data;
}

bool Gps::hasFix() const noexcept
{
    return m_data.fix_type != GpsFixType::NoFix;
}
