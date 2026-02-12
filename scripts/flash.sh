#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build/stm32f7"
BINARY="$BUILD_DIR/applications/flight_controller/flight_controller.elf"

if [ ! -f "$BINARY" ]; then
    echo "Error: Binary not found at $BINARY"
    echo "Run build_stm32f7.sh first."
    exit 1
fi

echo "Flashing $BINARY ..."

if command -v openocd &> /dev/null; then
    openocd \
        -f interface/stlink-v2-1.cfg \
        -f target/stm32f7x.cfg \
        -c "program $BINARY verify reset exit"
elif command -v st-flash &> /dev/null; then
    st-flash --format ihex write "$BINARY"
else
    echo "Error: Neither openocd nor st-flash found on PATH."
    exit 1
fi

echo "Flash complete."
