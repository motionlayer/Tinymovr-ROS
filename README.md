# Tinymovr ROS 2 Hardware Interface

![ROS2](https://img.shields.io/badge/ROS2-Humble%20|%20Jazzy-blue)
![ROS1](https://img.shields.io/badge/ROS1-Noetic-inactive)
[![CI](https://github.com/tinymovr/Tinymovr-ROS/actions/workflows/industrial_ci.yaml/badge.svg)](https://github.com/tinymovr/Tinymovr-ROS/actions)

> [!IMPORTANT]
> **This branch (`main`) is for ROS 2** (Humble on Ubuntu 22.04 or Jazzy on Ubuntu 24.04)
>
> **For ROS 1 Noetic**, see the [`ros1-noetic`](https://github.com/tinymovr/Tinymovr-ROS/tree/ros1-noetic) branch (legacy support)
>
> **Migrating from ROS 1?** See [MIGRATION_GUIDE.md](MIGRATION_GUIDE.md)

---

A ROS 2 package that provides hardware interfacing for the [Tinymovr](https://tinymovr.com) motor controller. This interface allows for seamless integration of Tinymovr devices with ROS 2-based robotic systems using the ros2_control framework.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
  - [Ubuntu 22.04/24.04](#ubuntu-22042404)
  - [Raspberry Pi OS / Debian](#raspberry-pi-os--debian)
- [Quick Start](#quick-start)
- [Configuration](#configuration)
- [Monitoring and Control](#monitoring-and-control)
- [Documentation](#documentation)

## Features
- Real-time reading of joint positions, velocities, and efforts
- Ability to send joint command setpoints for position, velocity, and effort control
- Full lifecycle management with ros2_control SystemInterface
- Error handling and robust exception management
- Compatible with standard ROS 2 controllers, enabling a plug-and-play experience
- Integration with diff_drive_controller for differential drive robots

## Prerequisites

- **Tinymovr** devices with firmware 1.6.x or 2.x (properly calibrated)
- **SocketCAN** tools and utilities
- **ROS 2 Humble** (Ubuntu 22.04, Raspberry Pi/Debian) or **Jazzy** (Ubuntu 24.04)

> [!NOTE]
> If you plan to use the CANine adapter, flash it with Candlelight firmware for SocketCAN compatibility using [this web-based flasher](https://canable.io/updater/canable1.html) (use Chrome, choose Candlelight firmware).

---

## Installation

### Ubuntu 22.04/24.04

#### 1. Install ROS 2 and Dependencies

**For Humble (Ubuntu 22.04):**
```bash
sudo apt update
sudo apt install -y \
  ros-humble-ros-base \
  ros-humble-ros2-control \
  ros-humble-ros2-controllers \
  ros-humble-xacro \
  ros-humble-robot-state-publisher \
  ros-humble-teleop-twist-keyboard
```

**For Jazzy (Ubuntu 24.04):**
```bash
sudo apt update
sudo apt install -y \
  ros-jazzy-ros-base \
  ros-jazzy-ros2-control \
  ros-jazzy-ros2-controllers \
  ros-jazzy-xacro \
  ros-jazzy-robot-state-publisher \
  ros-jazzy-teleop-twist-keyboard
```

#### 2. Build Workspace

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
git clone https://github.com/tinymovr/Tinymovr-ROS.git tinymovr_ros
cd ~/ros2_ws
colcon build --packages-select tinymovr_ros
source install/setup.bash
```

---

### Raspberry Pi OS / Debian

Debian Trixie (testing) and Raspberry Pi OS have newer system libraries that conflict with Ubuntu 22.04 ROS packages. The **official ROS 2 recommendation** is to use Docker ([source](https://docs.ros.org/en/foxy/How-To-Guides/Installing-on-Raspberry-Pi.html)).

#### 1. Install Docker (one-time setup)

```bash
# Install Docker
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh

# Add your user to docker group
sudo usermod -aG docker $USER
newgrp docker  # Or logout/login

# Install docker-compose
sudo apt install -y docker-compose
```

#### 2. Start ROS 2 Container

```bash
cd ~/Tinymovr-ROS  # Or wherever you cloned the repo
./docker_run.sh
```

This starts a persistent container named `tinymovr_ros2` with Ubuntu + ROS 2 Humble.

#### 3. Enter Container and Build

```bash
# Enter the container
docker exec -it tinymovr_ros2 bash

# Inside container: Install dependencies
apt update && apt install -y \
  python3-pip \
  python3-colcon-common-extensions \
  iproute2 \
  ros-humble-ament-package \
  ros-humble-rosidl-typesupport-c \
  ros-humble-rosidl-typesupport-cpp \
  ros-humble-rosidl-default-generators \
  ros-humble-ros2-control \
  ros-humble-ros2-controllers \
  ros-humble-xacro \
  ros-humble-robot-state-publisher \
  ros-humble-teleop-twist-keyboard

# Build your robot package
cd /workspace
source /opt/ros/humble/setup.bash
colcon build --packages-select tinymovr_ros
source install/setup.bash
```

**Optional: Add shortcuts to your `~/.bashrc` on Raspberry Pi:**
```bash
alias ros2_shell='docker exec -it tinymovr_ros2 bash -c "cd /workspace && source /opt/ros/humble/setup.bash && source install/setup.bash && exec bash"'
```

Then just run `ros2_shell` to enter ROS 2 environment.

**Docker Container Management:**
```bash
docker-compose stop      # Stop container
docker-compose up -d     # Start container
docker-compose restart   # Restart container
docker logs tinymovr_ros2  # View logs
```

---

## Quick Start

### 1. Bring up SocketCAN

```bash
sudo ip link set can0 type can bitrate 1000000
sudo ip link set up can0
```

*If using Docker, run this inside the container.*

### 2. Configure Your Robot

This package includes two example configurations:

#### Demo Robot (`tinymovr_diffbot_demo.launch.py`)
Generic 2-wheel differential drive configuration. Modify these files:
- **Hardware**: `urdf/tinymovr_diffbot.urdf.xacro` - CAN IDs, encoder conversion, offsets
- **Controller**: `config/diff_drive_config.yaml` - Wheel separation, radius, rates

#### Your Custom Robot (`my_robot.launch.py`)
A pre-configured example converted from ROS 1 hardware.yaml format:
- **Hardware**: `urdf/my_robot.urdf.xacro` - CAN IDs 1&2, offset=0.0 for teleop
- **Controller**: `config/my_robot_config.yaml` - 0.4m separation, 0.12m radius

### 3. Launch Your Robot

**Demo robot:**
```bash
ros2 launch tinymovr_ros tinymovr_diffbot_demo.launch.py
```

**Your custom robot:**
```bash
ros2 launch tinymovr_ros my_robot.launch.py
```

### 4. Drive with Keyboard

In another terminal:
```bash
source ~/ros2_ws/install/setup.bash  # Or ros2_shell if using Docker
ros2 run teleop_twist_keyboard teleop_twist_keyboard \
  --ros-args --remap cmd_vel:=/cmd_vel
```

**Controls:**
- `i` - Forward
- `k` - Stop
- `,` - Backward
- `j` - Turn left
- `l` - Turn right
- `q`/`z` - Increase/decrease speeds

---

## Configuration

The Tinymovr ROS 2 interface uses the ros2_control framework:

### Hardware Configuration (URDF)

Hardware parameters are defined in `urdf/*.urdf.xacro` using ros2_control tags. Each joint specifies:

| Parameter | Description | Example |
|-----------|-------------|---------|
| `id` | CAN bus ID of Tinymovr controller | `1` |
| `delay_us` | Communication delay in microseconds | `200` |
| `rads_to_ticks` | Encoder ticks per radian conversion | `14.323944878` |
| `command_interface` | Control mode (velocity, position, or effort) | `velocity` |
| `offset` | Position offset in radians | `0.0` or `3.14159265359` |

**Example joint configuration:**
```xml
<joint name="wheel_1">
  <command_interface name="velocity"/>
  <state_interface name="position"/>
  <state_interface name="velocity"/>
  <state_interface name="effort"/>
  <param name="id">1</param>
  <param name="delay_us">200</param>
  <param name="rads_to_ticks">14.323944878</param>
  <param name="command_interface">velocity</param>
  <param name="offset">0.0</param>
</joint>
```

### Controller Configuration (YAML)

Controller parameters are defined in `config/*.yaml`:

```yaml
diff_drive_controller:
  ros__parameters:
    left_wheel_names: ["wheel_1"]
    right_wheel_names: ["wheel_2"]
    wheel_separation: 0.4  # meters
    wheel_radius: 0.12     # meters
    publish_rate: 50.0     # Hz
```

### Adjustments

**If robot moves wrong direction:**
Edit URDF and add π to offset:
```xml
<param name="offset">3.14159265359</param>  <!-- 180° flip -->
```

**If robot turns too much/little:**
Edit YAML config:
```yaml
wheel_separation: 0.4  # Increase to turn less, decrease to turn more
```

**If robot moves too fast/slow:**
Edit YAML config:
```yaml
wheel_radius: 0.12  # Increase for faster, decrease for slower
```

---

## Monitoring and Control

**Check controller status:**
```bash
ros2 control list_controllers
ros2 control list_hardware_interfaces
```

**View joint states:**
```bash
ros2 topic echo /joint_states
```

**View odometry:**
```bash
ros2 topic echo /diff_drive_controller/odom
```

**Send velocity commands:**
```bash
# Move forward slowly
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.1}}"

# Rotate in place
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{angular: {z: 0.5}}"

# Stop
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{}"
```

---

## Architecture

This package implements a ros2_control `SystemInterface` that:
- Manages lifecycle states (configure, activate, deactivate, cleanup, shutdown)
- Exports position, velocity, and effort state interfaces
- Exports position, velocity, and effort command interfaces
- Communicates with Tinymovr controllers via SocketCAN
- Integrates with standard ROS 2 controllers (diff_drive_controller, joint_state_broadcaster, etc.)

**Key components:**
- **Hardware Interface**: `tinymovr_system.cpp` - SystemInterface implementation
- **Plugin Description**: `tinymovr_ros.xml` - Pluginlib registration
- **Launch Files**: `launch/*.launch.py` - Python launch configurations
- **URDF**: `urdf/*.urdf.xacro` - Hardware descriptions with ros2_control tags

---

## Documentation

- **[MIGRATION_GUIDE.md](MIGRATION_GUIDE.md)** - Complete guide for migrating from ROS 1 to ROS 2
  - Parameter mapping (hardware.yaml → URDF)
  - Controller config updates
  - Physical measurements and calibration
  - Troubleshooting

- **[FORMATTING.md](FORMATTING.md)** - Code style guide for contributors
  - Formatting standards
  - Linting setup
  - Pre-commit hooks

- **API Documentation** - See header files for detailed API reference

---

## Contributing

Contributions are welcome! Please:
1. Read [FORMATTING.md](FORMATTING.md) for code style
2. Test changes with `colcon test`
3. Run formatters: `./format_code.sh`
4. Open an issue or submit a pull request

---

## External Links

- [ROS Wiki Page](http://wiki.ros.org/Robots/tinymovr)
- [Tinymovr Documentation](https://tinymovr.com)
- [ROS 2 Raspberry Pi Setup](https://docs.ros.org/en/foxy/How-To-Guides/Installing-on-Raspberry-Pi.html)

---

## License

This package is licensed under the [Apache 2.0 License](LICENSE).
