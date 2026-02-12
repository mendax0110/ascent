#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build/native"

if [ ! -d "$BUILD_DIR" ]; then
    echo "Native build directory not found. Building first..."
    "$SCRIPT_DIR/build_native.sh"
fi

cd "$BUILD_DIR"
ctest --output-on-failure

echo "All tests passed."
