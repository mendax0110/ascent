#include "ascent/drivers/actuators/servo.h"

using namespace ascent::drivers;
using namespace ascent::core;
using namespace ascent::hal;

Servo::Servo(const char* name, std::unique_ptr<Pwm> pwm,
             const uint32_t min_pulse_us, const uint32_t max_pulse_us) noexcept
    : ActuatorBase(name)
    , m_pwm(std::move(pwm))
    , m_min_pulse_us(min_pulse_us)
    , m_max_pulse_us(max_pulse_us)
{
}

void Servo::setAngle(float angle_deg) noexcept
{
    if (m_state != ActuatorState::Ready && m_state != ActuatorState::Active)
    {
        return;
    }

    if (angle_deg < 0.0f) angle_deg = 0.0f;
    if (angle_deg > 180.0f) angle_deg = 180.0f;

    m_current_angle = angle_deg;
    const float ratio = angle_deg / 180.0f;
    const uint32_t pulse = m_min_pulse_us + static_cast<uint32_t>(ratio * static_cast<float>(m_max_pulse_us - m_min_pulse_us));

    if (m_pwm)
    {
        m_pwm->setPulseWidth(pulse);
    }
    m_state = ActuatorState::Active;
}

float Servo::getAngle() const noexcept
{
    return m_current_angle;
}

StatusCode Servo::doInit() noexcept
{
    if (m_pwm)
    {
        m_pwm->enable();
        return StatusCode::Ok;
    }
    return StatusCode::HardwareFault;
}

void Servo::doSafe() noexcept
{
    if (m_pwm)
    {
        m_pwm->setPulseWidth(m_min_pulse_us);
        m_pwm->disable();
    }
    m_current_angle = 0.0f;
}
