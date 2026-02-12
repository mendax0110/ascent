#include "ascent/hal/spi.h"

using namespace ascent::hal;

Spi::Spi(const SpiConfig& config) noexcept
    : m_config(config)
    , m_initialized(false)
{
    // Platform-specific SPI initialization
    m_initialized = true;
}

Spi::~Spi() noexcept
{
    if (m_initialized)
    {
        m_initialized = false;
    }
}

Spi::Spi(Spi&& other) noexcept
    : m_config(other.m_config)
    , m_initialized(other.m_initialized)
{
    other.m_initialized = false;
}

Spi& Spi::operator=(Spi&& other) noexcept
{
    if (this != &other)
    {
        m_config = other.m_config;
        m_initialized = other.m_initialized;
        other.m_initialized = false;
    }
    return *this;
}

StatusCode Spi::transfer(const uint8_t* tx_data, uint8_t* rx_data, size_t length) noexcept
{
    if (!m_initialized) return StatusCode::NotInitialized;
    // Platform-specific implementation
    return StatusCode::Ok;
}

StatusCode Spi::write(const uint8_t* data, size_t length) noexcept
{
    return transfer(data, nullptr, length);
}

StatusCode Spi::read(uint8_t* data, size_t length) noexcept
{
    return transfer(nullptr, data, length);
}

void Spi::selectChip() noexcept
{
    // Platform-specific CS assert
}

void Spi::deselectChip() noexcept
{
    // Platform-specific CS deassert
}
