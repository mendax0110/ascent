#include "mock_gpio.h"

using namespace ascent::sim;

void MockGpio::setHigh() noexcept
{
    m_state = true;
}

void MockGpio::setLow() noexcept
{
    m_state = false;
}

void MockGpio::toggle() noexcept
{
    m_state = !m_state;
}

bool MockGpio::read() const noexcept
{
    return m_state;
}

bool MockGpio::getState() const noexcept
{
    return m_state;
}
