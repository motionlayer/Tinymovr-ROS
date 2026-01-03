# Code Formatting Guide

This project uses automated code formatters to maintain consistent code style.

## Setup

### Install formatters:

**On Ubuntu/Debian:**
```bash
sudo apt install clang-format python3-autopep8
```

**On macOS:**
```bash
brew install clang-format
pip3 install autopep8
```

## Usage

### Automatic formatting (recommended):

Run the formatting script:
```bash
./format_code.sh
```

This will automatically format:
- C++ files (`*.cpp`, `*.hpp`) using clang-format
- Python files (`*.py`) using autopep8

### Manual formatting:

**Format a specific C++ file:**
```bash
clang-format -i --style=file src/tinymovr_system.cpp
```

**Format a specific Python file:**
```bash
autopep8 --in-place --max-line-length 100 launch/tinymovr_diffbot_demo.launch.py
```

### Pre-commit hook (optional):

To automatically format before each commit:

```bash
# Create pre-commit hook
cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash
./format_code.sh
git add -u
EOF

chmod +x .git/hooks/pre-commit
```

## CI Linting

The CI pipeline uses:
- **clang-format**: Checks C++ formatting (ROS 2 style, 100 char line limit)
- **flake8**: Checks Python style

External libraries (tinymovr protocol, socketcan_cpp) are excluded from linting.

## Style Rules

- **Line length**: 100 characters maximum
- **Indentation**: 2 spaces (no tabs)
- **Braces**: Required for all control statements
- **Style guide**: Based on Google C++ Style Guide with ROS 2 modifications

See `.clang-format` for complete configuration.
