#!/bin/bash
# Auto-format code using clang-format

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "Formatting C++ files..."
find "$SCRIPT_DIR/src" "$SCRIPT_DIR/include/tinymovr_ros" -type f \( -name "*.cpp" -o -name "*.hpp" \) \
  ! -path "*/tinymovr/*" \
  ! -path "*/socketcan_cpp/*" \
  -exec clang-format -i --style=file {} \;

echo "Formatting Python files..."
find "$SCRIPT_DIR/launch" -type f -name "*.py" -exec autopep8 --in-place --max-line-length 100 {} \;

echo "✓ Code formatting complete!"
