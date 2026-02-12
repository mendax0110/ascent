#include <gtest/gtest.h>
#include "ascent/safety/safety_monitor.h"
#include "ascent/safety/range_safety.h"
#include "ascent/safety/health_monitor.h"

using namespace ascent::safety;
using namespace ascent::core;

class SafetyMonitorTest : public ::testing::Test
{
protected:
    SafetyMonitor monitor;
};

TEST_F(SafetyMonitorTest, InitSucceeds)
{
    auto status = monitor.init();
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST_F(SafetyMonitorTest, InitialAlertLevelNone)
{
    EXPECT_EQ(monitor.getAlertLevel(), AlertLevel::None);
}

TEST_F(SafetyMonitorTest, InitiallyNoAbort)
{
    EXPECT_FALSE(monitor.isAbortRequired());
}

TEST_F(SafetyMonitorTest, UpdateDoesNotCrash)
{
    monitor.init();
    monitor.update();
}

class RangeSafetyTest : public ::testing::Test
{
protected:
    GeofenceConfig config;
    void SetUp() override
    {
        config.max_altitude_m = 10000.0f;
        config.max_range_m = 5000.0f;
        config.max_speed_ms = 400.0f;
        config.max_tilt_deg = 30.0f;
    }
};

TEST_F(RangeSafetyTest, WithinLimits)
{
    RangeSafety rs(config);
    Vec3f pos{100.0f, 200.0f, -500.0f};  // NED: -Z is up
    Vec3f vel{10.0f, 5.0f, -20.0f};
    EXPECT_TRUE(rs.checkLimits(pos, vel));
}

TEST_F(RangeSafetyTest, Origin)
{
    RangeSafety rs(config);
    Vec3f zero{};
    EXPECT_TRUE(rs.checkLimits(zero, zero));
}

TEST_F(RangeSafetyTest, DefaultConfig)
{
    RangeSafety rs;
    auto& cfg = rs.getConfig();
    EXPECT_FLOAT_EQ(cfg.max_altitude_m, 10000.0f);
    EXPECT_FLOAT_EQ(cfg.max_range_m, 5000.0f);
    EXPECT_FLOAT_EQ(cfg.max_speed_ms, 400.0f);
}

TEST_F(RangeSafetyTest, SetConfig)
{
    RangeSafety rs;
    GeofenceConfig custom;
    custom.max_altitude_m = 500.0f;
    rs.setConfig(custom);
    EXPECT_FLOAT_EQ(rs.getConfig().max_altitude_m, 500.0f);
}

TEST(HealthMonitor, InitialStatus)
{
    HealthMonitor hm;
    auto& status = hm.getStatus();
    EXPECT_FLOAT_EQ(status.battery_voltage, 0.0f);
    EXPECT_FALSE(status.all_ok);
}

TEST(HealthMonitor, SetBatteryLimits)
{
    HealthMonitor hm;
    hm.setBatteryLimits(3.0f, 3.3f);
}

TEST(HealthMonitor, UpdateDoesNotCrash)
{
    HealthMonitor hm;
    hm.update();
}
