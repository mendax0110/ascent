#pragma once

#include "ascent/core/types.h"
#include <cstdint>

/// @brief Abort sequence controller. Manages abort sequence execution. \namespace ascent::safety
namespace ascent::safety
{
    /// @brief Reasons for abort. \enum ascent::safety::AbortReason
    enum class AbortReason : uint8_t
    {
        None = 0,
        CommandReceived,
        OverSpeed,
        OffNominalTrajectory,
        SensorFailure,
        CommunicationLoss,
        HardwareFault,
        RangeSafetyViolation
    };

    /**
     * \class AbortController
     * @brief Manages abort sequence execution.
     */
    class AbortController
    {
    public:
        AbortController() noexcept;
        ~AbortController() = default;

        AbortController(const AbortController&) = delete;
        AbortController& operator=(const AbortController&) = delete;
        AbortController(AbortController&&) = default;
        AbortController& operator=(AbortController&&) = default;

        /**
         * @brief Trigger an abort.
         * @param reason Reason for abort.
         */
        void triggerAbort(AbortReason reason) noexcept;

        /**
         * @brief Execute abort sequence steps.
         */
        void update() noexcept;

        /**
         * @brief Check if abort has been triggered.
         * @return True if abort has been triggered, false otherwise.
         */
        bool isAborted() const noexcept;

        /**
         * @brief Get the abort reason.
         * @return Reason for abort.
         */
        AbortReason getReason() const noexcept;

    private:
        AbortReason m_reason = AbortReason::None;
        bool m_aborted = false;
    };
} // namespace ascent::safety