#pragma once

#include "ascent/core/types.h"
#include <cstdint>
#include <cstddef>

/// @brief Protocol handler for ground station communication. Handles packet framing, CRC, and acknowledgments. \namespace ascent::communication
namespace ascent::communication
{
    /**
     * \class ProtocolHandler
     * @brief Handles packet framing, CRC, and acknowledgments.
     */
    class ProtocolHandler
    {
    public:
        static constexpr uint8_t kSyncByte = 0xAA;
        static constexpr size_t kMaxPayloadSize = 240;
        static constexpr size_t kHeaderSize = 6;

        ProtocolHandler() noexcept;
        ~ProtocolHandler() = default;

        ProtocolHandler(const ProtocolHandler&) = delete;
        ProtocolHandler& operator=(const ProtocolHandler&) = delete;
        ProtocolHandler(ProtocolHandler&&) = default;
        ProtocolHandler& operator=(ProtocolHandler&&) = default;

        /**
         * @brief Frame a payload into a packet.
         * @param payload Payload data.
         * @param payload_len Payload length.
         * @param packet Output packet buffer.
         * @param packet_size Output packet size.
         * @return Ok on success.
         */
        core::StatusCode framePacket(const uint8_t* payload, size_t payload_len, uint8_t* packet, size_t& packet_size) noexcept;

        /**
         * @brief Parse a received packet and extract payload.
         * @param packet Raw packet data.
         * @param packet_len Packet length.
         * @param payload Output payload buffer.
         * @param payload_len Output payload length.
         * @return Ok if packet is valid.
         */
        core::StatusCode parsePacket(const uint8_t* packet, size_t packet_len, uint8_t* payload, size_t& payload_len) noexcept;

        /**
         * @brief Compute CRC-16 over data.
         * @param data Input data buffer.
         * @param length Number of bytes.
         * @return CRC-16 value.
         */
        static uint16_t computeCrc16(const uint8_t* data, size_t length) noexcept;

    private:
        uint16_t m_tx_sequence = 0;
    };
} // namespace ascent::communication