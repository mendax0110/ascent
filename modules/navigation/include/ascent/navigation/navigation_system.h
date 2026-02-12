#pragma once

#include "ascent/core/types.h"
#include "ascent/drivers/sensors/imu.h"
#include "ascent/drivers/sensors/barometer.h"
#include "ascent/drivers/sensors/gps.h"
#include "ascent/drivers/sensors/magnetometer.h"

/// @brief Navigation system for rocket flight. Fuses IMU, barometer, GPS, and magnetometer data into a coherent navigation solution. \namespace ascent::navigation
namespace ascent::navigation
{
    /// @brief Navigation state structure. \struct ascent::navigation::NavigationState
    struct NavigationState
    {
        core::Vec3f position;       // Position in NED frame [m]
        core::Vec3f velocity;       // Velocity in NED frame [m/s]
        core::Quaternion attitude;  // Attitude quaternion
        core::Vec3f euler_deg;      // Euler angles (roll, pitch, yaw) [deg]
        float altitude_agl_m = 0;   // Altitude above ground level [m]
        float altitude_msl_m = 0;   // Altitude above mean sea level [m]
        float vertical_speed_ms = 0;// Vertical speed [m/s]
        uint32_t timestamp_ms = 0;
        bool valid = false;
    };

    /**
     * \class NavigationSystem
     * @brief Main navigation system.
     *
     * Fuses IMU, barometer, GPS, and magnetometer data into a
     * coherent navigation solution.
     */
    class NavigationSystem
    {
    public:
        NavigationSystem() noexcept;
        ~NavigationSystem() = default;

        NavigationSystem(const NavigationSystem&) = delete;
        NavigationSystem& operator=(const NavigationSystem&) = delete;
        NavigationSystem(NavigationSystem&&) = default;
        NavigationSystem& operator=(NavigationSystem&&) = default;

        /**
         * @brief Initialize the navigation system.
         * @return ascent::core::StatusCode
         */
        core::StatusCode init() noexcept;

        /**
         * @brief Run one navigation update cycle.
         * @param dt_s Time step in seconds.
         */
        void update(float dt_s) noexcept;

        /**
         * @brief Get current navigation state.
         * @return Current navigation state.
         */
        const NavigationState& getState() const noexcept;

        /**
         * @brief Feed IMU measurement.
         * @param data Raw IMU data. 
         */
        void feedImu(const drivers::ImuData& data) noexcept;

        /**
         * @brief Feed barometer measurement.
         * @param data Barometer data.
         */
        void feedBarometer(const drivers::BarometerData& data) noexcept;

        /**
         * @brief Feed GPS measurement.
         * @param data GPS data.
         */
        void feedGps(const drivers::GpsData& data) noexcept;

        /**
         * @brief Feed magnetometer measurement.
         * @param data Magnetometer data.
         */
        void feedMagnetometer(const drivers::MagnetometerData& data) noexcept;

    private:
        NavigationState m_state;
        bool m_initialized = false;
    };
} // namespace ascent::navigation