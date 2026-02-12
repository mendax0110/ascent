add_library(ascent_mock_hardware STATIC
    mock_hardware/src/mock_sensor.cpp
    mock_hardware/src/mock_actuator.cpp
    mock_hardware/src/mock_gpio.cpp
)

target_include_directories(ascent_mock_hardware
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/mock_hardware/include
)

target_link_libraries(ascent_mock_hardware
    PUBLIC
        ascent_drivers
)

add_executable(desktop_runner
    desktop_runner/src/desktop_main.cpp
)

target_link_libraries(desktop_runner
    PRIVATE
        ascent_core
        ascent_mock_hardware
        ascent_navigation
        ascent_propulsion
        ascent_communication
        ascent_telemetry
        ascent_safety
)
