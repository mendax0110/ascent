#pragma once

#include "ascent/core/types.h"
#include <cstdint>

/// @brief Top-level safety monitor. Aggregates health checks, range safety, and abort conditions. \namespace ascent::safety
namespace ascent::safety
{
    /// @brief Alert levels for safety monitoring. \enum ascent::safety::AlertLevel
    enum class AlertLevel : uint8_t
    {
        None,
        Advisory,
        Caution,
        Warning,
        Critical
    };

    /**
     * \class SafetyMonitor
     * @brief Top-level safety monitor.
     *
     * Aggregates health checks, range safety, and abort conditions.
     */
    class SafetyMonitor
    {
    public:
        SafetyMonitor() noexcept;
        ~SafetyMonitor() = default;

        SafetyMonitor(const SafetyMonitor&) = delete;
        SafetyMonitor& operator=(const SafetyMonitor&) = delete;
        SafetyMonitor(SafetyMonitor&&) = default;
        SafetyMonitor& operator=(SafetyMonitor&&) = default;

        /**
         * @brief Initialize safety monitoring.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode init() noexcept;

        /**
         * @brief Run safety checks.
         */
        void update() noexcept;

        /**
         * @brief Get current alert level.
         * @return Current alert level.
         */
        [[nodiscard]] AlertLevel getAlertLevel() const noexcept;

        /**
         * @brief Check if abort is required.
         * @return True if abort is required, false otherwise.
         */
        [[nodiscard]] bool isAbortRequired() const noexcept;

    private:
        AlertLevel m_alert_level = AlertLevel::None;
        bool m_abort_required = false;
    };
} // namespace ascent::safety