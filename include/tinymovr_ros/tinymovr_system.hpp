#pragma once

#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp"
#include "rclcpp_lifecycle/state.hpp"

#include <tinymovr/tinymovr.hpp>

namespace tinymovr_ros
{

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class TinymovrSystem : public hardware_interface::SystemInterface
{
public:
  RCLCPP_SHARED_PTR_DEFINITIONS(TinymovrSystem)

  // Lifecycle management methods
  CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;

  CallbackReturn on_configure(const rclcpp_lifecycle::State & previous_state) override;

  CallbackReturn on_cleanup(const rclcpp_lifecycle::State & previous_state) override;

  CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state) override;

  CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state) override;

  CallbackReturn on_shutdown(const rclcpp_lifecycle::State & previous_state) override;

  CallbackReturn on_error(const rclcpp_lifecycle::State & previous_state) override;

  // Hardware communication methods
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  hardware_interface::return_type read(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

  hardware_interface::return_type write(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

private:
  // Helper method to convert mode string to mode index
  uint8_t str2mode(const std::string & mode_string);

  // State storage
  std::vector<double> hw_commands_positions_;
  std::vector<double> hw_commands_velocities_;
  std::vector<double> hw_commands_efforts_;
  std::vector<double> hw_states_positions_;
  std::vector<double> hw_states_velocities_;
  std::vector<double> hw_states_efforts_;

  // Hardware communication
  std::vector<Tinymovr> servos_;
  std::vector<std::string> servo_modes_;
  std::vector<double> rads_to_ticks_;
  std::vector<int> servo_ids_;
  std::vector<int> delay_us_;
  std::vector<double> offsets_;

  std::string can_interface_;
};

}  // namespace tinymovr_ros
