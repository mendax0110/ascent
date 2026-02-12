#pragma once

#include "ascent/core/types.h"
#include <cstdint>
#include <cstddef>

/// @brief Telemetry packet formatter. \namespace ascent::telemetry
namespace ascent::telemetry
{
    /// @brief Telemetry packet types. \enum ascent::telemetry::PacketType
    enum class PacketType : uint8_t
    {
        Status = 0x01,
        Navigation = 0x02,
        Sensor = 0x03,
        Propulsion = 0x04,
        Gps = 0x05,
        Event = 0x06
    };

    /**
     * \class PacketFormatter
     * @brief Formats structured data into telemetry packets.
     */
    class PacketFormatter
    {
    public:
        static constexpr size_t kMaxPacketSize = 256;

        PacketFormatter() noexcept;
        ~PacketFormatter() = default;

        PacketFormatter(const PacketFormatter&) = delete;
        PacketFormatter& operator=(const PacketFormatter&) = delete;
        PacketFormatter(PacketFormatter&&) = default;
        PacketFormatter& operator=(PacketFormatter&&) = default;

        /**
         * @brief Format a status telemetry packet.
         * @param buffer Output buffer.
         * @param buffer_size Buffer size.
         * @param written Bytes written.
         * @return Ok on success.
         */
        core::StatusCode formatStatus(uint8_t* buffer, size_t buffer_size, size_t& written) noexcept;

        /**
         * @brief Format a navigation telemetry packet.
         * @param buffer Output buffer.
         * @param buffer_size Buffer size.
         * @param written Bytes written.
         * @return Ok on success.
         */
        core::StatusCode formatNavigation(uint8_t* buffer, size_t buffer_size, size_t& written) noexcept;

    private:
        uint16_t m_sequence = 0;
    };
} // namespace ascent::telemetry