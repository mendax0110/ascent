# Navigation module
add_library(ascent_navigation STATIC
    navigation/src/navigation_system.cpp
    navigation/src/kalman_filter.cpp
    navigation/src/attitude_estimator.cpp
    navigation/src/altitude_estimator.cpp
    navigation/src/imu_fusion.cpp
    navigation/src/gps_handler.cpp
)

target_include_directories(ascent_navigation
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/navigation/include
)

target_link_libraries(ascent_navigation
    PUBLIC
        ascent_drivers
)

# Propulsion module
add_library(ascent_propulsion STATIC
    propulsion/src/propulsion_controller.cpp
    propulsion/src/ignition_sequence.cpp
    propulsion/src/valve_controller.cpp
    propulsion/src/thrust_monitor.cpp
)

target_include_directories(ascent_propulsion
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/propulsion/include
)

target_link_libraries(ascent_propulsion
    PUBLIC
        ascent_drivers
)

# Communication module
add_library(ascent_communication STATIC
    communication/src/radio_link.cpp
    communication/src/command_parser.cpp
    communication/src/protocol_handler.cpp
)

target_include_directories(ascent_communication
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/communication/include
)

target_link_libraries(ascent_communication
    PUBLIC
        ascent_hal
)

# Telemetry module
add_library(ascent_telemetry STATIC
    telemetry/src/telemetry_manager.cpp
    telemetry/src/packet_formatter.cpp
    telemetry/src/data_logger.cpp
)

target_include_directories(ascent_telemetry
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/telemetry/include
)

target_link_libraries(ascent_telemetry
    PUBLIC
        ascent_core
)

# Safety module
add_library(ascent_safety STATIC
    safety/src/safety_monitor.cpp
    safety/src/health_monitor.cpp
    safety/src/abort_controller.cpp
    safety/src/range_safety.cpp
)

target_include_directories(ascent_safety
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/safety/include
)

target_link_libraries(ascent_safety
    PUBLIC
        ascent_core
)
