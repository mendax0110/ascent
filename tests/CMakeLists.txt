include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Helper: define a gtest test executable
function(ascent_add_test TARGET SOURCE)
    add_executable(${TARGET} ${SOURCE})
    target_link_libraries(${TARGET} PRIVATE GTest::gtest GTest::gtest_main ${ARGN})
    target_compile_options(${TARGET} PRIVATE -Wno-sign-conversion)
    add_test(NAME ${TARGET} COMMAND ${TARGET})
endfunction()

# --- Core unit tests ---
ascent_add_test(test_types         unit/core/test_types.cpp          ascent_core)
ascent_add_test(test_scheduler     unit/core/test_scheduler.cpp      ascent_core)
ascent_add_test(test_event_bus     unit/core/test_event_bus.cpp      ascent_core)
ascent_add_test(test_error_handler unit/core/test_error_handler.cpp  ascent_core)
ascent_add_test(test_system        unit/core/test_system.cpp         ascent_core)

# --- HAL unit tests ---
ascent_add_test(test_gpio unit/hal/test_gpio.cpp ascent_hal)
ascent_add_test(test_spi  unit/hal/test_spi.cpp  ascent_hal)
ascent_add_test(test_i2c  unit/hal/test_i2c.cpp  ascent_hal)
ascent_add_test(test_uart unit/hal/test_uart.cpp ascent_hal)

# --- Driver unit tests ---
ascent_add_test(test_imu       unit/drivers/test_imu.cpp       ascent_drivers)
ascent_add_test(test_barometer unit/drivers/test_barometer.cpp ascent_drivers)
ascent_add_test(test_gps       unit/drivers/test_gps.cpp       ascent_drivers)

# --- Module unit tests ---
ascent_add_test(test_navigation unit/modules/test_navigation.cpp ascent_navigation)
ascent_add_test(test_propulsion unit/modules/test_propulsion.cpp ascent_propulsion)
ascent_add_test(test_telemetry  unit/modules/test_telemetry.cpp  ascent_telemetry)
ascent_add_test(test_safety     unit/modules/test_safety.cpp     ascent_safety)

# --- Integration tests ---
ascent_add_test(test_flight_sequence integration/test_flight_sequence.cpp
    ascent_core ascent_navigation ascent_propulsion ascent_communication ascent_telemetry ascent_safety)

ascent_add_test(test_sensor_fusion integration/test_sensor_fusion.cpp
    ascent_core ascent_navigation)

ascent_add_test(test_telemetry_pipeline integration/test_telemetry_pipeline.cpp
    ascent_core ascent_communication ascent_telemetry)
