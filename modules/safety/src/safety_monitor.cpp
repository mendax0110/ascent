#include "ascent/safety/safety_monitor.h"

using namespace ascent::safety;
using namespace ascent::core;

SafetyMonitor::SafetyMonitor() noexcept
{
}

StatusCode SafetyMonitor::init() noexcept
{
    m_alert_level = AlertLevel::None;
    m_abort_required = false;
    return StatusCode::Ok;
}

void SafetyMonitor::update() noexcept
{
    // Aggregate health, range safety, and abort checks
}

AlertLevel SafetyMonitor::getAlertLevel() const noexcept
{
    return m_alert_level;
}

bool SafetyMonitor::isAbortRequired() const noexcept
{
    return m_abort_required;
}


