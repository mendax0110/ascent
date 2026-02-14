#include <gtest/gtest.h>
#include "ascent/drivers/sensors/barometer.h"

using namespace ascent;
using namespace ascent::drivers;
using namespace ascent::hal;

class TestBarometer : public Barometer
{
public:
    TestBarometer() noexcept : Barometer("TestBaro") {}

protected:
    core::StatusCode doInit() noexcept override
    {
        m_data.pressure_pa = 101325.0f;
        m_data.temperature_c = 20.0f;
        m_data.altitude_m = 0.0f;
        return core::StatusCode::Ok;
    }

    core::StatusCode doUpdate() noexcept override
    {
        return core::StatusCode::Ok;
    }
};

TEST(Barometer, DefaultDataIsZero)
{
    const TestBarometer baro;
    auto& data = baro.getData();
    EXPECT_FLOAT_EQ(data.pressure_pa, 0.0f);
    EXPECT_FLOAT_EQ(data.temperature_c, 0.0f);
    EXPECT_FLOAT_EQ(data.altitude_m, 0.0f);
}

TEST(Barometer, InitPopulatesData)
{
    TestBarometer baro;
    baro.init();
    auto& data = baro.getData();
    EXPECT_FLOAT_EQ(data.pressure_pa, 101325.0f);
    EXPECT_FLOAT_EQ(data.temperature_c, 20.0f);
}

TEST(Barometer, InitSetsReady)
{
    TestBarometer baro;
    EXPECT_EQ(baro.getState(), SensorState::Uninitialized);
    baro.init();
    EXPECT_EQ(baro.getState(), SensorState::Ready);
}

TEST(Barometer, SetReferencePressure)
{
    TestBarometer baro;
    baro.setReferencePressure(100000.0f);
}

TEST(Barometer, NameIsCorrect)
{
    TestBarometer baro;
    EXPECT_STREQ(baro.getName(), "TestBaro");
}

TEST(Barometer, UpdateIncrementsSampleCount)
{
    TestBarometer baro;
    baro.init();
    baro.update();
    EXPECT_EQ(baro.getSampleCount(), 1u);
}
