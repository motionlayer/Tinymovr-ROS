# Your Custom Robot Configuration

These files were automatically converted from your ROS 1 configuration for teleop use.

## Files Created

1. **`urdf/my_robot.urdf.xacro`** - Your hardware configuration
   - CAN IDs: wheel_1=1, wheel_2=2
   - Encoder conversion: 14.323944878 ticks/rad
   - Offsets: Set to 0.0 for teleop (you can adjust if needed)

2. **`config/my_robot_config.yaml`** - Your controller configuration
   - Wheel separation: 0.4 m
   - Wheel radius: 0.12 m
   - Publish rate: 50 Hz

3. **`launch/my_robot.launch.py`** - Launch file for your robot

## Quick Start

### 1. Build the package
```bash
cd ~/ros2_ws
colcon build --packages-select tinymovr_ros
source install/setup.bash
```

### 2. Bring up CAN interface
```bash
sudo ip link set can0 type can bitrate 1000000
sudo ip link set up can0
```

### 3. Launch your robot
```bash
ros2 launch tinymovr_ros my_robot.launch.py
```

### 4. Drive with keyboard
In another terminal:
```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard \
  --ros-args --remap cmd_vel:=/cmd_vel
```

**Controls:**
- `i` - Move forward
- `k` - Stop
- `,` - Move backward
- `j` - Turn left
- `l` - Turn right
- `q/z` - Increase/decrease max speeds

## Verify Everything Works

### Check joint states
```bash
ros2 topic echo /joint_states
```
You should see positions and velocities for wheel_1 and wheel_2.

### Check controllers
```bash
ros2 control list_controllers
```
Should show:
- `joint_state_broadcaster` [active]
- `diff_drive_controller` [active]

### Test movement
```bash
# Slow forward
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.1}}"

# Stop
ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{}"
```

## Adjustments

### If robot moves wrong direction
Edit `urdf/my_robot.urdf.xacro` and change offset:
```xml
<param name="offset">3.14159265359</param>  <!-- Add π for 180° flip -->
```

### If robot turns too much/little
Edit `config/my_robot_config.yaml` and adjust:
```yaml
wheel_separation: 0.4  # Increase to turn less, decrease to turn more
```

### If robot moves too fast/slow
Edit `config/my_robot_config.yaml` and adjust:
```yaml
wheel_radius: 0.12  # Increase for faster, decrease for slower
```

## Configuration Source

**Converted from your ROS 1 config:**
- Hardware: 2 wheels (IDs 1 & 2) with velocity control
- Encoder resolution: 14.323944878 ticks/rad
- Original offset: 3.14159265359 rad (set to 0.0 for teleop simplicity)
- Wheel dimensions: 0.4m separation, 0.12m radius

## Need Help?

- **Documentation**: See [MIGRATION_GUIDE.md](MIGRATION_GUIDE.md) for detailed info
- **Issues**: https://github.com/tinymovr/Tinymovr-ROS/issues
