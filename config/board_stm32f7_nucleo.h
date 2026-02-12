#pragma once

#include <cstdint>
#include "ascent/hal/types.h"

/// @brief Board configuration for STM32F7 Nucleo. \namespace ascent::config
namespace ascent::config
{
    /// @brief Configuration parameters for STM32F7 Nucleo board. \struct BoardStm32f7
    struct BoardStm32f7
    {
        // Clock configuration
        static constexpr uint32_t kSystemClockHz = 216000000;
        static constexpr uint32_t kAhbClockHz = 216000000;
        static constexpr uint32_t kApb1ClockHz = 54000000;
        static constexpr uint32_t kApb2ClockHz = 108000000;

        // Watchdog and hardware presence
        static constexpr bool kHasHardwareWatchdog = true;
        static constexpr bool kHasRealHardware = true;

        // UART debug console
        static constexpr hal::UartPort kDebugUartPort = 3;
        static constexpr hal::BaudRate kDebugUartBaud = 115200;

        // SPI bus for IMU and barometer
        static constexpr hal::SpiBus kSensorSpiBus = 1;
        static constexpr uint32_t kSensorSpiClockHz = 10000000;

        // I2C bus for magnetometer
        static constexpr hal::I2cBus kSensorI2cBus = 1;
        static constexpr uint32_t kSensorI2cClockHz = 400000;

        // GPS UART
        static constexpr hal::UartPort kGpsUartPort = 2;
        static constexpr hal::BaudRate kGpsUartBaud = 9600;

        // Radio UART
        static constexpr hal::UartPort kRadioUartPort = 4;
        static constexpr hal::BaudRate kRadioUartBaud = 57600;

        // PWM channels for servos
        static constexpr uint8_t kServoTimerNum = 3;
        static constexpr uint8_t kServoChannel1 = 1;
        static constexpr uint8_t kServoChannel2 = 2;
    };
} // namespace ascent::config