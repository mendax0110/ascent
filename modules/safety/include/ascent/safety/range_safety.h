#pragma once

#include "ascent/core/types.h"
#include <cstdint>

/// @brief Range safety monitor enforcing geofence constraints. \namespace ascent::safety
namespace ascent::safety
{
    /// @brief Geofence configuration parameters. \struct ascent::safety::GeofenceConfig
    struct GeofenceConfig
    {
        float max_altitude_m = 10000.0f;
        float max_range_m = 5000.0f;
        float max_speed_ms = 400.0f;
        float max_tilt_deg = 30.0f;
    };

    /**
     * \class RangeSafety
     * @brief Range safety monitor enforcing geofence constraints.
     */
    class RangeSafety
    {
    public:
        explicit RangeSafety(const GeofenceConfig& config = {}) noexcept;
        ~RangeSafety() = default;

        /**
         * @brief Check position against geofence.
         * @param position Position in NED frame [m].
         * @param velocity Velocity in NED frame [m/s].
         * @return true if within safe limits.
         */
        [[nodiscard]] bool checkLimits(const core::Vec3f& position, const core::Vec3f& velocity) const noexcept;

        /**
         * @brief Set geofence configuration.
         * @param config Geofence configuration parameters.
         */
        void setConfig(const GeofenceConfig& config) noexcept;

        /**
         * @brief Get current geofence configuration.
         * @return Current geofence configuration.
         */
        [[nodiscard]] const GeofenceConfig& getConfig() const noexcept;

    private:
        GeofenceConfig m_config;
    };
} // namespace ascent::safety