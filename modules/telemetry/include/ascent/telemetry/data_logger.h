#pragma once

#include "ascent/core/types.h"
#include <cstdint>
#include <cstddef>
#include <array>

/// @brief Flight data logger. \namespace ascent::telemetry
namespace ascent::telemetry
{
    /**
     * \class DataLogger
     * @brief Logs flight data to onboard storage.
     *
     * Uses a fixed-size ring buffer. Data is written in binary format
     * for minimal overhead.
     */
    class DataLogger
    {
    public:
        DataLogger() noexcept;
        ~DataLogger() = default;

        DataLogger(const DataLogger&) = delete;
        DataLogger& operator=(const DataLogger&) = delete;
        DataLogger(DataLogger&&) = default;
        DataLogger& operator=(DataLogger&&) = default;

        /**
         * @brief Initialize the data logger.
         * @return ascent::core::StatusCode
         */
        core::StatusCode init() noexcept;

        /**
         * @brief Log a data record.
         * @param data Raw data.
         * @param length Data length.
         * @return Ok on success.
         */
        core::StatusCode log(const uint8_t* data, size_t length) noexcept;

        /**
         * @brief Flush any buffered data to storage.
         */
        void flush() noexcept;

        /**
         * @brief Get total bytes logged.
         * @return Total bytes logged.
         */
        [[nodiscard]] uint32_t getBytesLogged() const noexcept;

        /**
         * @brief Enable or disable logging.
         * @param enabled True to enable logging, false to disable.
         */
        void setEnabled(bool enabled) noexcept;

    private:
        static constexpr size_t kBufferSize = 1024;
        std::array<uint8_t, kBufferSize> m_buffer = {};
        size_t m_write_pos = 0;
        uint32_t m_total_bytes = 0;
        bool m_enabled = false;
        bool m_initialized = false;
    };
} // namespace ascent::telemetry