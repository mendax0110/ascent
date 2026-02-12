#include "ascent/navigation/imu_fusion.h"

using namespace ascent::navigation;
using namespace ascent::drivers;

ImuFusion::ImuFusion() noexcept
    : m_calibration{
        {0, 0, 0},  // accel_bias
        {0, 0, 0},  // gyro_bias
        {1, 1, 1},  // accel_scale
        {1, 1, 1}   // gyro_scale
    }
{
}

ImuData ImuFusion::apply(const ImuData& raw) const noexcept
{
    ImuData calibrated;
    calibrated.accel.x = (raw.accel.x - m_calibration.accel_bias.x) * m_calibration.accel_scale.x;
    calibrated.accel.y = (raw.accel.y - m_calibration.accel_bias.y) * m_calibration.accel_scale.y;
    calibrated.accel.z = (raw.accel.z - m_calibration.accel_bias.z) * m_calibration.accel_scale.z;
    calibrated.gyro.x = (raw.gyro.x - m_calibration.gyro_bias.x) * m_calibration.gyro_scale.x;
    calibrated.gyro.y = (raw.gyro.y - m_calibration.gyro_bias.y) * m_calibration.gyro_scale.y;
    calibrated.gyro.z = (raw.gyro.z - m_calibration.gyro_bias.z) * m_calibration.gyro_scale.z;
    calibrated.temperature = raw.temperature;
    return calibrated;
}

void ImuFusion::setCalibration(const ImuCalibration& cal) noexcept
{
    m_calibration = cal;
}

const ImuCalibration& ImuFusion::getCalibration() const noexcept
{
    return m_calibration;
}


