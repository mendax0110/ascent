#pragma once

#include "ascent/core/types.h"
#include <cstdint>

/// @brief Propulsion system controller. Coordinates ignition, valve control, and thrust monitoring. \namespace ascent::propulsion
namespace ascent::propulsion
{
    /// @brief Propulsion state enumeration. Represents the current state of the propulsion system. \enum ascent::propulsion::PropulsionState
    enum class PropulsionState : uint8_t
    {
        Safe,
        Armed,
        Igniting,
        Burning,
        Burnout,
        Abort
    };

    /**
     * \class PropulsionController
     * @brief Top-level propulsion system controller.
     *
     * Coordinates ignition sequence, valve control, and thrust monitoring.
     */
    class PropulsionController
    {
    public:
        PropulsionController() noexcept;
        ~PropulsionController() = default;

        PropulsionController(const PropulsionController&) = delete;
        PropulsionController& operator=(const PropulsionController&) = delete;
        PropulsionController(PropulsionController&&) = default;
        PropulsionController& operator=(PropulsionController&&) = default;

        /**
         * @brief Initialize propulsion subsystem.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode init() noexcept;

        /**
         * @brief Update propulsion state machine.
         */
        void update() noexcept;

        /**
         * @brief Arm the propulsion system.
         * @return ascent::core::StatusCode
         */
        core::StatusCode arm() noexcept;

        /**
         * @brief Disarm the propulsion system.
         */
        void disarm() noexcept;

        /**
         * @brief Initiate ignition sequence.
         * @return ascent::core::StatusCode
         */
        core::StatusCode ignite() noexcept;

        /**
         * @brief Emergency shutdown.
         */
        void abort() noexcept;

        /**
         * @brief Get current propulsion state.
         * @return ascent::propulsion::PropulsionState
         */
        [[nodiscard]] PropulsionState getState() const noexcept;

    private:
        PropulsionState m_state = PropulsionState::Safe;
    };
} // namespace ascent::propulsion