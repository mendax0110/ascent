#include "ascent/propulsion/propulsion_controller.h"

using namespace ascent::propulsion;
using namespace ascent::core;

PropulsionController::PropulsionController() noexcept
{
}

StatusCode PropulsionController::init() noexcept
{
    m_state = PropulsionState::Safe;
    return StatusCode::Ok;
}

void PropulsionController::update() noexcept
{
    // TODO AdrGos : State machine update here
}

StatusCode PropulsionController::arm() noexcept
{
    if (m_state != PropulsionState::Safe)
    {
        return StatusCode::InvalidParam;
    }
    m_state = PropulsionState::Armed;
    return StatusCode::Ok;
}

void PropulsionController::disarm() noexcept
{
    m_state = PropulsionState::Safe;
}

StatusCode PropulsionController::ignite() noexcept
{
    if (m_state != PropulsionState::Armed)
    {
        return StatusCode::InvalidParam;
    }
    m_state = PropulsionState::Igniting;
    return StatusCode::Ok;
}

void PropulsionController::abort() noexcept
{
    m_state = PropulsionState::Abort;
}

PropulsionState PropulsionController::getState() const noexcept
{
    return m_state;
}


