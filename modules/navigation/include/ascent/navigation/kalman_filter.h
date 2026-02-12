#pragma once

#include <cstdint>

/// @brief 1D Kalman filter. \namespace ascent::navigation
namespace ascent::navigation
{
    /**
     * \class KalmanFilter1D
     * @brief 1D Kalman filter.
     *
     * Lightweight scalar Kalman filter suitable for altitude,
     * velocity, or single-axis estimation.
     */
    class KalmanFilter1D
    {
    public:
        /**
         * @brief Construct filter with process/measurement noise.
         * @param process_noise Process noise covariance (Q).
         * @param measurement_noise Measurement noise covariance (R).
         * @param initial_estimate Initial state estimate.
         */
        KalmanFilter1D(float process_noise, float measurement_noise, float initial_estimate = 0.0f) noexcept;
        ~KalmanFilter1D() = default;

        KalmanFilter1D(const KalmanFilter1D&) = default;
        KalmanFilter1D& operator=(const KalmanFilter1D&) = default;
        KalmanFilter1D(KalmanFilter1D&&) = default;
        KalmanFilter1D& operator=(KalmanFilter1D&&) = default;

        /**
         * @brief Predict step.
         * @param dt Time step.
         */
        void predict(float dt) noexcept;

        /**
         * @brief Update step with measurement.
         * @param measurement Observed value.
         */
        void update(float measurement) noexcept;

        /**
         * @brief Get current state estimate.
         * @return Current state estimate.
         */
        float getEstimate() const noexcept;

        /**
         * @brief Reset filter state.
         */
        void reset(float initial_estimate = 0.0f) noexcept;

    private:
        float m_estimate;
        float m_error_covariance;
        float m_process_noise;
        float m_measurement_noise;
    };
} // namespace ascent::navigation