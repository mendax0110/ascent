#pragma once

#include "ascent/drivers/actuators/actuator_base.h"

/// @brief Mock actuator for testing. \namespace ascent::sim
namespace ascent::sim
{
    /**
     * @class MockActuator
     * @brief Mock actuator for testing.
     */
    class MockActuator : public drivers::ActuatorBase
    {
    public:
        explicit MockActuator(const char* name = "MOCK_ACTUATOR") noexcept;
        ~MockActuator() override = default;

        /**
         * @brief Check if safe() was called.
         * @return true if safe() was called at least once.
         */
        [[nodiscard]] bool wasSafed() const noexcept;

        /**
         * @brief Get number of times safe() was called.
         * @return Number of times safe() was called. 
         */
        [[nodiscard]] uint32_t getSafeCount() const noexcept;

    protected:
        /**
         * @brief Initialize the mock actuator (no-op).
         * @return ascent::core::StatusCode 
         */
        core::StatusCode doInit() noexcept override;
        
        /**
         * @brief Increment safe count to track calls to safe().
         */
        void doSafe() noexcept override;

    private:
        uint32_t m_safe_count = 0;
    };
} // namespace ascent::sim
