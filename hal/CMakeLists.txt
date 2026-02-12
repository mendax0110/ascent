add_library(ascent_hal STATIC
    src/gpio.cpp
    src/spi.cpp
    src/i2c.cpp
    src/uart.cpp
    src/pwm.cpp
    src/adc.cpp
    src/time.cpp
    src/watchdog.cpp
    src/sensor_interface.cpp
    src/actuator_interface.cpp
    src/communication_interface.cpp
    src/gpio_interface.cpp
)

target_include_directories(ascent_hal
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ascent_hal
    PUBLIC
        ascent_core
)
