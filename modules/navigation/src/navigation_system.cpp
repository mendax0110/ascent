#include "ascent/navigation/navigation_system.h"

using namespace ascent::navigation;
using namespace ascent::core;
using namespace ascent::drivers;

NavigationSystem::NavigationSystem() noexcept
{
}

StatusCode NavigationSystem::init() noexcept
{
    m_state = {};
    m_initialized = true;
    return StatusCode::Ok;
}

void NavigationSystem::update(float dt_s) noexcept
{
    if (!m_initialized)
    {
        return;
    }
    (void)dt_s;
    // Full fusion implementation will be added
}

const NavigationState& NavigationSystem::getState() const noexcept
{
    return m_state;
}

void NavigationSystem::feedImu(const ImuData& data) noexcept
{
    (void)data;
}

void NavigationSystem::feedBarometer(const BarometerData& data) noexcept
{
    (void)data;
}

void NavigationSystem::feedGps(const GpsData& data) noexcept
{
    (void)data;
}

void NavigationSystem::feedMagnetometer(const MagnetometerData& data) noexcept
{
    (void)data;
}


