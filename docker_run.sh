#!/bin/bash
# Helper script to run Tinymovr ROS 2 in Docker

set -e

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo "Docker is not installed. Install with:"
    echo "  curl -fsSL https://get.docker.com -o get-docker.sh"
    echo "  sudo sh get-docker.sh"
    echo "  sudo usermod -aG docker $USER"
    exit 1
fi

# Check if docker compose is available (new) or docker-compose (old)
if docker compose version &> /dev/null; then
    COMPOSE_CMD="docker compose"
elif command -v docker-compose &> /dev/null; then
    COMPOSE_CMD="docker-compose"
else
    echo "Docker Compose is not available."
    echo "It should have been installed with Docker."
    echo "Try: docker compose version"
    exit 1
fi

echo "Starting ROS 2 Humble container..."
$COMPOSE_CMD up -d

echo ""
echo "Container started. To enter the container:"
echo "  docker exec -it tinymovr_ros2 bash"
echo ""
echo "Once inside, build and run your robot:"
echo "  apt update && apt install -y ros-humble-ros2-control ros-humble-ros2-controllers ros-humble-xacro ros-humble-robot-state-publisher ros-humble-teleop-twist-keyboard"
echo "  cd /workspace"
echo "  source /opt/ros/humble/setup.bash"
echo "  colcon build --packages-select tinymovr_ros"
echo "  source install/setup.bash"
echo "  # Set up CAN (from inside container)"
echo "  ip link set can0 type can bitrate 1000000"
echo "  ip link set up can0"
echo "  # Launch"
echo "  ros2 launch tinymovr_ros my_robot.launch.py"
