add_executable(groundstation_ifc
    main.cpp
    src/groundstation_main.cpp
)

target_link_libraries(groundstation_ifc
    PRIVATE
        ascent_core
        ascent_communication
        ascent_telemetry
        ascent_hal
)
