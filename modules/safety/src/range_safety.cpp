#include "ascent/safety/range_safety.h"
#include <cmath>

using namespace ascent::safety;
using namespace ascent::core;

RangeSafety::RangeSafety(const GeofenceConfig& config) noexcept
    : m_config(config)
{
}

bool RangeSafety::checkLimits(const Vec3f& position, const Vec3f& velocity) const noexcept
{
    const float altitude = -position.z;
    if (altitude > m_config.max_altitude_m)
    {
        return false;
    }

    const float range = std::sqrt(position.x * position.x + position.y * position.y);
    if (range > m_config.max_range_m)
    {
        return false;
    }

    const float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
    if (speed > m_config.max_speed_ms)
    {
        return false;
    }

    return true;
}

void RangeSafety::setConfig(const GeofenceConfig& config) noexcept
{
    m_config = config;
}

const GeofenceConfig& RangeSafety::getConfig() const noexcept
{
    return m_config;
}


