#pragma once

#include "ascent/hal/types.h"

/// @brief SPI bus abstraction with RAII lifecycle. \namespace ascent::hal
namespace ascent::hal 
{
    /**
     * \class Spi
     * @brief SPI bus abstraction with RAII lifecycle.
     */
    class Spi
    {
    public:
        /**
         * @brief Construct and initialize SPI peripheral.
         * @param config SPI bus configuration.
         */
        explicit Spi(const SpiConfig& config) noexcept;
        ~Spi() noexcept;

        Spi(const Spi&) = delete;
        Spi& operator=(const Spi&) = delete;
        Spi(Spi&& other) noexcept;
        Spi& operator=(Spi&& other) noexcept;

        /**
         * @brief Transmit and receive data.
         * @param tx_data Transmit buffer.
         * @param rx_data Receive buffer.
         * @param length Number of bytes to transfer.
         * @return Ok on success.
         */
        StatusCode transfer(const uint8_t* tx_data, uint8_t* rx_data, size_t length) noexcept;

        /**
         * @brief Write data to SPI bus.
         * @param data Data buffer.
         * @param length Number of bytes.
         * @return Ok on success.
         */
        StatusCode write(const uint8_t* data, size_t length) noexcept;

        /**
         * @brief Read data from SPI bus.
         * @param data Receive buffer.
         * @param length Number of bytes.
         * @return Ok on success.
         */
        StatusCode read(uint8_t* data, size_t length) noexcept;

        /**
         * @brief Assert chip select (active low).
         */
        void selectChip() noexcept;

        /**
         * @brief Deassert chip select.
         */
        void deselectChip() noexcept;

    private:
        SpiConfig m_config;
        bool m_initialized = false;
    };
} // namespace ascent::hal