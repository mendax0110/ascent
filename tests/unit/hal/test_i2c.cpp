#include <gtest/gtest.h>
#include "ascent/hal/i2c.h"

using namespace ascent::hal;

TEST(I2c, ConstructWithConfig)
{
    I2cConfig config;
    config.bus = 1;
    config.clock_hz = 400000;
    I2c i2c(config);
}

TEST(I2c, WriteReturnsOk)
{
    I2c i2c(I2cConfig{});
    constexpr uint8_t data[] = {0x10, 0x20};
    const auto status = i2c.write(0x68, data, sizeof(data));
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(I2c, ReadReturnsOk)
{
    I2c i2c(I2cConfig{});
    uint8_t data[4] = {};
    const auto status = i2c.read(0x68, data, sizeof(data));
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(I2c, WriteReadReturnsOk)
{
    I2c i2c(I2cConfig{});
    constexpr uint8_t tx[] = {0x75};
    uint8_t rx[1] = {};
    const auto status = i2c.writeRead(0x68, tx, 1, rx, 1);
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(I2c, MoveConstruction)
{
    I2cConfig config;
    config.bus = 0;
    I2c i2c1(config);
    I2c i2c2(std::move(i2c1));
}
