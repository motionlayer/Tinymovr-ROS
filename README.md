__Tinymovr ROS 2 Hardware Interface__

![ROS2](https://img.shields.io/badge/ROS2-Humble%20|%20Jazzy-blue)
![ROS1](https://img.shields.io/badge/ROS1-Noetic-inactive)
[![CI](https://github.com/tinymovr/Tinymovr-ROS/actions/workflows/industrial_ci.yaml/badge.svg)](https://github.com/tinymovr/Tinymovr-ROS/actions)

> [!IMPORTANT]
> **This branch (`main`) is for ROS 2** (Humble on Ubuntu 22.04 or Jazzy on Ubuntu 24.04)
>
> **For ROS 1 Noetic**, see the [`ros1-noetic`](https://github.com/tinymovr/Tinymovr-ROS/tree/ros1-noetic) branch (legacy support)
>
> _Note: CI currently tests with ROS 2 Humble due to GitHub Actions runner availability_

---

A ROS 2 package that provides hardware interfacing for the [Tinymovr](https://tinymovr.com) motor controller. This interface allows for seamless integration of Tinymovr devices with ROS 2-based robotic systems using the ros2_control framework.

## Features
- Real-time reading of joint positions, velocities, and efforts
- Ability to send joint command setpoints for position, velocity, and effort control
- Full lifecycle management with ros2_control SystemInterface
- Error handling and robust exception management
- Compatible with standard ROS 2 controllers, enabling a plug-and-play experience
- Integration with diff_drive_controller for differential drive robots

## Prerequisites

- **ROS 2 Humble** (Ubuntu 22.04) or **ROS 2 Jazzy** (Ubuntu 24.04)
- **SocketCAN** tools and utilities installed
- **Tinymovr** devices with firmware 1.6.x or 2.x
- Devices properly set up and calibrated

### Required ROS 2 Packages

**For ROS 2 Humble (Ubuntu 22.04):**
```bash
sudo apt install ros-humble-ros2-control ros-humble-ros2-controllers \
  ros-humble-xacro ros-humble-robot-state-publisher
```

**For ROS 2 Jazzy (Ubuntu 24.04):**
```bash
sudo apt install ros-jazzy-ros2-control ros-jazzy-ros2-controllers \
  ros-jazzy-xacro ros-jazzy-robot-state-publisher
```

> [!NOTE]
> If you plan to use the CANine adapter, you need to flash it with the Candlelight firmware, which is compatible with SocketCAN. Use [this web-based flasher](https://canable.io/updater/canable1.html) for easy upgrade. Use Chrome and choose the Candlelight firmware from the drop-down list.

## Installation

1. Create a ROS 2 workspace (if you don't have one):

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
```

2. Clone the repository:

```bash
git clone git@github.com:tinymovr/Tinymovr-ROS.git tinymovr_ros
```

3. Build your workspace:

```bash
cd ~/ros2_ws
colcon build --packages-select tinymovr_ros
```

4. Source the workspace:

```bash
source install/setup.bash
```

## Bring up SocketCAN

Depending on your device you may need to add the correct module to the kernel. Following that, bring up the interface as follows:

```bash
sudo ip link set can0 type can bitrate 1000000
sudo ip link set up can0
```

## Run the Diffbot Demo!

1. Ensure your Tinymovr instances are calibrated and well tuned. Test functioning using Tinymovr Studio or CLI.

2. Configure your hardware in `urdf/tinymovr_diffbot.urdf.xacro` and diff drive config in `config/diff_drive_config.yaml`

3. Start the hardware interface and controllers:

```bash
ros2 launch tinymovr_ros tinymovr_diffbot_demo.launch.py
```

4. Spin up a keyboard teleop and drive your robot:

```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args --remap cmd_vel:=/diff_drive_controller/cmd_vel_unstamped
```

## Configuration

The Tinymovr ROS 2 interface uses the ros2_control framework:

### Hardware Configuration
Hardware parameters are defined in `urdf/tinymovr_diffbot.urdf.xacro` using ros2_control tags. Each joint specifies:
- `id`: CAN bus ID of the Tinymovr controller
- `delay_us`: Communication delay in microseconds
- `rads_to_ticks`: Conversion factor from radians to encoder ticks
- `command_interface`: Control mode (position, velocity, or effort)
- `offset`: Position offset in radians

### Controller Configuration
Controller parameters are defined in `config/diff_drive_config.yaml`:
- Wheel separation and radius
- Odometry parameters
- Control loop update rate
- Covariance matrices

## Architecture

This package implements a ros2_control `SystemInterface` that:
- Manages lifecycle states (configure, activate, deactivate, cleanup, shutdown)
- Exports position, velocity, and effort state interfaces
- Exports position, velocity, and effort command interfaces
- Communicates with Tinymovr controllers via SocketCAN
- Integrates with standard ROS 2 controllers (diff_drive_controller, joint_state_broadcaster, etc.)

## Monitoring and Control

Check controller status:
```bash
ros2 control list_controllers
ros2 control list_hardware_interfaces
```

View joint states:
```bash
ros2 topic echo /joint_states
```

View odometry:
```bash
ros2 topic echo /diff_drive_controller/odom
```

Send velocity commands directly:
```bash
ros2 topic pub /diff_drive_controller/cmd_vel_unstamped geometry_msgs/msg/Twist "{linear: {x: 0.1}, angular: {z: 0.0}}"
```

## API Documentation

Further details about the API and individual functions can be found in the code documentation. Please refer to the header files for advanced use cases.

## Contributing

Contributions to improve and expand the functionality of Tinymovr ROS 2 are welcome! Please open an issue or submit a pull request on the GitHub repository.

## External Links

[ROS Wiki Page](http://wiki.ros.org/Robots/tinymovr)

## License

This package is licensed under the [Apache 2.0 License](LICENSE).
