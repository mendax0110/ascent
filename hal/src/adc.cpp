#include "ascent/hal/adc.h"

using namespace ascent::hal;
using namespace ascent::core;

Adc::Adc(AdcChannel channel, uint8_t resolution_bits) noexcept
    : m_channel(channel)
    , m_resolution_bits(resolution_bits)
    , m_initialized(false)
{
    // Platform-specific ADC initialization
    m_initialized = true;
}

Adc::~Adc() noexcept
{
    m_initialized = false;
}

Adc::Adc(Adc&& other) noexcept
    : m_channel(other.m_channel)
    , m_resolution_bits(other.m_resolution_bits)
    , m_initialized(other.m_initialized)
{
    other.m_initialized = false;
}

Adc& Adc::operator=(Adc&& other) noexcept
{
    if (this != &other)
    {
        m_channel = other.m_channel;
        m_resolution_bits = other.m_resolution_bits;
        m_initialized = other.m_initialized;
        other.m_initialized = false;
    }
    return *this;
}

Result<uint16_t> Adc::readRaw() noexcept
{
    if (!m_initialized)
    {
        return Result<uint16_t>::error(StatusCode::NotInitialized);
    }
    // Platform-specific implementation
    return Result<uint16_t>::success(0);
}

Result<uint32_t> Adc::readMillivolts(uint32_t vref_mv) noexcept
{
    auto raw = readRaw();
    if (!raw.ok())
    {
        return Result<uint32_t>::error(raw.status);
    }
    const uint32_t max_val = (1U << m_resolution_bits) - 1;
    const uint32_t mv = (static_cast<uint32_t>(raw.value) * vref_mv) / max_val;
    return Result<uint32_t>::success(mv);
}
