#include "ascent/navigation/altitude_estimator.h"

using namespace ascent::navigation;

AltitudeEstimator::AltitudeEstimator() noexcept
    : m_altitude_filter(0.1f, 1.0f, 0.0f)
{
}

void AltitudeEstimator::updateBarometer(float baro_alt_m, float dt) noexcept
{
    m_altitude_filter.predict(dt);
    m_altitude_filter.update(baro_alt_m);
}

void AltitudeEstimator::updateAccelerometer(float accel_z_ms2, float dt) noexcept
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

void AltitudeEstimator::setGroundLevel(float alt_m) noexcept
{
    m_ground_level = alt_m;
}


