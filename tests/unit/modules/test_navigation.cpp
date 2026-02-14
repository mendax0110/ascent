#include <gtest/gtest.h>
#include "ascent/navigation/kalman_filter.h"
#include "ascent/navigation/navigation_system.h"

using namespace ascent::navigation;
using namespace ascent::core;

class KalmanFilterTest : public ::testing::Test
{
protected:
    KalmanFilter1D filter{0.1f, 1.0f, 0.0f};
};

TEST_F(KalmanFilterTest, InitialEstimate)
{
    EXPECT_FLOAT_EQ(filter.getEstimate(), 0.0f);
}

TEST_F(KalmanFilterTest, UpdateMovesEstimate)
{
    filter.predict(0.01f);
    filter.update(10.0f);
    EXPECT_GT(filter.getEstimate(), 0.0f);
}

TEST_F(KalmanFilterTest, ConvergesToMeasurement)
{
    for (int i = 0; i < 100; ++i)
    {
        filter.predict(0.01f);
        filter.update(42.0f);
    }
    EXPECT_NEAR(filter.getEstimate(), 42.0f, 1.0f);
}

TEST_F(KalmanFilterTest, ResetClearsState)
{
    filter.predict(0.01f);
    filter.update(50.0f);
    filter.reset(0.0f);
    EXPECT_FLOAT_EQ(filter.getEstimate(), 0.0f);
}

TEST_F(KalmanFilterTest, CopyConstruction)
{
    filter.predict(0.01f);
    filter.update(20.0f);
    KalmanFilter1D copy(filter);
    EXPECT_FLOAT_EQ(copy.getEstimate(), filter.getEstimate());
}

// --- NavigationSystem ---

TEST(NavigationSystem, InitSucceeds)
{
    NavigationSystem nav;
    const auto status = nav.init();
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(NavigationSystem, InitialStateInvalid)
{
    NavigationSystem nav;
    nav.init();
    auto& state = nav.getState();
    EXPECT_FALSE(state.valid);
}

TEST(NavigationSystem, FeedImuAndUpdate)
{
    NavigationSystem nav;
    nav.init();

    ascent::drivers::ImuData imu_data;
    imu_data.accel = {0.0f, 0.0f, -9.81f};
    imu_data.gyro = {0.0f, 0.0f, 0.0f};
    nav.feedImu(imu_data);
    nav.update(0.01f);
}

TEST(NavigationSystem, FeedBarometer)
{
    NavigationSystem nav;
    nav.init();

    ascent::drivers::BarometerData baro_data;
    baro_data.pressure_pa = 101325.0f;
    baro_data.altitude_m = 100.0f;
    nav.feedBarometer(baro_data);
    nav.update(0.01f);
}
