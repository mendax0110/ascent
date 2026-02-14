#include <gtest/gtest.h>
#include "ascent/hal/spi.h"

using namespace ascent::hal;

TEST(Spi, ConstructWithConfig)
{
    SpiConfig config;
    config.bus = 1;
    config.clock_hz = 4000000;
    config.mode = 0;
    Spi spi(config);
}

TEST(Spi, WriteReturnsOk)
{
    Spi spi(SpiConfig{});
    constexpr uint8_t data[] = {0x01, 0x02};
    const auto status = spi.write(data, sizeof(data));
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(Spi, ReadReturnsOk)
{
    Spi spi(SpiConfig{});
    uint8_t data[4] = {};
    const auto status = spi.read(data, sizeof(data));
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(Spi, TransferReturnsOk)
{
    Spi spi(SpiConfig{});
    constexpr uint8_t tx[2] = {0xAA, 0xBB};
    uint8_t rx[2] = {};
    const auto status = spi.transfer(tx, rx, 2);
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(Spi, ChipSelect)
{
    Spi spi(SpiConfig{});
    spi.selectChip();
    spi.deselectChip();
}

TEST(Spi, MoveConstruction)
{
    SpiConfig config;
    config.bus = 2;
    Spi spi1(config);
    Spi spi2(std::move(spi1));
}
