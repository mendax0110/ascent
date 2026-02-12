#include "ascent/drivers/sensors/barometer.h"
#include <cmath>

using namespace ascent::drivers;

Barometer::Barometer(const char* name) noexcept
    : SensorBase(name, 10)
{
}

const BarometerData& Barometer::getData() const noexcept
{
    return m_data;
}

void Barometer::setReferencePressure(float ref_pressure_pa) noexcept
{
    m_ref_pressure_pa = ref_pressure_pa;
}
