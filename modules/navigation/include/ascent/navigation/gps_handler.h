#pragma once

#include "ascent/core/types.h"
#include "ascent/drivers/sensors/gps.h"

/// @brief GPS handler for navigation. Processes GPS data and converts to local NED frame. \namespace ascent::navigation
namespace ascent::navigation
{
    /**
     * \class GpsHandler
     * @brief Processes GPS data and converts to local NED frame.
     */
    class GpsHandler
    {
    public:
        GpsHandler() noexcept;
        ~GpsHandler() = default;

        /**
         * @brief Set the launch site as local reference origin.
         * @param lat_deg Latitude [deg].
         * @param lon_deg Longitude [deg].
         * @param alt_m Altitude MSL [m].
         */
        void setOrigin(double lat_deg, double lon_deg, float alt_m) noexcept;

        /**
         * @brief Convert GPS coordinates to local NED position.
         * @param gps GPS data.
         * @return Position in NED frame [m].
         */
        [[nodiscard]] core::Vec3f toLocalNed(const drivers::GpsData& gps) const noexcept;

        /**
         * @brief Check if origin is set.
         * @return true if origin is set.
         */
        [[nodiscard]] bool hasOrigin() const noexcept;

    private:
        double m_origin_lat = 0;
        double m_origin_lon = 0;
        float m_origin_alt = 0;
        bool m_origin_set = false;
    };
} // namespace ascent::navigation