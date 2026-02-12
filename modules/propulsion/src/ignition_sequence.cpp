#include "ascent/propulsion/ignition_sequence.h"

using namespace ascent::propulsion;
using namespace ascent::core;

IgnitionSequence::IgnitionSequence() noexcept
{
}

StatusCode IgnitionSequence::addStep(const char* name, uint32_t delay_ms, uint32_t hold_ms) noexcept
{
    if (m_step_count >= kMaxSteps)
    {
        return StatusCode::OutOfMemory;
    }

    auto& step = m_steps[m_step_count];
    step.name = name;
    step.delay_ms = delay_ms;
    step.hold_ms = hold_ms;
    step.completed = false;
    ++m_step_count;

    return StatusCode::Ok;
}

StatusCode IgnitionSequence::start() noexcept
{
    if (m_step_count == 0)
    {
        return StatusCode::InvalidParam;
    }
    m_current_step = 0;
    m_step_start_ms = 0;
    m_running = true;
    m_complete = false;
    return StatusCode::Ok;
}

void IgnitionSequence::update(uint32_t now_ms) noexcept
{
    if (!m_running || m_complete)
    {
        return;
    }

    if (m_step_start_ms == 0)
    {
        m_step_start_ms = now_ms;
    }

    const auto& step = m_steps[m_current_step];
    const uint32_t elapsed = now_ms - m_step_start_ms;

    if (elapsed >= step.delay_ms + step.hold_ms)
    {
        m_steps[m_current_step].completed = true;
        ++m_current_step;
        m_step_start_ms = now_ms;

        if (m_current_step >= m_step_count)
        {
            m_complete = true;
            m_running = false;
        }
    }
}

void IgnitionSequence::abort() noexcept
{
    m_running = false;
}

bool IgnitionSequence::isComplete() const noexcept
{
    return m_complete;
}

bool IgnitionSequence::isRunning() const noexcept
{
    return m_running;
}


