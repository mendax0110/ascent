#pragma once

#include "ascent/core/types.h"
#include <cstdint>
#include <array>

/// @brief Ignition sequence manager. Manages a timed sequence of ignition steps for motor startup. \namespace ascent::propulsion
namespace ascent::propulsion
{
    /// @brief Ignition step structure. Represents a single step in the ignition sequence with timing parameters.
    struct IgnitionStep
    {
        const char* name = nullptr;
        uint32_t delay_ms = 0;   // Delay before this step
        uint32_t hold_ms = 0;    // Duration of this step
        bool completed = false;
    };

    /**
     * \class IgnitionSequence
     * @brief Manages a timed ignition sequence.
     *
     * Executes a series of timed steps for motor ignition.
     */
    class IgnitionSequence
    {
    public:
        static constexpr uint32_t kMaxSteps = 8;

        IgnitionSequence() noexcept;
        ~IgnitionSequence() = default;

        IgnitionSequence(const IgnitionSequence&) = delete;
        IgnitionSequence& operator=(const IgnitionSequence&) = delete;
        IgnitionSequence(IgnitionSequence&&) = default;
        IgnitionSequence& operator=(IgnitionSequence&&) = default;

        /**
         * @brief Add a step to the sequence.
         * @param name Step identifier.
         * @param delay_ms Delay before this step in milliseconds.
         * @param hold_ms Duration of this step in milliseconds.
         * @return ascent::core::StatusCode
         */
        core::StatusCode addStep(const char* name, uint32_t delay_ms, uint32_t hold_ms) noexcept;

        /**
         * @brief Start the ignition sequence.
         * @return ascent::core::StatusCode 
         */
        core::StatusCode start() noexcept;

        /**
         * @brief Update the sequence (call each tick).
         * @param now_ms Current time in milliseconds.
         */
        void update(uint32_t now_ms) noexcept;

        /**
         * @brief Abort the sequence.
         */
        void abort() noexcept;

        /**
         * @brief Check if sequence is complete.
         * @return true if complete, false otherwise.
         */
        [[nodiscard]] bool isComplete() const noexcept;

        /**
        * @brief Check if sequence is running.
        * @return true if running, false otherwise.
        */
        [[nodiscard]] bool isRunning() const noexcept;

    private:
        std::array<IgnitionStep, kMaxSteps> m_steps = {};
        uint32_t m_step_count = 0;
        uint32_t m_current_step = 0;
        uint32_t m_step_start_ms = 0;
        bool m_running = false;
        bool m_complete = false;
    };

} // namespace ascent::propulsion