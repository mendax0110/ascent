#include "ascent/propulsion/valve_controller.h"

using namespace ascent::propulsion;
using namespace ascent::core;
using namespace ascent::drivers;

ValveController::ValveController() noexcept
{
}

StatusCode ValveController::addValve(Valve* valve) noexcept
{
    if (valve == nullptr)
    {
        return StatusCode::InvalidParam;
    }
    if (m_valve_count >= kMaxValves)
    {
        return StatusCode::OutOfMemory;
    }

    m_valves[m_valve_count] = valve;
    ++m_valve_count;
    return StatusCode::Ok;
}

void ValveController::openAll() noexcept
{
    for (uint32_t i = 0; i < m_valve_count; ++i)
    {
        if (m_valves[i] != nullptr)
        {
            m_valves[i]->open();
        }
    }
}

void ValveController::closeAll() noexcept
{
    for (uint32_t i = 0; i < m_valve_count; ++i)
    {
        if (m_valves[i] != nullptr)
        {
            m_valves[i]->close();
        }
    }
}

uint32_t ValveController::getValveCount() const noexcept
{
    return m_valve_count;
}


