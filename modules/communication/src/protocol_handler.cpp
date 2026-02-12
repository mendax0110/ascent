#include "ascent/communication/protocol_handler.h"
#include <algorithm>

using namespace ascent::communication;
using namespace ascent::core;

ProtocolHandler::ProtocolHandler() noexcept
{
}

StatusCode ProtocolHandler::framePacket(const uint8_t* payload, size_t payload_len, uint8_t* packet, size_t& packet_size) noexcept
{
    if (payload_len > kMaxPayloadSize)
    {
        return StatusCode::InvalidParam;
    }

    packet[0] = kSyncByte;
    packet[1] = static_cast<uint8_t>(payload_len & 0xFF);
    packet[2] = static_cast<uint8_t>((payload_len >> 8) & 0xFF);
    packet[3] = static_cast<uint8_t>(m_tx_sequence & 0xFF);
    packet[4] = static_cast<uint8_t>((m_tx_sequence >> 8) & 0xFF);

    std::copy_n(payload, payload_len, packet + kHeaderSize - 1);

    const uint16_t crc = computeCrc16(packet, kHeaderSize - 1 + payload_len);
    const size_t crc_pos = kHeaderSize - 1 + payload_len;
    packet[crc_pos] = static_cast<uint8_t>(crc & 0xFF);
    packet[crc_pos + 1] = static_cast<uint8_t>((crc >> 8) & 0xFF);

    packet_size = crc_pos + 2;
    ++m_tx_sequence;

    return StatusCode::Ok;
}

StatusCode ProtocolHandler::parsePacket(const uint8_t* packet, size_t packet_len, uint8_t* payload, size_t& payload_len) noexcept
{
    if (packet_len < kHeaderSize + 2)
    {
        return StatusCode::InvalidParam;
    }
    if (packet[0] != kSyncByte)
    {
        return StatusCode::InvalidParam;
    }

    const size_t len = static_cast<size_t>(packet[1]) | (static_cast<size_t>(packet[2]) << 8);
    if (len > kMaxPayloadSize || len + kHeaderSize + 1 > packet_len)
    {
        return StatusCode::InvalidParam;
    }

    std::copy_n(packet + kHeaderSize - 1, len, payload);
    payload_len = len;

    return StatusCode::Ok;
}

uint16_t ProtocolHandler::computeCrc16(const uint8_t* data, size_t length) noexcept
{
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; ++i)
    {
        crc ^= data[i];
        for (uint8_t bit = 0; bit < 8; ++bit)
        {
            if (crc & 1)
            {
                crc = (crc >> 1) ^ 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}


