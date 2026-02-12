#include "ascent/hal/uart.h"

using namespace ascent::hal;

Uart::Uart(const UartConfig& config) noexcept
    : m_config(config)
    , m_initialized(false)
{
    // Platform-specific UART initialization
    m_initialized = true;
}

Uart::~Uart() noexcept
{
    if (m_initialized)
    {
        m_initialized = false;
    }
}

Uart::Uart(Uart&& other) noexcept
    : m_config(other.m_config)
    , m_initialized(other.m_initialized)
{
    other.m_initialized = false;
}

Uart& Uart::operator=(Uart&& other) noexcept
{
    if (this != &other)
    {
        m_config = other.m_config;
        m_initialized = other.m_initialized;
        other.m_initialized = false;
    }
    return *this;
}

StatusCode Uart::write(const uint8_t* data, size_t length) noexcept
{
    if (!m_initialized) return StatusCode::NotInitialized;
    // Platform-specific implementation
    return StatusCode::Ok;
}

StatusCode Uart::read(uint8_t* data, size_t length, size_t& bytes_read) noexcept
{
    if (!m_initialized) return StatusCode::NotInitialized;
    bytes_read = 0;
    // Platform-specific implementation
    return StatusCode::Ok;
}

size_t Uart::available() const noexcept
{
    // Platform-specific implementation
    return 0;
}

void Uart::flush() noexcept
{
    // Platform-specific implementation
}
