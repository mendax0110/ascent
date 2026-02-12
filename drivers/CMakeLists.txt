add_library(ascent_drivers STATIC
    src/sensors/sensor_base.cpp
    src/sensors/imu_base.cpp
    src/sensors/barometer_base.cpp
    src/sensors/gps_base.cpp
    src/sensors/magnetometer_base.cpp
    src/sensors/imu_bmi088.cpp
    src/sensors/imu_mpu6050.cpp
    src/sensors/barometer_bmp388.cpp
    src/sensors/barometer_ms5611.cpp
    src/sensors/gps_ublox.cpp
    src/sensors/magnetometer_lis3mdl.cpp
    src/actuators/actuator_base.cpp
    src/actuators/servo.cpp
    src/actuators/valve.cpp
    src/actuators/pyro_channel.cpp
    src/actuators/igniter.cpp
)

target_include_directories(ascent_drivers
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ascent_drivers
    PUBLIC
        ascent_hal
)
