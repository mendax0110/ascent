#pragma once

#include "ascent/hal/types.h"

/// @brief I2C bus abstraction with RAII lifecycle. \namespace ascent::hal
namespace ascent::hal
{
    /**
     * \class I2c
     * @brief I2C bus abstraction with RAII lifecycle.
     */
    class I2c
    {
    public:
        /**
         * @brief Construct and initialize I2C peripheral.
         * @param config I2C bus configuration.
         */
        explicit I2c(const I2cConfig& config) noexcept;
        ~I2c() noexcept;

        I2c(const I2c&) = delete;
        I2c& operator=(const I2c&) = delete;
        I2c(I2c&& other) noexcept;
        I2c& operator=(I2c&& other) noexcept;

        /**
         * @brief Write data to I2C device.
         * @param address 7-bit device address.
         * @param data Data buffer.
         * @param length Number of bytes.
         * @return Ok on success.
         */
        StatusCode write(uint8_t address, const uint8_t* data, size_t length) noexcept;

        /**
         * @brief Read data from I2C device.
         * @param address 7-bit device address.
         * @param data Receive buffer.
         * @param length Number of bytes.
         * @return Ok on success.
         */
        StatusCode read(uint8_t address, uint8_t* data, size_t length) noexcept;

        /**
         * @brief Write then read in a single transaction (repeated start).
         * @param address 7-bit device address.
         * @param tx_data Transmit buffer.
         * @param tx_len Transmit length.
         * @param rx_data Receive buffer.
         * @param rx_len Receive length.
         * @return Ok on success.
         */
        StatusCode writeRead(uint8_t address, const uint8_t* tx_data, size_t tx_len, uint8_t* rx_data, size_t rx_len) noexcept;

    private:
        I2cConfig m_config;
        bool m_initialized = false;
    };
} // namespace ascent::hal