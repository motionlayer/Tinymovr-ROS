#include "tinymovr_ros/tinymovr_system.hpp"

#include <chrono>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/rclcpp.hpp"
#include "socketcan_cpp/socketcan_cpp.hpp"

namespace tinymovr_ros
{

// Global SocketCAN instance
static scpp::SocketCan socket_can;

// Helper function to convert SocketCAN error to string
const char* SocketCanErrorToString(scpp::SocketCanStatus status) {
    switch (status) {
        case scpp::STATUS_OK:
            return "No error";
        case scpp::STATUS_SOCKET_CREATE_ERROR:
            return "SocketCAN socket creation error";
        case scpp::STATUS_INTERFACE_NAME_TO_IDX_ERROR:
            return "SocketCAN interface name to index error";
        case scpp::STATUS_MTU_ERROR:
            return "SocketCAN maximum transfer unit error";
        case scpp::STATUS_CANFD_NOT_SUPPORTED:
            return "SocketCAN flexible data-rate not supported on this interface";
        case scpp::STATUS_ENABLE_FD_SUPPORT_ERROR:
            return "Error enabling SocketCAN flexible-data-rate support";
        case scpp::STATUS_WRITE_ERROR:
            return "SocketCAN write error";
        case scpp::STATUS_READ_ERROR:
            return "SocketCAN read error";
        case scpp::STATUS_BIND_ERROR:
            return "SocketCAN bind error";
        default:
            return "Unknown SocketCAN error";
    }
}

// CAN send callback
void send_cb(uint32_t arbitration_id, uint8_t *data, uint8_t data_length, bool rtr)
{
    RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"),
                 "Attempting to write CAN frame with arbitration_id: %u", arbitration_id);

    scpp::CanFrame cf_to_write;
    cf_to_write.id = arbitration_id;
    if (rtr) {
        cf_to_write.id |= CAN_RTR_FLAG;
    }
    cf_to_write.len = data_length;
    for (int i = 0; i < data_length; ++i)
        cf_to_write.data[i] = data[i];

    auto write_status = socket_can.write(cf_to_write);
    if (write_status != scpp::STATUS_OK)
    {
        throw std::runtime_error(SocketCanErrorToString(write_status));
    }
    else
    {
        RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"),
                     "CAN frame with arbitration_id: %u written successfully.", arbitration_id);
    }
}

// CAN receive callback
bool recv_cb(uint32_t *arbitration_id, uint8_t *data, uint8_t *data_length)
{
    RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"), "Attempting to read CAN frame...");

    scpp::CanFrame fr;
    scpp::SocketCanStatus read_status = socket_can.read(fr);
    if (read_status == scpp::STATUS_OK)
    {
        *arbitration_id = fr.id & CAN_EFF_MASK;
        *data_length = fr.len;
        std::copy(fr.data, fr.data + fr.len, data);
        RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"),
                     "CAN frame with arbitration_id: %u read successfully.", *arbitration_id);
        return true;
    }
    else
    {
        throw std::runtime_error(SocketCanErrorToString(read_status));
        return false;
    }
}

// Delay callback
void delay_us_cb(uint32_t us)
{
    rclcpp::sleep_for(std::chrono::microseconds(us));
}

CallbackReturn TinymovrSystem::on_init(const hardware_interface::HardwareInfo & info)
{
  if (hardware_interface::SystemInterface::on_init(info) != CallbackReturn::SUCCESS)
  {
    return CallbackReturn::ERROR;
  }

  // Get CAN interface parameter
  can_interface_ = "can0";  // Default
  if (info_.hardware_parameters.find("can_interface") != info_.hardware_parameters.end())
  {
    can_interface_ = info_.hardware_parameters.at("can_interface");
  }

  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"),
              "Initializing Tinymovr hardware interface with CAN interface: %s", can_interface_.c_str());

  // Resize state and command storage
  hw_states_positions_.resize(info_.joints.size(), std::numeric_limits<double>::quiet_NaN());
  hw_states_velocities_.resize(info_.joints.size(), std::numeric_limits<double>::quiet_NaN());
  hw_states_efforts_.resize(info_.joints.size(), std::numeric_limits<double>::quiet_NaN());
  hw_commands_positions_.resize(info_.joints.size(), std::numeric_limits<double>::quiet_NaN());
  hw_commands_velocities_.resize(info_.joints.size(), std::numeric_limits<double>::quiet_NaN());
  hw_commands_efforts_.resize(info_.joints.size(), std::numeric_limits<double>::quiet_NaN());

  // Resize hardware-specific storage
  servo_ids_.resize(info_.joints.size());
  delay_us_.resize(info_.joints.size());
  rads_to_ticks_.resize(info_.joints.size());
  servo_modes_.resize(info_.joints.size());
  offsets_.resize(info_.joints.size());

  // Parse joint parameters
  for (size_t i = 0; i < info_.joints.size(); ++i)
  {
    const auto & joint = info_.joints[i];
    RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Configuring joint: %s", joint.name.c_str());

    // Parse required parameters
    try {
      servo_ids_[i] = std::stoi(joint.parameters.at("id"));
      delay_us_[i] = std::stoi(joint.parameters.at("delay_us"));
      rads_to_ticks_[i] = std::stod(joint.parameters.at("rads_to_ticks"));
      servo_modes_[i] = joint.parameters.at("command_interface");
      offsets_[i] = std::stod(joint.parameters.at("offset"));

      RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"),
                  "  id: %d, delay_us: %d, rads_to_ticks: %f, mode: %s, offset: %f",
                  servo_ids_[i], delay_us_[i], rads_to_ticks_[i],
                  servo_modes_[i].c_str(), offsets_[i]);
    }
    catch (const std::exception & e) {
      RCLCPP_ERROR(rclcpp::get_logger("TinymovrSystem"),
                   "Error parsing parameters for joint %s: %s", joint.name.c_str(), e.what());
      return CallbackReturn::ERROR;
    }

    // Create Tinymovr instance (will be added to servos_ vector in on_configure)
  }

  return CallbackReturn::SUCCESS;
}

CallbackReturn TinymovrSystem::on_configure(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Configuring hardware interface...");

  // Open SocketCAN interface
  const scpp::SocketCanStatus status = socket_can.open(can_interface_);
  if (scpp::STATUS_OK != status)
  {
    RCLCPP_ERROR(rclcpp::get_logger("TinymovrSystem"),
                 "Can't open SocketCAN interface %s: %s",
                 can_interface_.c_str(), SocketCanErrorToString(status));
    return CallbackReturn::ERROR;
  }
  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "SocketCAN opened successfully");

  // Create Tinymovr instances
  servos_.clear();
  for (size_t i = 0; i < info_.joints.size(); ++i)
  {
    servos_.emplace_back(Tinymovr(servo_ids_[i], &send_cb, &recv_cb, &delay_us_cb, delay_us_[i]));
  }

  // Verify spec compatibility
  RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"), "Asserting spec compatibility");
  for (size_t i = 0; i < servos_.size(); ++i)
  {
    uint32_t proto_hash = servos_[i].get_protocol_hash();
    if (proto_hash != avlos_proto_hash)
    {
      RCLCPP_ERROR(rclcpp::get_logger("TinymovrSystem"),
                   "Protocol hash mismatch for joint %s (got 0x%08X, expected 0x%08X)",
                   info_.joints[i].name.c_str(), proto_hash, avlos_proto_hash);
      return CallbackReturn::ERROR;
    }
    RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"), "%s protocol OK", info_.joints[i].name.c_str());
  }

  // Verify calibration
  RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"), "Asserting calibrated");
  for (size_t i = 0; i < servos_.size(); ++i)
  {
    bool calibrated = servos_[i].get_calibrated();
    if (!calibrated)
    {
      RCLCPP_ERROR(rclcpp::get_logger("TinymovrSystem"),
                   "Joint %s is not calibrated!", info_.joints[i].name.c_str());
      return CallbackReturn::ERROR;
    }
    RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"), "%s calibrated OK", info_.joints[i].name.c_str());
  }

  // Initialize command values to zero
  for (size_t i = 0; i < info_.joints.size(); ++i)
  {
    hw_commands_positions_[i] = 0.0;
    hw_commands_velocities_[i] = 0.0;
    hw_commands_efforts_[i] = 0.0;
  }

  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Hardware interface configured successfully");
  return CallbackReturn::SUCCESS;
}

CallbackReturn TinymovrSystem::on_cleanup(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Cleaning up hardware interface...");
  // SocketCAN will be closed in on_shutdown if needed
  return CallbackReturn::SUCCESS;
}

CallbackReturn TinymovrSystem::on_activate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Activating hardware interface...");

  // Set servo states and modes
  for (size_t i = 0; i < servos_.size(); ++i)
  {
    RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"), "Setting state for %s", info_.joints[i].name.c_str());
    servos_[i].controller.set_state(2);  // State 2 = closed-loop control

    const uint8_t mode = str2mode(servo_modes_[i]);
    RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"), "Setting mode to %u for %s", mode, info_.joints[i].name.c_str());
    servos_[i].controller.set_mode(mode);

    rclcpp::sleep_for(std::chrono::milliseconds(1));

    // Verify state and mode
    uint8_t current_state = servos_[i].controller.get_state();
    uint8_t current_mode = servos_[i].controller.get_mode();
    if (current_state != 2 || current_mode != mode)
    {
      RCLCPP_ERROR(rclcpp::get_logger("TinymovrSystem"),
                   "Failed to set state/mode for %s (state: %u, mode: %u)",
                   info_.joints[i].name.c_str(), current_state, current_mode);
      return CallbackReturn::ERROR;
    }
    RCLCPP_DEBUG(rclcpp::get_logger("TinymovrSystem"), "State and mode OK for %s", info_.joints[i].name.c_str());
  }

  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Hardware interface activated successfully");
  return CallbackReturn::SUCCESS;
}

CallbackReturn TinymovrSystem::on_deactivate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Deactivating hardware interface...");

  // Gracefully stop motors
  for (size_t i = 0; i < servos_.size(); ++i)
  {
    try {
      servos_[i].controller.set_state(0);  // State 0 = idle
      rclcpp::sleep_for(std::chrono::milliseconds(1));
    }
    catch (const std::exception & e) {
      RCLCPP_WARN(rclcpp::get_logger("TinymovrSystem"),
                  "Error deactivating joint %s: %s", info_.joints[i].name.c_str(), e.what());
    }
  }

  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Hardware interface deactivated");
  return CallbackReturn::SUCCESS;
}

CallbackReturn TinymovrSystem::on_shutdown(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Shutting down hardware interface...");

  // Emergency stop all motors
  for (size_t i = 0; i < servos_.size(); ++i)
  {
    try {
      servos_[i].controller.set_state(0);  // State 0 = idle
      rclcpp::sleep_for(std::chrono::milliseconds(1));
    }
    catch (const std::exception & e) {
      RCLCPP_ERROR(rclcpp::get_logger("TinymovrSystem"),
                   "Error shutting down joint %s: %s", info_.joints[i].name.c_str(), e.what());
    }
  }

  RCLCPP_INFO(rclcpp::get_logger("TinymovrSystem"), "Hardware interface shut down");
  return CallbackReturn::SUCCESS;
}

CallbackReturn TinymovrSystem::on_error(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_ERROR(rclcpp::get_logger("TinymovrSystem"), "Hardware interface encountered an error!");
  // Attempt to stop motors
  for (size_t i = 0; i < servos_.size(); ++i)
  {
    try {
      servos_[i].controller.set_state(0);
    }
    catch (...) {
      // Ignore errors in error handler
    }
  }
  return CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> TinymovrSystem::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;

  for (size_t i = 0; i < info_.joints.size(); ++i)
  {
    state_interfaces.emplace_back(hardware_interface::StateInterface(
      info_.joints[i].name, hardware_interface::HW_IF_POSITION, &hw_states_positions_[i]));
    state_interfaces.emplace_back(hardware_interface::StateInterface(
      info_.joints[i].name, hardware_interface::HW_IF_VELOCITY, &hw_states_velocities_[i]));
    state_interfaces.emplace_back(hardware_interface::StateInterface(
      info_.joints[i].name, hardware_interface::HW_IF_EFFORT, &hw_states_efforts_[i]));
  }

  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> TinymovrSystem::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;

  for (size_t i = 0; i < info_.joints.size(); ++i)
  {
    command_interfaces.emplace_back(hardware_interface::CommandInterface(
      info_.joints[i].name, hardware_interface::HW_IF_POSITION, &hw_commands_positions_[i]));
    command_interfaces.emplace_back(hardware_interface::CommandInterface(
      info_.joints[i].name, hardware_interface::HW_IF_VELOCITY, &hw_commands_velocities_[i]));
    command_interfaces.emplace_back(hardware_interface::CommandInterface(
      info_.joints[i].name, hardware_interface::HW_IF_EFFORT, &hw_commands_efforts_[i]));
  }

  return command_interfaces;
}

hardware_interface::return_type TinymovrSystem::read(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{
  try {
    for (size_t i = 0; i < servos_.size(); ++i)
    {
      const double ticks_to_rads = 1.0 / rads_to_ticks_[i];
      hw_states_positions_[i] = servos_[i].sensors.user_frame.get_position_estimate() * ticks_to_rads;
      hw_states_velocities_[i] = servos_[i].sensors.user_frame.get_velocity_estimate() * ticks_to_rads;
      hw_states_efforts_[i] = servos_[i].controller.current.get_Iq_estimate();
    }
    return hardware_interface::return_type::OK;
  }
  catch(const std::exception& e)
  {
    RCLCPP_ERROR(rclcpp::get_logger("TinymovrSystem"), "Error reading from Tinymovr CAN: %s", e.what());
    return hardware_interface::return_type::ERROR;
  }
}

hardware_interface::return_type TinymovrSystem::write(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{
  try {
    for (size_t i = 0; i < servos_.size(); ++i)
    {
      servos_[i].controller.position.set_setpoint(hw_commands_positions_[i] * rads_to_ticks_[i]);
      servos_[i].controller.velocity.set_setpoint(hw_commands_velocities_[i] * rads_to_ticks_[i]);
      servos_[i].controller.current.set_Iq_setpoint(hw_commands_efforts_[i]);
    }
    return hardware_interface::return_type::OK;
  }
  catch(const std::exception& e)
  {
    RCLCPP_ERROR(rclcpp::get_logger("TinymovrSystem"), "Error writing to Tinymovr CAN: %s", e.what());
    return hardware_interface::return_type::ERROR;
  }
}

uint8_t TinymovrSystem::str2mode(const std::string & mode_string)
{
  if (mode_string == "current" || mode_string == "effort")
    return 0;
  else if (mode_string == "velocity")
    return 1;
  else if (mode_string == "position")
    return 2;
  else {
    RCLCPP_WARN(rclcpp::get_logger("TinymovrSystem"),
                "Unknown command mode '%s', defaulting to current/effort", mode_string.c_str());
    return 0;
  }
}

}  // namespace tinymovr_ros

#include "pluginlib/class_list_macros.hpp"

PLUGINLIB_EXPORT_CLASS(tinymovr_ros::TinymovrSystem, hardware_interface::SystemInterface)
