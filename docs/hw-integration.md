# Hardware Integration

## Target Board

**STM32F7 Nucleo-F767ZI**

| Parameter | Value |
|---|---|
| MCU | STM32F767ZI |
| Core | ARM Cortex-M7 |
| Clock | 216 MHz |
| Flash | 1 MB |
| RAM | 320 KB SRAM + 16 KB DTCM |
| FPU | Double-precision |

## Pin Assignments

Defined in `config/board_stm32f7_nucleo.h`.

| Function | Bus | Pins |
|---|---|---|
| IMU (BMI088) | SPI1 | MOSI=PA7, MISO=PA6, SCK=PA5, CS=PA4 |
| Barometer (MS5611) | SPI2 | MOSI=PB15, MISO=PB14, SCK=PB13, CS=PB12 |
| GPS (u-blox) | UART2 | TX=PD5, RX=PD6 |
| Magnetometer (LIS3MDL) | I2C1 | SDA=PB9, SCL=PB8, Addr=0x1E |
| Radio | UART1 | TX=PA9, RX=PA10 |
| Servo TVC | PWM | CH1=PE9, CH2=PE11 |
| Pyro channels | GPIO | Fire=PC0, Arm=PC1, Cont=PC2 |
| Status LED | GPIO | PB0 |

## Sensor Wiring

1. Connect IMU via SPI1 with dedicated chip-select (PA4).
2. Connect barometer via SPI2 with dedicated chip-select (PB12).
3. GPS module via UART2 at 9600 baud (default u-blox rate).
4. Magnetometer via I2C1 with 400 kHz clock.

## Actuator Wiring

1. TVC servos on PWM timer channels at 50 Hz.
2. Pyro channels require external MOSFET drivers. Arm/Fire/Continuity are active-high logic.

## Watchdog

The independent watchdog (IWDG) is configured with a 500 ms timeout.
The main loop must call `Watchdog::feed()` within this window.

## Power

- Board powered via USB or external 7-12V on Vin.
- Pyro channels require separate battery supply with arming switch.
- Consider brownout detection for flight reliability.
