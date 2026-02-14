#include "ascent/communication/radio_link.h"

using namespace ascent::communication;
using namespace ascent::core;
using namespace ascent::hal;

RadioLink::RadioLink(ICommunication* comm, const uint32_t timeout_ms) noexcept
    : m_comm(comm)
    , m_timeout_ms(timeout_ms)
{
}

StatusCode RadioLink::init() noexcept
{
    if (m_comm == nullptr)
    {
        return StatusCode::InvalidParam;
    }
    const auto status = m_comm->init();
    if (status == StatusCode::Ok)
    {
        m_state = LinkState::Connected;
    }
    return status;
}

StatusCode RadioLink::send(const uint8_t* data, const size_t length) noexcept
{
    if (m_comm == nullptr)
    {
        return StatusCode::NotInitialized;
    }
    const auto status = m_comm->send(data, length);
    if (status == StatusCode::Ok)
    {
        ++m_stats.packets_sent;
    }
    return status;
}

StatusCode RadioLink::receive(uint8_t* data, const size_t max_length, size_t& received) noexcept
{
    if (m_comm == nullptr)
    {
        return StatusCode::NotInitialized;
    }
    const auto status = m_comm->receive(data, max_length, received);
    if (status == StatusCode::Ok && received > 0)
    {
        ++m_stats.packets_received;
    }
    return status;
}

void RadioLink::update(const uint32_t now_ms) noexcept
{
    if (m_stats.last_rx_ms > 0 && (now_ms - m_stats.last_rx_ms) > m_timeout_ms)
    {
        m_state = LinkState::Disconnected;
    }
}

LinkState RadioLink::getState() const noexcept
{
    return m_state;
}

const LinkStats& RadioLink::getStats() const noexcept
{
    return m_stats;
}


