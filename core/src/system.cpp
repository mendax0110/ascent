#include "system.h"
#include "ascent/core/logger.h"
#include "error_handler.h"
#include "event_bus.h"

using namespace ascent::core;

StatusCode System::init() noexcept
{
    if (m_initialized)
    {
        return StatusCode::Ok;
    }

    Logger::init(LogLevel::Info);
    ErrorHandler::init();
    EventBus::init();

    m_state = SystemState::Init;
    m_initialized = true;

    Logger::log(LogLevel::Info, "SYS", "System initialized");

    EventBus::publish({EventId::SystemInit, 0, 0});

    m_state = SystemState::Idle;
    EventBus::publish({EventId::SystemReady, 0, 0});

    return StatusCode::Ok;
}

void System::run() noexcept
{
    Logger::log(LogLevel::Info, "SYS", "Entering main loop");
}

StatusCode System::requestStateTransition(SystemState new_state) noexcept
{
    if (!isValidTransition(m_state, new_state))
    {
        Logger::log(LogLevel::Warning, "SYS", "Invalid state transition %u -> %u", static_cast<uint8_t>(m_state), static_cast<uint8_t>(new_state));
        return StatusCode::InvalidParam;
    }

    Logger::log(LogLevel::Info, "SYS", "State: %u -> %u", static_cast<uint8_t>(m_state), static_cast<uint8_t>(new_state));
    m_state = new_state;

    return StatusCode::Ok;
}

SystemState System::getState() const noexcept
{
    return m_state;
}

uint32_t System::getUptimeMs() const noexcept
{
    return 0;
}

bool System::isValidTransition(SystemState from, SystemState to) const noexcept
{
    if (to == SystemState::Abort || to == SystemState::Fault)
    {
        return true;
    }

    switch (from)
    {
        case SystemState::Boot:    return to == SystemState::Init;
        case SystemState::Init:    return to == SystemState::Idle;
        case SystemState::Idle:    return to == SystemState::Armed;
        case SystemState::Armed:   return to == SystemState::Launch || to == SystemState::Idle;
        case SystemState::Launch:  return to == SystemState::Ascent;
        case SystemState::Ascent:  return to == SystemState::Coast;
        case SystemState::Coast:   return to == SystemState::Apogee;
        case SystemState::Apogee:  return to == SystemState::Descent;
        case SystemState::Descent: return to == SystemState::Recovery;
        default: return false;
    }
}
