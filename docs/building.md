# Building Ascent

## Prerequisites

- CMake 3.16+
- C++17-capable compiler (GCC 9+, Clang 10+)
- For STM32F7: ARM GCC toolchain (`arm-none-eabi-gcc`)
- For docs: Doxygen

## Native Build (Desktop / Simulation)

```bash
./scripts/build_native.sh
```

Or manually:

```bash
mkdir -p build/native && cd build/native
cmake ../.. -DASCENT_PLATFORM=native -DASCENT_BUILD_SIMULATION=ON -DASCENT_BUILD_TESTS=ON
make -j$(nproc)
```

## STM32F7 Build

```bash
./scripts/build_stm32f7.sh
```

Or manually:

```bash
mkdir -p build/stm32f7 && cd build/stm32f7
cmake ../.. -DASCENT_PLATFORM=stm32f7 -DCMAKE_TOOLCHAIN_FILE=../../cmake/stm32f7_toolchain.cmake
make -j$(nproc)
```

## Running Tests

```bash
./scripts/run_tests.sh
```

Or from the native build directory:

```bash
cd build/native
ctest --output-on-failure
```

## Flashing

```bash
./scripts/flash.sh
```

Requires OpenOCD or ST-Link utilities.

## Generating Documentation

```bash
./scripts/generate_docs.sh
```

Output is placed in `build/docs/html/`.

## CMake Options

| Option | Default | Description |
|---|---|---|
| `ASCENT_PLATFORM` | `native` | Target platform (`native` or `stm32f7`) |
| `ASCENT_BUILD_TESTS` | `OFF` | Build unit and integration tests |
| `ASCENT_BUILD_SIMULATION` | `OFF` | Build simulation and mock hardware |
| `ASCENT_BUILD_DOCS` | `OFF` | Build Doxygen documentation |
