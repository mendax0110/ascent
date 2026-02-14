#include "ascent/navigation/altitude_estimator.h"

using namespace ascent::navigation;

AltitudeEstimator::AltitudeEstimator() noexcept
    : m_altitude_filter(0.1f, 1.0f, 0.0f)
{
}

void AltitudeEstimator::updateBarometer(const float baro_alt_m, const float dt) noexcept
{
    m_altitude_filter.predict(dt);
    m_altitude_filter.update(baro_alt_m);
}

void AltitudeEstimator::updateAccelerometer(const float accel_z_ms2, const float dt) noexcept
{
    m_vertical_velocity += accel_z_ms2 * dt;
}

float AltitudeEstimator::getAltitude() const noexcept
{
    return m_altitude_filter.getEstimate() - m_ground_level;
}

float AltitudeEstimator::getVerticalVelocity() const noexcept
{
    return m_vertical_velocity;
}

void AltitudeEstimator::setGroundLevel(const float alt_m) noexcept
{
    m_ground_level = alt_m;
}


