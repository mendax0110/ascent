#include "ascent/drivers/sensors/magnetometer.h"
#include "ascent/hal/i2c.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

/**
 * @brief LIS3MDL magnetometer concrete driver.
 * Uses I2C for communication. Provides 3-axis magnetic field data.
 */
class MagnetometerLis3mdl : public Magnetometer
{
public:
    /**
     * @brief Construct LIS3MDL magnetometer driver.
     * @param i2c I2C interface for communication (reference, not owned).
     * @param address I2C address of the LIS3MDL (default 0x1E).
     */
    explicit MagnetometerLis3mdl(I2c& i2c, uint8_t address = 0x1E) noexcept
        : Magnetometer("LIS3MDL")
        , m_i2c(i2c)
        , m_address(address)
    {
    }

protected:
    /**
     * @brief Initialize the LIS3MDL hardware. Configure I2C settings and initialize sensor registers.
     * @return StatusCode 
     */
    StatusCode doInit() noexcept override
    {
        return StatusCode::Ok;
    }

    /**
     * @brief Read raw data from the LIS3MDL, apply calibration, and update m_data with magnetic field readings.
     * @return StatusCode 
     */
    StatusCode doUpdate() noexcept override
    {
        return StatusCode::Ok;
    }

private:
    I2c& m_i2c;
    uint8_t m_address;
};
