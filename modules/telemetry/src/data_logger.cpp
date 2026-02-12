#include "ascent/telemetry/data_logger.h"
#include <algorithm>

using namespace ascent::telemetry;
using namespace ascent::core;

DataLogger::DataLogger() noexcept
{
}

StatusCode DataLogger::init() noexcept
{
    m_write_pos = 0;
    m_total_bytes = 0;
    m_initialized = true;
    return StatusCode::Ok;
}

StatusCode DataLogger::log(const uint8_t* data, size_t length) noexcept
{
    if (!m_enabled || !m_initialized)
    {
        return StatusCode::NotInitialized;
    }
    if (m_write_pos + length > kBufferSize)
    {
        flush();
    }
    if (length > kBufferSize)
    {
        return StatusCode::InvalidParam;
    }

    std::copy_n(data, length, m_buffer.data() + m_write_pos);
    m_write_pos += length;
    m_total_bytes += static_cast<uint32_t>(length);
    return StatusCode::Ok;
}

void DataLogger::flush() noexcept
{
    // TODO AdrGos: Write buffer to persistent storage (SD card)
    m_write_pos = 0;
}

uint32_t DataLogger::getBytesLogged() const noexcept
{
    return m_total_bytes;
}

void DataLogger::setEnabled(bool enabled) noexcept
{
    m_enabled = enabled;
}


