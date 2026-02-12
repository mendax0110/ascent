#include "ascent/telemetry/packet_formatter.h"

using namespace ascent::telemetry;
using namespace ascent::core;

PacketFormatter::PacketFormatter() noexcept
{
}

StatusCode PacketFormatter::formatStatus(uint8_t* buffer, size_t buffer_size, size_t& written) noexcept
{
    if (buffer_size < 16)
    {
        return StatusCode::InvalidParam;
    }
    // TODO AdrGos: implemented Status packet formatting
    written = 0;
    ++m_sequence;
    return StatusCode::Ok;
}

StatusCode PacketFormatter::formatNavigation(uint8_t* buffer, size_t buffer_size, size_t& written) noexcept
{
    if (buffer_size < 48)
    {
        return StatusCode::InvalidParam;
    }
    // TODO AdrGos: implemented Navigation packet formatting
    written = 0;
    ++m_sequence;
    return StatusCode::Ok;
}


