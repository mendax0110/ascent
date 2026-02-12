#include "ascent/communication/command_parser.h"
#include <cstring>

using namespace ascent::communication;

CommandParser::CommandParser() noexcept
{
}

void CommandParser::feed(const uint8_t* data, size_t length) noexcept
{
    for (size_t i = 0; i < length && m_write_pos < kBufferSize; ++i)
    {
        m_buffer[m_write_pos++] = data[i];
    }
    // Packet parsing will be implemented with protocol framing
}

bool CommandParser::hasCommand() const noexcept
{
    return m_has_pending;
}

Command CommandParser::getCommand() noexcept
{
    Command cmd = m_pending;
    m_pending = {};
    m_has_pending = false;
    return cmd;
}


