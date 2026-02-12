#include "ascent/hal/i2c.h"

using namespace ascent::hal;

I2c::I2c(const I2cConfig& config) noexcept
    : m_config(config)
    , m_initialized(false)
{
    // Platform-specific I2C initialization
    m_initialized = true;
}

I2c::~I2c() noexcept
{
    if (m_initialized)
    {
        m_initialized = false;
    }
}

I2c::I2c(I2c&& other) noexcept
    : m_config(other.m_config)
    , m_initialized(other.m_initialized)
{
    other.m_initialized = false;
}

I2c& I2c::operator=(I2c&& other) noexcept
{
    if (this != &other)
    {
        m_config = other.m_config;
        m_initialized = other.m_initialized;
        other.m_initialized = false;
    }
    return *this;
}

StatusCode I2c::write(uint8_t address, const uint8_t* data, size_t length) noexcept
{
    if (!m_initialized) return StatusCode::NotInitialized;
    // Platform-specific implementation
    return StatusCode::Ok;
}

StatusCode I2c::read(uint8_t address, uint8_t* data, size_t length) noexcept
{
    if (!m_initialized) return StatusCode::NotInitialized;
    // Platform-specific implementation
    return StatusCode::Ok;
}

StatusCode I2c::writeRead(uint8_t address, const uint8_t* tx_data, size_t tx_len,
                           uint8_t* rx_data, size_t rx_len) noexcept
{
    if (!m_initialized) return StatusCode::NotInitialized;
    // Platform-specific implementation
    return StatusCode::Ok;
}
