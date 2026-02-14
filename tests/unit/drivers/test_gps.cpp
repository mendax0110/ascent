#include <gtest/gtest.h>
#include "ascent/drivers/sensors/gps.h"

using namespace ascent;
using namespace ascent::drivers;
using namespace ascent::hal;

class TestGps : public Gps
{
public:
    TestGps() noexcept : Gps("TestGPS") {}

    void simulateFix() noexcept
    {
        m_data.fix_type = GpsFixType::Fix3D;
        m_data.latitude_deg = 28.5729;
        m_data.longitude_deg = -80.6490;
        m_data.altitude_m = 5.0f;
        m_data.num_satellites = 12;
        m_data.hdop = 0.9f;
    }

protected:
    core::StatusCode doInit() noexcept override
    {
        return core::StatusCode::Ok;
    }

    core::StatusCode doUpdate() noexcept override
    {
        return core::StatusCode::Ok;
    }
};

TEST(Gps, DefaultNoFix)
{
    TestGps gps;
    EXPECT_FALSE(gps.hasFix());
    auto& data = gps.getData();
    EXPECT_EQ(data.fix_type, GpsFixType::NoFix);
    EXPECT_EQ(data.num_satellites, 0);
}

TEST(Gps, InitSetsReady)
{
    TestGps gps;
    gps.init();
    EXPECT_EQ(gps.getState(), SensorState::Ready);
}

TEST(Gps, SimulateFixHasFix)
{
    TestGps gps;
    gps.init();
    gps.simulateFix();
    EXPECT_TRUE(gps.hasFix());

    auto& data = gps.getData();
    EXPECT_EQ(data.fix_type, GpsFixType::Fix3D);
    EXPECT_EQ(data.num_satellites, 12);
    EXPECT_NEAR(data.latitude_deg, 28.5729, 0.001);
    EXPECT_NEAR(data.longitude_deg, -80.649, 0.001);
    EXPECT_FLOAT_EQ(data.altitude_m, 5.0f);
}

TEST(Gps, DefaultHdop)
{
    const TestGps gps;
    EXPECT_FLOAT_EQ(gps.getData().hdop, 99.9f);
}

TEST(Gps, NameIsCorrect)
{
    const TestGps gps;
    EXPECT_STREQ(gps.getName(), "TestGPS");
}
