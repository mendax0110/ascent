#include "ascent/drivers/sensors/barometer.h"
#include "ascent/hal/spi.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

/**
 * @brief MS5611 barometer concrete driver.
 * Uses SPI for communication. Provides pressure, temperature, and altitude data.
 * Altitude is calculated using the barometric formula with a reference pressure.
 */
class BarometerMs5611 : public Barometer
{
public:

    /**
     * @brief Construct MS5611 barometer driver.
     * @param spi SPI interface for communication (reference, not owned).
     */
    explicit BarometerMs5611(Spi& spi) noexcept
        : Barometer("MS5611")
        , m_spi(spi)
    {
    }

protected:

    /**
     * @brief Initialize the MS5611 hardware. Perform sensor reset, read calibration data, and configure settings.
     * @return StatusCode 
     */
    StatusCode doInit() noexcept override
    {
        return StatusCode::Ok;
    }

    /**
     * @brief Read raw data from the MS5611, apply calibration, and update m_data with pressure, temperature, and altitude.
     * @return StatusCode 
     */
    StatusCode doUpdate() noexcept override
    {
        return StatusCode::Ok;
    }

private:
    Spi& m_spi;
};
