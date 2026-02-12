#include "ascent/safety/health_monitor.h"

using namespace ascent::safety;

HealthMonitor::HealthMonitor() noexcept
{
}

void HealthMonitor::update() noexcept
{
    m_status.all_ok = (m_status.battery_voltage >= m_min_battery_v);
}

const HealthStatus& HealthMonitor::getStatus() const noexcept
{
    return m_status;
}

void HealthMonitor::setBatteryLimits(float min_v, float warn_v) noexcept
{
    m_min_battery_v = min_v;
    m_warn_battery_v = warn_v;
}


