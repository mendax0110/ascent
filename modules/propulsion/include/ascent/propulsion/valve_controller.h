#pragma once

#include "ascent/core/types.h"
#include "ascent/drivers/actuators/valve.h"
#include <cstdint>

/// @brief Valve controller managing multiple valves. \namespace ascent::propulsion
namespace ascent::propulsion
{
    /**
     * \class ValveController
     * @brief Valve controller managing multiple valves.
     */
    class ValveController
    {
    public:
        static constexpr uint32_t kMaxValves = 8;

        ValveController() noexcept;
        ~ValveController() = default;

        ValveController(const ValveController&) = delete;
        ValveController& operator=(const ValveController&) = delete;
        ValveController(ValveController&&) = default;
        ValveController& operator=(ValveController&&) = default;

        /**
         * @brief Register a valve.
         * @param valve Pointer to valve (not owned).
         * @return ascent::core::StatusCode 
         */
        core::StatusCode addValve(drivers::Valve* valve) noexcept;

        /**
         * @brief Open all registered valves.
         */
        void openAll() noexcept;

        /**
         * @brief Close all registered valves (safe state).
         */
        void closeAll() noexcept;

        /**
         * @brief Get number of registered valves.
         * @return Number of registered valves.
         */
        uint32_t getValveCount() const noexcept;

    private:
        drivers::Valve* m_valves[kMaxValves] = {};
        uint32_t m_valve_count = 0;
    };
} // namespace ascent::propulsion