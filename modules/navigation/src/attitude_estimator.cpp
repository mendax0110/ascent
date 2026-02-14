#include "ascent/navigation/attitude_estimator.h"
#include <cmath>

using namespace ascent::navigation;
using namespace ascent::core;

AttitudeEstimator::AttitudeEstimator(const float alpha) noexcept
    : m_attitude(Quaternion::identity())
    , m_alpha(alpha)
{
}

void AttitudeEstimator::update(const Vec3f& gyro, const Vec3f& accel, float dt) noexcept
{
    (void)gyro;
    (void)accel;
    (void)dt;
    // Complementary filter implementation will be added
}

const Quaternion& AttitudeEstimator::getAttitude() const noexcept
{
    return m_attitude;
}

Vec3f AttitudeEstimator::getEulerDeg() const noexcept
{
    // Quaternion to Euler conversion will be added
    return {};
}

void AttitudeEstimator::reset() noexcept
{
    m_attitude = Quaternion::identity();
}


