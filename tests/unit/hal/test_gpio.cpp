#include <gtest/gtest.h>
#include "ascent/hal/gpio.h"

using namespace ascent::hal;

TEST(Gpio, ConstructWithDefaults)
{
    constexpr PinId id{0, 5};
    const Gpio gpio(id);
    EXPECT_EQ(gpio.getId().port, 0);
    EXPECT_EQ(gpio.getId().pin, 5);
}

TEST(Gpio, ConstructAsOutput)
{
    constexpr PinId id{1, 3};
    const Gpio gpio(id, PinDirection::Output);
    EXPECT_EQ(gpio.getId().port, 1);
    EXPECT_EQ(gpio.getId().pin, 3);
}

TEST(Gpio, WriteAndRead)
{
    Gpio gpio({0, 0}, PinDirection::Output);
    gpio.write(true);
    gpio.write(false);
}

TEST(Gpio, SetHighSetLow)
{
    Gpio gpio({0, 1}, PinDirection::Output);
    gpio.setHigh();
    gpio.setLow();
}

TEST(Gpio, Toggle)
{
    Gpio gpio({0, 2}, PinDirection::Output);
    gpio.toggle();
}

TEST(Gpio, MoveConstruction)
{
    Gpio gpio1({2, 4}, PinDirection::Output);
    const Gpio gpio2(std::move(gpio1));
    EXPECT_EQ(gpio2.getId().port, 2);
    EXPECT_EQ(gpio2.getId().pin, 4);
}

TEST(Gpio, MoveAssignment)
{
    Gpio gpio1({3, 1}, PinDirection::Output);
    Gpio gpio2({0, 0});
    gpio2 = std::move(gpio1);
    EXPECT_EQ(gpio2.getId().port, 3);
    EXPECT_EQ(gpio2.getId().pin, 1);
}
