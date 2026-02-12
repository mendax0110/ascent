#pragma once

#include <cstdint>
#include "ascent/core/types.h"

/// @brief System lifecycle manager. \namespace ascent::core
namespace ascent::core
{
    /// @brief System states for lifecycle management. \enum SystemState
    enum class SystemState : uint8_t
    {
        Boot,
        Init,
        Idle,
        Armed,
        Launch,
        Ascent,
        Coast,
        Apogee,
        Descent,
        Recovery,
        Abort,
        Fault
    };

    /**
     * \class System
     * @brief System lifecycle manager.
     *
     * Manages initialization sequence, state transitions,
     * and orderly shutdown.
     */
    class System
    {
    public:
        System() = default;
        ~System() = default;

        System(const System&) = delete;
        System& operator=(const System&) = delete;
        System(System&&) = delete;
        System& operator=(System&&) = delete;

        /**
         * @brief Initialize all subsystems.
         * @return Ok on success, error code on failure.
         */
        StatusCode init() noexcept;

        /**
         * @brief Run the main loop. Does not return under normal operation.
         */
        void run() noexcept;

        /**
         * @brief Request a state transition.
         * @param new_state Desired state.
         * @return Ok if transition is valid.
         */
        StatusCode requestStateTransition(SystemState new_state) noexcept;

        /**
         * @brief Get current system state.
         * @return Current system state.
         */
        SystemState getState() const noexcept;

        /**
         * @brief Get system uptime in milliseconds.
         * @return Uptime in milliseconds since boot.
         */
        uint32_t getUptimeMs() const noexcept;

    private:
        SystemState m_state = SystemState::Boot;
        uint32_t m_boot_time_ms = 0;
        bool m_initialized = false;

        /**
         * @brief Validate a state transition.
         * @param from Current state.
         * @param to Desired new state.
         * @return True if transition is valid, false otherwise.
         */
        bool isValidTransition(SystemState from, SystemState to) const noexcept;
    };
} // namespace ascent::core
