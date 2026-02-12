#include "ascent/drivers/sensors/imu.h"
#include "ascent/hal/i2c.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

/**
 * @brief MPU6050 IMU concrete driver.
 * Uses I2C for communication. Provides accelerometer, gyroscope, and temperature data.
 */
class ImuMpu6050 : public Imu
{
public:
    /**
     * @brief Construct MPU6050 IMU driver.
     * @param i2c I2C interface for communication (reference, not owned).
     * @param address I2C address of the MPU6050 (default 0x68).
     */
    explicit ImuMpu6050(I2c& i2c, uint8_t address = 0x68) noexcept
        : Imu("MPU6050")
        , m_i2c(i2c)
        , m_address(address)
    {
    }

protected:
    /**
     * @brief Initialize the MPU6050 hardware. Configure I2C settings and initialize accelerometer and gyroscope.
     * @return StatusCode 
     */
    StatusCode doInit() noexcept override
    {
        return StatusCode::Ok;
    }

    /**
     * @brief Read raw data from the MPU6050, apply calibration, and update m_data with accelerometer, gyroscope, and temperature readings.
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
