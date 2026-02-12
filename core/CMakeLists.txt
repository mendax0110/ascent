add_library(ascent_core STATIC
    src/logger.cpp
    src/error_handler.cpp
    src/event_bus.cpp
    src/scheduler.cpp
    src/system.cpp
)

target_include_directories(ascent_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ascent_core PUBLIC cxx_std_17)
 