cmake_minimum_required(VERSION 3.16)
project(tinymovr_ros)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(controller_manager REQUIRED)
find_package(controller_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)

# Tinymovr protocol source files
set(TINYMOVR_SOURCES
  src/tinymovr/can.cpp
  src/tinymovr/comms.cpp
  src/tinymovr/commutation_sensor.cpp
  src/tinymovr/controller.cpp
  src/tinymovr/current.cpp
  src/tinymovr/external_spi.cpp
  src/tinymovr/hall.cpp
  src/tinymovr/homing.cpp
  src/tinymovr/motor.cpp
  src/tinymovr/onboard.cpp
  src/tinymovr/position_sensor.cpp
  src/tinymovr/position.cpp
  src/tinymovr/scheduler.cpp
  src/tinymovr/select.cpp
  src/tinymovr/setup.cpp
  src/tinymovr/stall_detect.cpp
  src/tinymovr/tinymovr.cpp
  src/tinymovr/traj_planner.cpp
  src/tinymovr/user_frame.cpp
  src/tinymovr/velocity.cpp
  src/tinymovr/voltage.cpp
  src/tinymovr/watchdog.cpp
)

# Build the hardware interface library
add_library(${PROJECT_NAME}_joint_iface SHARED
  ${TINYMOVR_SOURCES}
  src/socketcan_cpp/socketcan_cpp.cpp
  src/tinymovr_system.cpp
)

target_include_directories(${PROJECT_NAME}_joint_iface PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/tinymovr>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(${PROJECT_NAME}_joint_iface
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
  sensor_msgs
)

# Export the plugin
pluginlib_export_plugin_description_file(hardware_interface tinymovr_ros.xml)

# Install targets
install(
  TARGETS ${PROJECT_NAME}_joint_iface
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install header files
install(
  DIRECTORY include/
  DESTINATION include
)

# Install launch files
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

# Install config files
install(
  DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

# Install URDF files
install(
  DIRECTORY urdf
  DESTINATION share/${PROJECT_NAME}
)

# Install plugin description file
install(
  FILES tinymovr_ros.xml
  DESTINATION share/${PROJECT_NAME}
)

# Testing
if(BUILD_TESTING)
  # Disable linters that can't properly exclude external code
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  set(ament_cmake_uncrustify_FOUND TRUE)
  set(ament_cmake_lint_cmake_FOUND TRUE)
  set(ament_cmake_xmllint_FOUND TRUE)

  # Only run flake8 on Python files (properly handles exclusions)
  find_package(ament_cmake_flake8 QUIET)
  if(ament_cmake_flake8_FOUND)
    ament_flake8()
  endif()

  # Note: Use ./format_code.sh to format code with clang-format
  # CI will check formatting when clang-format is properly integrated
endif()

# Export dependencies
ament_export_include_directories(
  include
)
ament_export_libraries(
  ${PROJECT_NAME}_joint_iface
)
ament_export_targets(
  export_${PROJECT_NAME}
)
ament_export_dependencies(
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
  sensor_msgs
)

ament_package()
