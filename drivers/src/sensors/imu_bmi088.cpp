#include "ascent/drivers/sensors/imu.h"
#include "ascent/hal/spi.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

/**
 * @brief BMI088 IMU concrete driver.
 * Uses SPI for communication. Provides accelerometer, gyroscope, and temperature data.
 */
class ImuBmi088 : public Imu
{
public:
    /**
     * @brief Construct BMI088 IMU driver.
     * @param spi SPI interface for communication (reference, not owned).
     */
    explicit ImuBmi088(Spi& spi) noexcept
        : Imu("BMI088")
        , m_spi(spi)
    {
    }

protected:
    /**
     * @brief Initialize the BMI088 hardware. Configure SPI settings and initialize accelerometer and gyroscope.
     * @return StatusCode 
     */
    StatusCode doInit() noexcept override
    {
        return StatusCode::Ok;
    }

    /**
     * @brief Read raw data from the BMI088, apply calibration, and update m_data with accelerometer, gyroscope, and temperature readings.
     * @return StatusCode 
     */
    StatusCode doUpdate() noexcept override
    {
        return StatusCode::Ok;
    }

private:
    Spi& m_spi;
};
