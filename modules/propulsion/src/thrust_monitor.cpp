#include "ascent/propulsion/thrust_monitor.h"

using namespace ascent::propulsion;

ThrustMonitor::ThrustMonitor() noexcept
{
}

void ThrustMonitor::update(const float accel_ms2, const float dt) noexcept
{
    if (accel_ms2 > m_burnout_threshold)
    {
        if (!m_burning)
        {
            m_burning = true;
        }
        m_burn_duration += dt;
        m_total_impulse += accel_ms2 * dt;
    }
    else if (m_burning)
    {
        m_burnout = true;
        m_burning = false;
    }
}

bool ThrustMonitor::isBurnoutDetected() const noexcept
{
    return m_burnout;
}

float ThrustMonitor::getTotalImpulse() const noexcept
{
    return m_total_impulse;
}

float ThrustMonitor::getBurnDuration() const noexcept
{
    return m_burn_duration;
}

void ThrustMonitor::setBurnoutThreshold(const float threshold_ms2) noexcept
{
    m_burnout_threshold = threshold_ms2;
}


