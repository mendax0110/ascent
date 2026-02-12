#pragma once

#include <cstdint>
#include "ascent/core/types.h"

/// @brief Common hardware types and definitions. \namespace ascent::hal
namespace ascent::hal
{
    using core::StatusCode;

    /// @brief GPIO pin identifier. Combines port and pin number for microcontrollers with multiple GPIO ports. \struct ascent::hal::PinId     
    struct PinId
    {
        uint8_t port = 0;
        uint8_t pin = 0;
    };

    /// @brief GPIO pin direction. \enum class PinDirection
    enum class PinDirection : uint8_t
    {
        Input,
        Output,
        AlternateFunction,
        Analog
    };

    /// @brief GPIO pull-up/pull-down configuration. \enum class PullMode
    enum class PullMode : uint8_t
    {
        None,
        Up,
        Down
    };

    using SpiBus = uint8_t;
    using I2cBus = uint8_t;
    using UartPort = uint8_t;
    using AdcChannel = uint8_t;

    /// @brief PWM channel identifier. Combines timer and channel number for microcontrollers with multiple timers. \struct ascent::hal::PwmChannel
    struct PwmChannel
    {
        uint8_t timer = 0;
        uint8_t channel = 0;
    };

    using BaudRate = uint32_t;

    /// @brief SPI configuration. \struct ascent::hal::SpiConfig
    struct SpiConfig
    {
        SpiBus bus = 0;
        PinId cs_pin = {};
        uint32_t clock_hz = 1000000;
        uint8_t mode = 0;
    };

    /// @brief I2C configuration. \struct ascent::hal::I2cConfig
    struct I2cConfig
    {
        I2cBus bus = 0;
        uint32_t clock_hz = 100000;
    };

    /// @brief UART configuration. \struct ascent::hal::UartConfig
    struct UartConfig
    {
        UartPort port = 0;
        BaudRate baud = 115200;
        uint8_t data_bits = 8;
        uint8_t stop_bits = 1;
    };
} // namespace ascent::hal