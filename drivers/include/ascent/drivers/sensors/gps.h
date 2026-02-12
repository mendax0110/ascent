#pragma once

#include "ascent/drivers/sensors/sensor_base.h"

/// @brief GPS driver interface. \namespace ascent::drivers
namespace ascent::drivers
{
    /// @brief GPS fix type enumeration. \enum ascent::drivers::GpsFixType
    enum class GpsFixType : uint8_t
    {
        NoFix = 0,
        Fix2D,
        Fix3D,
        DGps,
        RTK
    };

    /// @brief GPS data structure. \struct ascent::drivers::GpsData
    struct GpsData
    {
        double latitude_deg = 0;
        double longitude_deg = 0;
        float altitude_m = 0;
        float speed_ms = 0;
        float heading_deg = 0;
        float hdop = 99.9f;
        uint8_t num_satellites = 0;
        GpsFixType fix_type = GpsFixType::NoFix;
    };

    /**
     * \class Gps
     * @brief Abstract GPS driver.
     *
     * Concrete implementation: GpsUblox.
     */
    class Gps : public SensorBase
    {
    public:
        explicit Gps(const char* name) noexcept;
        ~Gps() override = default;

        /**
         * @brief Get latest GPS data.
         * @return const GpsData&
         */
        const GpsData& getData() const noexcept;

        /**
         * @brief Check if GPS has a valid fix.
         * @return true if GPS has a valid fix.
         */
        bool hasFix() const noexcept;

    protected:
        GpsData m_data = {};
    };
} // namespace ascent::drivers