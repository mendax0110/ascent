#include "ascent/drivers/sensors/barometer.h"
#include "ascent/hal/spi.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

/**
 * @brief BMP388 barometer concrete driver.
 * Uses SPI for communication. Provides pressure, temperature, and altitude data.
 * Altitude is calculated using the barometric formula with a reference pressure.
 */
class BarometerBmp388 : public Barometer
{
public:

    /**
     * @brief Construct BMP388 barometer driver.
     * @param spi SPI interface for communication (reference, not owned).
     */
    explicit BarometerBmp388(Spi& spi) noexcept
        : Barometer("BMP388")
        , m_spi(spi)
    {
    }

protected:

    /**
     * @brief Initialize the BMP388 hardware. Perform sensor reset, read calibration data, and configure settings.
     * @return StatusCode 
     */
    StatusCode doInit() noexcept override
    {
        return StatusCode::Ok;
    }

    /**
     * @brief Read raw data from the BMP388, apply calibration, and update m_data with pressure, temperature, and altitude.
     * @return StatusCode 
     */
    StatusCode doUpdate() noexcept override
    {
        return StatusCode::Ok;
    }

private:
    Spi& m_spi;
};
