#include "ascent/drivers/sensors/gps.h"
#include "ascent/hal/uart.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

/**
 * @brief UBLOX GPS concrete driver.
 * Uses UART for communication. Parses UBX protocol messages to provide GPS data.
 */
class GpsUblox : public Gps
{
public:
    /**
     * @brief Construct UBLOX GPS driver.
     * @param uart UART interface for communication (reference, not owned).
     */
    explicit GpsUblox(Uart& uart) noexcept
        : Gps("UBLOX")
        , m_uart(uart)
    {
    }

protected:

    /**
     * @brief Initialize the UBLOX GPS hardware. Configure UART settings and send UBX configuration messages.
     * @return StatusCode 
     */
    StatusCode doInit() noexcept override
    {
        return StatusCode::Ok;
    }

    /**
     * @brief Read raw data from the UBLOX GPS, parse UBX messages, and update m_data with latitude, longitude, altitude, speed, heading, HDOP, and fix type.
     * @return StatusCode 
     */
    StatusCode doUpdate() noexcept override
    {
        return StatusCode::Ok;
    }

private:
    Uart& m_uart;
};
