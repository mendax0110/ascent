#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

if ! command -v doxygen &> /dev/null; then
    echo "Error: doxygen not found on PATH."
    exit 1
fi

cd "$PROJECT_ROOT/docs/doxygen"
doxygen Doxyfile

echo "Documentation generated in $PROJECT_ROOT/build/docs/html/"
