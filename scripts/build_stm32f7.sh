#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build/stm32f7"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake "$PROJECT_ROOT" \
    -DASCENT_PLATFORM=stm32f7 \
    -DCMAKE_TOOLCHAIN_FILE="$PROJECT_ROOT/cmake/stm32f7_toolchain.cmake"

make -j"$(nproc)"

echo "STM32F7 build complete: $BUILD_DIR"
