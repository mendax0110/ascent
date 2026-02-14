#include "ascent/telemetry/telemetry_manager.h"

using namespace ascent::telemetry;
using namespace ascent::core;

TelemetryManager::TelemetryManager() noexcept
{
}

StatusCode TelemetryManager::init() noexcept
{
    m_packets_sent = 0;
    m_initialized = true;
    return StatusCode::Ok;
}

void TelemetryManager::update() noexcept
{
    if (!m_initialized)
    {
        return;
    }
    // TODO AdrGos: Collect and transmit telemetry
}

void TelemetryManager::setRate(const uint32_t rate_hz) noexcept
{
    m_rate_hz = rate_hz;
}

uint32_t TelemetryManager::getPacketsSent() const noexcept
{
    return m_packets_sent;
}


