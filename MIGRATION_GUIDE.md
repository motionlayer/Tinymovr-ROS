# Migration Guide: Tinymovr 1.x → 2.x Configuration

This guide helps you migrate your existing robot configuration from the old ROS 1 Tinymovr driver to the new ROS 2 driver.

## Overview of Changes

**ROS 1 (old):**
- Hardware config: `config/hardware.yaml`
- Controller config: `config/diff_drive_config.yaml`

**ROS 2 (new):**
- Hardware config: `urdf/tinymovr_diffbot.urdf.xacro` (URDF format with ros2_control tags)
- Controller config: `config/diff_drive_config.yaml` (updated ROS 2 format)

---

## Step 1: Locate Your Old Configuration Files

From your old robot workspace, you need these two files:

```bash
# On your old robot (ROS 1 setup)
cd ~/catkin_ws/src/Tinymovr-ROS/config/

# Copy these files somewhere accessible:
# 1. hardware.yaml
# 2. diff_drive_config.yaml
```

---

## Step 2: Migrate Hardware Configuration

### What You Need from `hardware.yaml`:

For each joint (wheel), you need these parameters:

| Parameter | Description | Example |
|-----------|-------------|---------|
| `id` | CAN bus ID of the Tinymovr controller | `1` |
| `offset` | Position offset in radians | `3.14159265359` |
| `delay_us` | Communication delay in microseconds | `200` |
| `rads_to_ticks` | Encoder ticks per radian conversion | `14.323944878` |
| `command_interface` | Control mode (velocity, position, or effort) | `velocity` |

### Where to Put It in ROS 2:

Open `urdf/tinymovr_diffbot.urdf.xacro` and update each `<joint>` section:

**Example from your old `hardware.yaml`:**
```yaml
wheel_1:
  id: 1
  offset: 3.14159265359
  delay_us: 200
  rads_to_ticks: 14.323944878
  command_interface: velocity
```

**Maps to this in `urdf/tinymovr_diffbot.urdf.xacro`:**
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
  <param name="offset">3.14159265359</param>
</joint>
```

### ⚠️ Important: Calculate `rads_to_ticks`

This depends on your motor encoder resolution and gear ratio:

```python
# Formula
rads_to_ticks = (encoder_ticks_per_revolution * gear_ratio) / (2 * π)

# Example: 8192 ticks/rev encoder, 7.2:1 gear ratio
rads_to_ticks = (8192 * 7.2) / (2 * 3.14159265359) = 9363.2 ticks/rad
```

**Common configurations:**
- **Direct drive, 8192 CPR encoder**: `1303.8` ticks/rad
- **7:1 gearbox, 8192 CPR encoder**: `9126.6` ticks/rad
- **10:1 gearbox, 8192 CPR encoder**: `13038` ticks/rad

---

## Step 3: Migrate Controller Configuration

### What You Need from `diff_drive_config.yaml`:

| Parameter | Description | Example |
|-----------|-------------|---------|
| `wheel_separation` | Distance between left/right wheels (meters) | `0.4` |
| `wheel_radius` | Radius of wheels (meters) | `0.12` |
| `publish_rate` | Odometry publish rate (Hz) | `50.0` |
| `pose_covariance_diagonal` | Odometry pose uncertainty | `[0.001, 0.001, ...]` |
| `twist_covariance_diagonal` | Odometry velocity uncertainty | `[0.001, 0.001, ...]` |

### Where to Put It in ROS 2:

Open `config/diff_drive_config.yaml` and update the `diff_drive_controller` section:

**Old ROS 1 format:**
```yaml
diff_drive_controller:
  type: "diff_drive_controller/DiffDriveController"
  left_wheel: "wheel_1"
  right_wheel: "wheel_2"
  wheel_separation: 0.4
  wheel_radius: 0.12
  publish_rate: 50.0
```

**New ROS 2 format:**
```yaml
diff_drive_controller:
  ros__parameters:
    left_wheel_names: ["wheel_1"]      # Changed: now array
    right_wheel_names: ["wheel_2"]     # Changed: now array
    wheel_separation: 0.4              # Same
    wheel_radius: 0.12                 # Same
    publish_rate: 50.0                 # Same
    pose_covariance_diagonal: [0.001, 0.001, 1000000.0, 1000000.0, 1000000.0, 1000.0]
    twist_covariance_diagonal: [0.001, 0.001, 1000000.0, 1000000.0, 1000000.0, 1000.0]
```

**Key changes:**
- Add `ros__parameters:` wrapper
- `left_wheel` → `left_wheel_names` (now an array)
- `right_wheel` → `right_wheel_names` (now an array)

---

## Step 4: Physical Measurements

You'll need to measure/confirm these on your robot:

### 1. Wheel Separation
```
         ↑
         |
    [Left Wheel]  ←--- wheel_separation --->  [Right Wheel]
         |
         ↓
```

Measure center-to-center distance between left and right wheels (in meters).

**How to verify:**
```bash
# Drive forward 1 meter, wheels should travel same distance
ros2 topic pub /diff_drive_controller/cmd_vel_unstamped geometry_msgs/msg/Twist "{linear: {x: 0.2}}"

# Rotate 360°, measure actual rotation - adjust wheel_separation if off
ros2 topic pub /diff_drive_controller/cmd_vel_unstamped geometry_msgs/msg/Twist "{angular: {z: 1.0}}"
```

### 2. Wheel Radius
```
    ___
   /   \
  |  •  |  ← Center
   \___/
     ↕
   radius
```

Measure from wheel center to ground contact point (in meters).

**How to verify:**
```python
# Mark wheel, count rotations over a known distance
# radius = distance / (rotations * 2 * π)

# Example: 10 rotations = 7.54 meters
radius = 7.54 / (10 * 2 * 3.14159) = 0.12 meters
```

### 3. Motor Position Offset

Each motor may have a different zero position. The offset compensates for this.

**How to find offset:**
1. Home your robot to a known position (e.g., wheels aligned)
2. Read encoder positions via Tinymovr Studio
3. Calculate offset to make positions match expected values

**Common values:**
- `0.0` - No offset needed
- `3.14159265359` (π) - 180° offset
- `-1.5708` (-π/2) - 90° counter-clockwise offset

---

## Step 5: Configuration Files Template

### Create Your Custom Hardware URDF

Copy and modify `urdf/tinymovr_diffbot.urdf.xacro`:

```bash
cd ~/ros2_ws/src/tinymovr_ros/urdf/
cp tinymovr_diffbot.urdf.xacro my_robot.urdf.xacro
```

Edit `my_robot.urdf.xacro` with YOUR values:

```xml
<?xml version="1.0"?>
<robot xmlns:xacro="http://www.ros.org/wiki/xacro" name="my_robot">

  <ros2_control name="tinymovr_system" type="system">
    <hardware>
      <plugin>tinymovr_ros/TinymovrSystem</plugin>
      <param name="can_interface">can0</param>
    </hardware>

    <!-- LEFT WHEEL - Update these values! -->
    <joint name="wheel_left">
      <command_interface name="velocity"/>
      <state_interface name="position"/>
      <state_interface name="velocity"/>
      <state_interface name="effort"/>
      <param name="id">1</param>                    <!-- YOUR CAN ID -->
      <param name="delay_us">200</param>             <!-- YOUR delay -->
      <param name="rads_to_ticks">14.323944878</param> <!-- YOUR conversion -->
      <param name="command_interface">velocity</param>
      <param name="offset">3.14159265359</param>     <!-- YOUR offset -->
    </joint>

    <!-- RIGHT WHEEL - Update these values! -->
    <joint name="wheel_right">
      <command_interface name="velocity"/>
      <state_interface name="position"/>
      <state_interface name="velocity"/>
      <state_interface name="effort"/>
      <param name="id">2</param>                    <!-- YOUR CAN ID -->
      <param name="delay_us">200</param>             <!-- YOUR delay -->
      <param name="rads_to_ticks">14.323944878</param> <!-- YOUR conversion -->
      <param name="command_interface">velocity</param>
      <param name="offset">3.14159265359</param>     <!-- YOUR offset -->
    </joint>
  </ros2_control>

</robot>
```

### Create Your Custom Controller Config

Copy and modify `config/diff_drive_config.yaml`:

```bash
cd ~/ros2_ws/src/tinymovr_ros/config/
cp diff_drive_config.yaml my_robot_config.yaml
```

Edit `my_robot_config.yaml` with YOUR values:

```yaml
controller_manager:
  ros__parameters:
    update_rate: 100  # Hz - keep at 100

    joint_state_broadcaster:
      type: joint_state_broadcaster/JointStateBroadcaster

    diff_drive_controller:
      type: diff_drive_controller/DiffDriveController

joint_state_broadcaster:
  ros__parameters: {}

diff_drive_controller:
  ros__parameters:
    left_wheel_names: ["wheel_left"]           # Match your URDF joint names!
    right_wheel_names: ["wheel_right"]         # Match your URDF joint names!

    wheel_separation: 0.4                      # YOUR measurement (meters)
    wheel_radius: 0.12                         # YOUR measurement (meters)

    wheel_separation_multiplier: 1.0           # Fine-tune if needed
    left_wheel_radius_multiplier: 1.0          # Fine-tune if needed
    right_wheel_radius_multiplier: 1.0         # Fine-tune if needed

    publish_rate: 50.0                         # Odometry publish rate (Hz)
    odom_frame_id: odom
    base_frame_id: base_link

    # YOUR covariance values (from old config)
    pose_covariance_diagonal: [0.001, 0.001, 1000000.0, 1000000.0, 1000000.0, 1000.0]
    twist_covariance_diagonal: [0.001, 0.001, 1000000.0, 1000000.0, 1000000.0, 1000.0]

    open_loop: false
    enable_odom_tf: true
    cmd_vel_timeout: 0.5
    use_stamped_vel: false
    velocity_rolling_window_size: 10
    position_feedback: false
```

### Create Your Custom Launch File

Copy and modify `launch/tinymovr_diffbot_demo.launch.py`:

```bash
cd ~/ros2_ws/src/tinymovr_ros/launch/
cp tinymovr_diffbot_demo.launch.py my_robot.launch.py
```

Edit line 29 and 35 to use your custom files:

```python
# Line 29 - Update URDF path
PathJoinSubstitution(
    [FindPackageShare("tinymovr_ros"), "urdf", "my_robot.urdf.xacro"]  # YOUR file
),

# Line 35 - Update config path
robot_controllers = PathJoinSubstitution(
    [FindPackageShare("tinymovr_ros"), "config", "my_robot_config.yaml"]  # YOUR file
)
```

---

## Step 6: Quick Reference - Parameter Mapping

| Old (ROS 1) | New (ROS 2) | Location |
|-------------|-------------|----------|
| `hardware.yaml` → `joints` → `wheel_X` → `id` | `<param name="id">` | URDF |
| `hardware.yaml` → `joints` → `wheel_X` → `offset` | `<param name="offset">` | URDF |
| `hardware.yaml` → `joints` → `wheel_X` → `delay_us` | `<param name="delay_us">` | URDF |
| `hardware.yaml` → `joints` → `wheel_X` → `rads_to_ticks` | `<param name="rads_to_ticks">` | URDF |
| `hardware.yaml` → `joints` → `wheel_X` → `command_interface` | `<param name="command_interface">` | URDF |
| `diff_drive_config.yaml` → `left_wheel` | `left_wheel_names: ["..."]` | YAML |
| `diff_drive_config.yaml` → `right_wheel` | `right_wheel_names: ["..."]` | YAML |
| `diff_drive_config.yaml` → `wheel_separation` | `wheel_separation:` | YAML |
| `diff_drive_config.yaml` → `wheel_radius` | `wheel_radius:` | YAML |
| `diff_drive_config.yaml` → `publish_rate` | `publish_rate:` | YAML |

---

## Step 7: Testing Your Configuration

### 1. Build and Source
```bash
cd ~/ros2_ws
colcon build --packages-select tinymovr_ros
source install/setup.bash
```

### 2. Check Configuration Syntax
```bash
# Validate URDF
xacro urdf/my_robot.urdf.xacro > /tmp/test.urdf
check_urdf /tmp/test.urdf

# Check for syntax errors
colcon test --packages-select tinymovr_ros --event-handlers console_direct+
```

### 3. Bring Up Hardware
```bash
# Setup CAN interface
sudo ip link set can0 type can bitrate 1000000
sudo ip link set up can0

# Launch your robot
ros2 launch tinymovr_ros my_robot.launch.py
```

### 4. Verify Joint States
```bash
# In another terminal
ros2 topic echo /joint_states

# You should see position, velocity, effort for both wheels
```

### 5. Test Movement
```bash
# Slow forward movement
ros2 topic pub /diff_drive_controller/cmd_vel_unstamped geometry_msgs/msg/Twist "{linear: {x: 0.1}}"

# Slow rotation
ros2 topic pub /diff_drive_controller/cmd_vel_unstamped geometry_msgs/msg/Twist "{angular: {z: 0.5}}"

# Stop
ros2 topic pub /diff_drive_controller/cmd_vel_unstamped geometry_msgs/msg/Twist "{}"
```

### 6. Check Odometry
```bash
ros2 topic echo /diff_drive_controller/odom

# Drive forward 1 meter, check if odometry matches
```

---

## Common Issues and Solutions

### Issue: "Protocol hash mismatch"
**Cause:** Tinymovr firmware version incompatible with driver
**Solution:**
- Check firmware version: Tinymovr Studio → About
- This driver supports firmware 1.6.x and 2.x
- Update firmware if needed

### Issue: "Joint not calibrated"
**Cause:** Motor not calibrated in Tinymovr Studio
**Solution:**
```bash
# Calibrate using Tinymovr Studio or CLI
tinymovr --bus can0 --id 1 calibrate
tinymovr --bus can0 --id 2 calibrate
```

### Issue: Wheels move in wrong direction
**Solution:** Add π (3.14159...) to the offset parameter

### Issue: Odometry drifts
**Solutions:**
1. Verify `wheel_separation` measurement
2. Verify `wheel_radius` measurement
3. Use wheel radius multipliers for fine-tuning
4. Check for wheel slip

### Issue: Robot rotates too much/little
**Solution:** Adjust `wheel_separation` parameter:
- Robot rotates too much → decrease `wheel_separation`
- Robot rotates too little → increase `wheel_separation`

---

## Checklist

- [ ] Copy `hardware.yaml` from old robot
- [ ] Copy `diff_drive_config.yaml` from old robot
- [ ] Extract joint parameters (id, offset, delay_us, rads_to_ticks)
- [ ] Create custom URDF with your parameters
- [ ] Create custom controller config with your parameters
- [ ] Measure wheel separation
- [ ] Measure wheel radius
- [ ] Create custom launch file
- [ ] Build workspace
- [ ] Test with CAN interface up
- [ ] Verify joint states publishing
- [ ] Test movement commands
- [ ] Verify odometry accuracy
- [ ] Fine-tune multipliers if needed

---

## Need Help?

- **Documentation**: See [README.md](README.md) for general usage
- **Formatting**: See [FORMATTING.md](FORMATTING.md) for code style
- **Issues**: https://github.com/tinymovr/Tinymovr-ROS/issues
- **Tinymovr Docs**: https://tinymovr.com/
