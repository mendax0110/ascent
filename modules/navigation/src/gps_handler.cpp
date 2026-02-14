#include "ascent/navigation/gps_handler.h"
#include <cmath>

using namespace ascent::navigation;
using namespace ascent::core;
using namespace ascent::drivers;

GpsHandler::GpsHandler() noexcept
{
}

void GpsHandler::setOrigin(const double lat_deg, const double lon_deg, const float alt_m) noexcept
{
    m_origin_lat = lat_deg;
    m_origin_lon = lon_deg;
    m_origin_alt = alt_m;
    m_origin_set = true;
}

Vec3f GpsHandler::toLocalNed(const GpsData& gps) const noexcept
{
    if (!m_origin_set)
    {
        return {};
    }

    static constexpr double kEarthRadius = 6371000.0;
    static constexpr double kDegToRad = 3.14159265358979323846 / 180.0;

    const double dlat = (gps.latitude_deg - m_origin_lat) * kDegToRad;
    const double dlon = (gps.longitude_deg - m_origin_lon) * kDegToRad;

    Vec3f ned;
    ned.x = static_cast<float>(dlat * kEarthRadius);
    ned.y = static_cast<float>(dlon * kEarthRadius * std::cos(m_origin_lat * kDegToRad));
    ned.z = -(gps.altitude_m - m_origin_alt);

    return ned;
}

bool GpsHandler::hasOrigin() const noexcept
{
    return m_origin_set;
}


