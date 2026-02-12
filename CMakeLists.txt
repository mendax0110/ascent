cmake_minimum_required(VERSION 3.16)
project(ascent
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "Rocket avionics flight software"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------
# Build options
# -----------------------------------------------------------------------------
option(ASCENT_BUILD_TESTS "Build unit and integration tests" ON)
option(ASCENT_BUILD_SIMULATION "Build desktop simulation" ON)
option(ASCENT_BUILD_DOCS "Build Doxygen documentation" OFF)
option(ASCENT_PLATFORM "Target platform: native or stm32f7" "native")

# -----------------------------------------------------------------------------
# Compiler warnings
# -----------------------------------------------------------------------------
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -Wno-unused-parameter
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-Os -DNDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0)
endif()

# -----------------------------------------------------------------------------
# Global include directories
# -----------------------------------------------------------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/config
)

# -----------------------------------------------------------------------------
# Libraries (bottom-up dependency order)
# -----------------------------------------------------------------------------
add_subdirectory(core)
add_subdirectory(hal)
add_subdirectory(drivers)
add_subdirectory(modules)

# -----------------------------------------------------------------------------
# Applications
# -----------------------------------------------------------------------------
add_subdirectory(applications)

# -----------------------------------------------------------------------------
# Optional targets
# -----------------------------------------------------------------------------
if(ASCENT_BUILD_SIMULATION)
    add_subdirectory(simulation)
endif()

if(ASCENT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
