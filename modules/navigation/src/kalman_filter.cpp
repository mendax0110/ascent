#include "ascent/navigation/kalman_filter.h"

using namespace ascent::navigation;

KalmanFilter1D::KalmanFilter1D(float process_noise, float measurement_noise, float initial_estimate) noexcept
    : m_estimate(initial_estimate)
    , m_error_covariance(1.0f)
    , m_process_noise(process_noise)
    , m_measurement_noise(measurement_noise)
{
}

void KalmanFilter1D::predict(float dt) noexcept
{
    m_error_covariance += m_process_noise * dt;
}

void KalmanFilter1D::update(float measurement) noexcept
{
    const float gain = m_error_covariance / (m_error_covariance + m_measurement_noise);
    m_estimate += gain * (measurement - m_estimate);
    m_error_covariance *= (1.0f - gain);
}

float KalmanFilter1D::getEstimate() const noexcept
{
    return m_estimate;
}

void KalmanFilter1D::reset(float initial_estimate) noexcept
{
    m_estimate = initial_estimate;
    m_error_covariance = 1.0f;
}


