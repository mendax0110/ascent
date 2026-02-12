add_executable(flight_controller
    main.cpp
    src/flight_main.cpp
)

target_link_libraries(flight_controller
    PRIVATE
        ascent_core
        ascent_navigation
        ascent_propulsion
        ascent_communication
        ascent_telemetry
        ascent_safety
        ascent_drivers
        ascent_hal
)
