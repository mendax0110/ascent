#pragma once

#include "ascent/hal/types.h"

/// @brief UART serial port abstraction with RAII lifecycle. \namespace ascent::hal
namespace ascent::hal
{
    /**
     * \class Uart
     * @brief UART serial port abstraction with RAII lifecycle.
     */
    class Uart
    {
    public:
        /**
         * @brief Construct and initialize UART peripheral.
         * @param config UART configuration.
         */
        explicit Uart(const UartConfig& config) noexcept;
        ~Uart() noexcept;

        Uart(const Uart&) = delete;
        Uart& operator=(const Uart&) = delete;
        Uart(Uart&& other) noexcept;
        Uart& operator=(Uart&& other) noexcept;

        /**
         * @brief Transmit data.
         * @param data Data buffer.
         * @param length Number of bytes.
         * @return Ok on success.
         */
        StatusCode write(const uint8_t* data, size_t length) noexcept;

        /**
         * @brief Receive data.
         * @param data Receive buffer.
         * @param length Maximum bytes to receive.
         * @param bytes_read Actual bytes received.
         * @return Ok on success.
         */
        StatusCode read(uint8_t* data, size_t length, size_t& bytes_read) noexcept;

        /**
         * @brief Check if data is available.
         * @return Number of bytes available in receive buffer.
         */
        size_t available() const noexcept;

        /**
         * @brief Flush transmit buffer.
         */
        void flush() noexcept;

    private:
        UartConfig m_config;
        bool m_initialized = false;
    };
} // namespace ascent::hal