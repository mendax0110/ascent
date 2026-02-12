#include "ascent/safety/abort_controller.h"

using namespace ascent::safety;

AbortController::AbortController() noexcept
{
}

void AbortController::triggerAbort(AbortReason reason) noexcept
{
    m_reason = reason;
    m_aborted = true;
}

void AbortController::update() noexcept
{
    if (!m_aborted)
    {
        return;
    }
    // TODO AdrGOs: Execute abort sequence steps (safe actuators, deploy recovery, etc...)
}

bool AbortController::isAborted() const noexcept
{
    return m_aborted;
}

AbortReason AbortController::getReason() const noexcept
{
    return m_reason;
}


