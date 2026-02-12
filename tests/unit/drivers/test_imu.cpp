#include <gtest/gtest.h>
#include "ascent/drivers/sensors/imu.h"
#include "ascent/hal/spi.h"

using namespace ascent;
using namespace ascent::drivers;
using namespace ascent::hal;

class TestImu : public Imu
{
public:
    TestImu() noexcept : Imu("TestIMU") {}

protected:
    core::StatusCode doInit() noexcept override
    {
        m_data.accel = {0.0f, 0.0f, -9.81f};
        m_data.gyro = {0.0f, 0.0f, 0.0f};
        m_data.temperature = 25.0f;
        return core::StatusCode::Ok;
    }

    core::StatusCode doUpdate() noexcept override
    {
        m_data.accel.z = -9.81f;
        return core::StatusCode::Ok;
    }
};

TEST(Imu, DefaultDataIsZero)
{
    TestImu imu;
    auto& data = imu.getData();
    EXPECT_FLOAT_EQ(data.accel.x, 0.0f);
    EXPECT_FLOAT_EQ(data.accel.y, 0.0f);
    EXPECT_FLOAT_EQ(data.accel.z, 0.0f);
    EXPECT_FLOAT_EQ(data.temperature, 0.0f);
}

TEST(Imu, InitSetsState)
{
    TestImu imu;
    EXPECT_EQ(imu.getState(), SensorState::Uninitialized);
    auto status = imu.init();
    EXPECT_EQ(status, core::StatusCode::Ok);
    EXPECT_EQ(imu.getState(), SensorState::Ready);
}

TEST(Imu, InitPopulatesData)
{
    TestImu imu;
    imu.init();
    auto& data = imu.getData();
    EXPECT_FLOAT_EQ(data.accel.z, -9.81f);
    EXPECT_FLOAT_EQ(data.temperature, 25.0f);
}

TEST(Imu, UpdateIncrementsSampleCount)
{
    TestImu imu;
    imu.init();
    EXPECT_EQ(imu.getSampleCount(), 0u);
    imu.update();
    EXPECT_EQ(imu.getSampleCount(), 1u);
}

TEST(Imu, NameIsCorrect)
{
    TestImu imu;
    EXPECT_STREQ(imu.getName(), "TestIMU");
}

TEST(Imu, IsReadyAfterInit)
{
    TestImu imu;
    EXPECT_FALSE(imu.isReady());
    imu.init();
    EXPECT_TRUE(imu.isReady());
}
