#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build/native"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake "$PROJECT_ROOT" \
    -DASCENT_PLATFORM=native \
    -DASCENT_BUILD_TESTS=ON \
    -DASCENT_BUILD_SIMULATION=ON

make -j"$(nproc)"

echo "Native build complete: $BUILD_DIR"
