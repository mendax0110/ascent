#include <gtest/gtest.h>
#include "ascent/navigation/navigation_system.h"
#include "ascent/navigation/kalman_filter.h"
#include "ascent/core/types.h"

using namespace ascent;
using namespace ascent::navigation;
using namespace ascent::core;

class SensorFusionTest : public ::testing::Test
{
protected:
    NavigationSystem nav;

    void SetUp() override
    {
        nav.init();
    }
};

TEST_F(SensorFusionTest, InitialStateInvalid)
{
    EXPECT_FALSE(nav.getState().valid);
}

TEST_F(SensorFusionTest, FeedImuAndUpdate)
{
    drivers::ImuData imu;
    imu.accel = {0.0f, 0.0f, -9.81f};
    imu.gyro = {};

    nav.feedImu(imu);
    nav.update(0.01f);
}

TEST_F(SensorFusionTest, FeedBarometerAndUpdate)
{
    drivers::BarometerData baro;
    baro.pressure_pa = 101325.0f;
    baro.altitude_m = 100.0f;
    baro.temperature_c = 20.0f;

    nav.feedBarometer(baro);
    nav.update(0.01f);
}

TEST_F(SensorFusionTest, FeedGpsAndUpdate)
{
    drivers::GpsData gps;
    gps.fix_type = drivers::GpsFixType::Fix3D;
    gps.latitude_deg = 28.5729;
    gps.longitude_deg = -80.649;
    gps.altitude_m = 5.0f;
    gps.num_satellites = 10;

    nav.feedGps(gps);
    nav.update(0.01f);
}

TEST_F(SensorFusionTest, KalmanFilterIntegration)
{
    KalmanFilter1D alt_filter(0.1f, 1.0f, 0.0f);

    for (int i = 0; i < 50; ++i)
    {
        alt_filter.predict(0.01f);
        alt_filter.update(100.0f + static_cast<float>(i) * 0.1f);
    }

    EXPECT_GT(alt_filter.getEstimate(), 90.0f);
    EXPECT_LT(alt_filter.getEstimate(), 110.0f);
}

TEST_F(SensorFusionTest, MultiSensorUpdate)
{
    drivers::ImuData imu;
    imu.accel = {0.1f, 0.0f, -9.81f};
    imu.gyro = {0.01f, 0.0f, 0.0f};

    drivers::BarometerData baro;
    baro.altitude_m = 50.0f;

    for (int i = 0; i < 10; ++i)
    {
        nav.feedImu(imu);
        nav.feedBarometer(baro);
        nav.update(0.01f);
    }
}
