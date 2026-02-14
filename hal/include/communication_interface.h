#pragma once

#include <cstdint>
#include <cstddef>
#include "ascent/core/types.h"

/// @brief Communication interface. Common interface for UART, radio, and other communication channels. \namespace ascent::hal
namespace ascent::hal
{
    /**
     * \class ICommunication
     * @brief Abstract communication interface.
     *
     * Common interface for UART, radio, and other communication channels.
     */
    class ICommunication
    {
    public:
        virtual ~ICommunication() = default;

        /**
         * @brief Initialize the communication channel.
         * @return Ok on success.
         */
        virtual core::StatusCode init() noexcept = 0;

        /**
         * @brief Send data.
         * @param data Data buffer.
         * @param length Number of bytes.
         * @return Ok on success.
         */
        virtual core::StatusCode send(const uint8_t* data, size_t length) noexcept = 0;

        /**
         * @brief Receive data.
         * @param data Receive buffer.
         * @param max_length Maximum bytes to receive.
         * @param received Actual bytes received.
         * @return Ok on success.
         */
        virtual core::StatusCode receive(uint8_t* data, size_t max_length, size_t& received) noexcept = 0;

        /**
         * @brief Check if data is available for reading.
         * @return Number of bytes available for reading.
         */
        [[nodiscard]] virtual size_t available() const noexcept = 0;

    protected:
        ICommunication() = default;
        ICommunication(const ICommunication&) = default;
        ICommunication& operator=(const ICommunication&) = default;
        ICommunication(ICommunication&&) = default;
        ICommunication& operator=(ICommunication&&) = default;
    };
} // namespace ascent::hal