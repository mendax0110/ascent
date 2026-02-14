#pragma once

#include "communication_interface.h"
#include "ascent/core/types.h"
#include <cstdint>

/// @brief Radio link management for ground station communication. Wraps an ICommunication interface and adds link management, statistics, and timeout detection. \namespace ascent::communication
namespace ascent::communication
{
    /// @brief Link state enumeration. \enum ascent::communication::LinkState
    enum class LinkState : uint8_t
    {
        Disconnected,
        Connected,
        Degraded,
        Error
    };

    /// @brief Link statistics structure. \struct ascent::communication::LinkStats
    struct LinkStats
    {
        uint32_t packets_sent = 0;
        uint32_t packets_received = 0;
        uint32_t packets_dropped = 0;
        int8_t rssi_dbm = 0;
        uint32_t last_rx_ms = 0;
    };

    /**
     * \class RadioLink
     * @brief Manages a radio communication link.
     *
     * Wraps an ICommunication interface and adds link management,
     * statistics, and timeout detection.
     */
    class RadioLink
    {
    public:
        /**
         * @brief Construct radio link.
         * @param comm Communication interface (not owned).
         * @param timeout_ms Link timeout in milliseconds.
         */
        explicit RadioLink(hal::ICommunication* comm, uint32_t timeout_ms = 5000) noexcept;
        ~RadioLink() = default;

        RadioLink(const RadioLink&) = delete;
        RadioLink& operator=(const RadioLink&) = delete;
        RadioLink(RadioLink&&) = default;
        RadioLink& operator=(RadioLink&&) = default;

        /**
         * @brief Initialize the radio link.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode init() noexcept;

        /**
         * @brief Send a packet.
         * @param data Data buffer to send.
         * @param length Number of bytes to send.
         * @return Ok on success, error code on failure.
         */
        core::StatusCode send(const uint8_t* data, size_t length) noexcept;

        /**
         * @brief Receive a packet.
         * @param data Output buffer for received data.
         * @param max_length Maximum number of bytes to receive.
         * @param received Output number of bytes received.
         * @return Ok on success, error code on failure.
         */
        core::StatusCode receive(uint8_t* data, size_t max_length, size_t& received) noexcept;

        /**
         * @brief Update link state (check timeouts).
         * @param now_ms Current time.
         */
        void update(uint32_t now_ms) noexcept;

        /**
         * @brief Get link state.
         * @return LinkState
         */
        [[nodiscard]] LinkState getState() const noexcept;

        /**
         * @brief Get link statistics.
         * @return LinkStats reference.
         */
        [[nodiscard]] const LinkStats& getStats() const noexcept;

    private:
        hal::ICommunication* m_comm;
        uint32_t m_timeout_ms;
        LinkState m_state = LinkState::Disconnected;
        LinkStats m_stats;
    };
} // namespace ascent::communication