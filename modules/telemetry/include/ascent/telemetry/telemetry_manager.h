#pragma once

#include "ascent/core/types.h"
#include <cstdint>

/// @brief Telemetry packet formatter. \namespace ascent::telemetry
namespace ascent::telemetry
{
    /**
     * \class TelemetryManager
     * @brief Manages telemetry collection and transmission.
     */
    class TelemetryManager
    {
    public:
        TelemetryManager() noexcept;
        ~TelemetryManager() = default;

        TelemetryManager(const TelemetryManager&) = delete;
        TelemetryManager& operator=(const TelemetryManager&) = delete;
        TelemetryManager(TelemetryManager&&) = default;
        TelemetryManager& operator=(TelemetryManager&&) = default;

        /**
         * @brief Initialize the telemetry system.
         * @return ascent::core::StatusCode
         */
        core::StatusCode init() noexcept;

        /**
         * @brief Run one telemetry cycle (collect + transmit).
         */
        void update() noexcept;

        /**
         * @brief Set telemetry transmission rate.
         * @param rate_hz Transmission rate in Hz.
         */
        void setRate(uint32_t rate_hz) noexcept;

        /**
         * @brief Get total packets sent.
         * @return Total packets sent.
         */
        [[nodiscard]] uint32_t getPacketsSent() const noexcept;

    private:
        uint32_t m_rate_hz = 10;
        uint32_t m_packets_sent = 0;
        bool m_initialized = false;
    };
} // namespace ascent::telemetry