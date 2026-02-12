#include <gtest/gtest.h>
#include "ascent/hal/uart.h"

using namespace ascent::hal;

TEST(Uart, ConstructWithConfig)
{
    UartConfig config;
    config.port = 1;
    config.baud = 9600;
    Uart uart(config);
}

TEST(Uart, WriteReturnsOk)
{
    Uart uart(UartConfig{});
    uint8_t data[] = {0x48, 0x49};
    auto status = uart.write(data, sizeof(data));
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(Uart, ReadReturnsOk)
{
    Uart uart(UartConfig{});
    uint8_t data[8] = {};
    size_t bytes_read = 0;
    auto status = uart.read(data, sizeof(data), bytes_read);
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(Uart, AvailableReturnsZeroInitially)
{
    Uart uart(UartConfig{});
    EXPECT_EQ(uart.available(), 0u);
}

TEST(Uart, Flush)
{
    Uart uart(UartConfig{});
    uart.flush();
}

TEST(Uart, MoveConstruction)
{
    UartConfig config;
    config.port = 2;
    Uart uart1(config);
    Uart uart2(std::move(uart1));
}
