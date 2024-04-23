
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <stdexcept>

#include <ros/console.h>

#include "socketcan_cpp/socketcan_cpp.hpp"
#include <tm_joint_iface.hpp>

using namespace std;

namespace tinymovr_ros
{

scpp::SocketCan socket_can;

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

/**
 * @brief Callback function to send a CAN frame.
 * 
 * This function is called whenever a CAN frame needs to be transmitted. It sets up the necessary 
 * CAN frame fields and writes the frame using the SocketCAN interface.
 * 
 * @param arbitration_id The frame arbitration id.
 * @param data Pointer to the data array to be transmitted.
 * @param data_length The size of transmitted data.
 * @param rtr If the frame is of request transmit type (RTR).
 * 
 * @throws std::runtime_error If the CAN frame write fails.
 * 
 * @note The function logs debug messages about the CAN frame write status.
 */
void send_cb(uint32_t arbitration_id, uint8_t *data, uint8_t data_length, bool rtr)
{
    ROS_DEBUG_STREAM("Attempting to write CAN frame with arbitration_id: " << arbitration_id);

    scpp::CanFrame cf_to_write;

    cf_to_write.id = arbitration_id;
    if (rtr) {
        cf_to_write.id |= CAN_RTR_FLAG; // Set RTR flag if rtr argument
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
        ROS_DEBUG_STREAM("CAN frame with arbitration_id: " << arbitration_id << " written successfully.");
    }
}

/**
 * @brief Callback function to receive a CAN frame.
 * 
 * This function is called whenever a CAN frame is to be received. It attempts to read a CAN 
 * frame using the SocketCAN interface.
 * 
 * @param arbitration_id Pointer to the frame arbitration id.
 * @param data Pointer to the data array to be received.
 * @param data_length Pointer to the variable that will hold the size of received data.
 * 
 * @return True if the CAN frame was read successfully, false otherwise.
 * 
 * @throws std::runtime_error If the CAN frame read fails.
 * 
 * @note The function logs debug messages about the CAN frame read status.
 */
bool recv_cb(uint32_t *arbitration_id, uint8_t *data, uint8_t *data_length)
{
    ROS_DEBUG_STREAM("Attempting to read CAN frame...");

    scpp::CanFrame fr;
    scpp::SocketCanStatus read_status = socket_can.read(fr);
    if (read_status == scpp::STATUS_OK)
    {
        *arbitration_id = fr.id & CAN_EFF_MASK;
        *data_length = fr.len;
        std::copy(fr.data, fr.data + fr.len, data);
        ROS_DEBUG_STREAM("CAN frame with arbitration_id: " << *arbitration_id << " read successfully.");
        return true;
    }
    else
    {
        throw std::runtime_error(SocketCanErrorToString(read_status));
        return false;
    }
}

/**
 * @brief Callback function to perform a delay.
 * 
 * This function is called whenever a delay is required. It uses the ROS sleep functionality
 * to create a delay for a specified duration in microseconds.
 * 
 * @param us The microseconds to wait for.
 * 
 * @note The function relies on the ROS sleep mechanism for precise timing.
 */
void delay_us_cb(uint32_t us)
{
    ros::Duration(us * 1e-6).sleep();
}

TinymovrJoint::TinymovrJoint() {}

TinymovrJoint::~TinymovrJoint() {}

/**
 * @brief Initializes the TinymovrJoint instance.
 * 
 * This function initializes the TinymovrJoint, setting up the servos based on the ROS parameters
 * specified in the given NodeHandle. It also sets up the interfaces for joint state, position,
 * velocity, and effort, and registers these interfaces.
 * 
 * @param root_nh The root node handle.
 * @param robot_hw_nh The robot hardware node handle.
 * 
 * @return True if initialization succeeds, false otherwise.
 * 
 * @note The initialization process involves several steps, including reading configuration
 * from the ROS parameter server, setting up the SocketCAN interface, initializing each
 * servo's mode and state, and registering the necessary hardware interfaces.
 */
bool TinymovrJoint::init(ros::NodeHandle& root_nh, ros::NodeHandle& robot_hw_nh)
{
    
    XmlRpc::XmlRpcValue servos_param;

    bool got_all_params = true;

    // build servo instances from configuration
    if (got_all_params &= robot_hw_nh.getParam("/tinymovr_joint_iface/joints", servos_param)) {
            ROS_ASSERT(servos_param.getType() == XmlRpc::XmlRpcValue::TypeStruct);
        try {
            for (XmlRpc::XmlRpcValue::ValueStruct::const_iterator it = servos_param.begin(); it != servos_param.end(); ++it) {

                std::string current_joint_name = static_cast<std::string>(it->first);
                ROS_INFO_STREAM("servo: " << current_joint_name);
                joint_name.push_back(current_joint_name); // Store joint name

                id_t id;
                int delay_us;
                if (it->second.hasMember("id"))
                {
                    id = static_cast<int>(servos_param[it->first]["id"]);
                    delay_us = static_cast<int>(servos_param[it->first]["delay_us"]);
                    ROS_INFO_STREAM("\tid: " << id << " delay_us: " << delay_us);
                    servos.push_back(Tinymovr(id, &send_cb, &recv_cb, &delay_us_cb, delay_us));
                    servo_modes.push_back(servos_param[it->first]["command_interface"]);
                    rads_to_ticks.push_back(static_cast<double>(servos_param[it->first]["rads_to_ticks"]));
                }
                else
                {
                    ROS_ERROR_STREAM("servo " << it->first << " has no associated servo ID.");
                    continue;
                }
            }
        }
        catch (XmlRpc::XmlRpcException& e) 
        {
            ROS_FATAL_STREAM("Exception raised by XmlRpc while reading the "
                << "configuration: " << e.getMessage() << ".\n"
                << "Please check the configuration, particularly parameter types.");
            return false;
        }
    }

    if (!got_all_params) {
        std::string sub_namespace = robot_hw_nh.getNamespace();
        std::string error_message = "One or more of the following parameters "
                            "were not set:\n"
            + sub_namespace + "/tinymovr_joint_iface/joints";
        ROS_FATAL_STREAM(error_message);
        return false;
    }

    num_joints = servos_param.size();

    joint_position_command.resize(num_joints, 0.0);
    joint_velocity_command.resize(num_joints, 0.0);
    joint_effort_command.resize(num_joints, 0.0);
    joint_position_state.resize(num_joints, 0.0);
    joint_velocity_state.resize(num_joints, 0.0);
    joint_effort_state.resize(num_joints, 0.0);

    const scpp::SocketCanStatus status = socket_can.open("can0");
    if (scpp::STATUS_OK == status)
    {
        ROS_INFO("Socketcan opened successfully");
    }
    else
    {
        ROS_ERROR("Cant' open Socketcan: %d", status);
        exit(1);
    }

    // initialize servos with correct mode
    ROS_DEBUG("Asserting spec compatibility");
    for (int i=0; i<num_joints; i++)
    {
        ROS_ASSERT(servos[i].get_protocol_hash() == avlos_proto_hash);
        ROS_DEBUG("%s ok", joint_name[i].c_str());
    }

    ROS_DEBUG("Asserting calibrated");
    for (int i=0; i<num_joints; i++)
    {
        ROS_ASSERT(servos[i].get_calibrated() == true);
        ROS_DEBUG("%s ok", joint_name[i].c_str());
    }

    for (int i=0; i<num_joints; i++)
    { 
        ROS_DEBUG("Setting state");
        servos[i].controller.set_state(2);
        const uint8_t mode = _str2mode(servo_modes[i]);
        ROS_DEBUG("Setting mode to %u", mode);
        servos[i].controller.set_mode(mode);
        ros::Duration(0.001).sleep();
        ROS_DEBUG("Asserting state and mode");
        ROS_ASSERT((servos[i].controller.get_state() == 2) && (servos[i].controller.get_mode() == mode));
    }

    ROS_DEBUG("Registering Tinymovr Interfaces");
    // register state interfaces
    for (int i=0; i<num_joints; i++)
    {
        // connect and register the joint state interface
        hardware_interface::JointStateHandle state_handle(
            joint_name[i],
            &joint_position_state[i],
            &joint_velocity_state[i],
            &joint_effort_state[i]
            );
        joint_state_interface.registerHandle(state_handle);
        
        const uint8_t mode = _str2mode(servo_modes[i]);

        // connect and register the joint position interface
        hardware_interface::JointHandle pos_handle(joint_state_interface.getHandle(joint_name[i]), &joint_position_command[i]);
        joint_pos_interface.registerHandle(pos_handle);
        
        // connect and register the joint velocity interface
        hardware_interface::JointHandle vel_handle(joint_state_interface.getHandle(joint_name[i]), &joint_velocity_command[i]);
        joint_vel_interface.registerHandle(vel_handle);
        
        // connect and register the joint effort interface
        hardware_interface::JointHandle eff_handle(joint_state_interface.getHandle(joint_name[i]), &joint_effort_command[i]);
        joint_eff_interface.registerHandle(eff_handle);
    }

    registerInterface(&joint_state_interface);
    registerInterface(&joint_pos_interface);
    registerInterface(&joint_vel_interface);
    registerInterface(&joint_eff_interface);

    return true;
}

/** 
 * @brief Convert a string to an operating mode
 *
 * @param mode_string name of the operating mode (current or effort, velocity or position)
 * @return mode index corresponding to the index of the mode
 */
uint8_t TinymovrJoint::_str2mode(std::string& mode_string)
{
    if ("current" == mode_string || "effort" == mode_string)
        return 0;
    if ("velocity" == mode_string)
        return 1;
    else if ("position" == mode_string)
        return 2;
    else {
        ROS_ERROR_STREAM("The command mode " << mode_string << " is not available");
        return 0;
    }
}

/**
 * @brief Reads the state of each servo in the TinymovrJoint.
 * 
 * This function iterates over each servo connected to the TinymovrJoint
 * and fetches its current position, velocity, and effort (current) state.
 * In case of any communication or other exceptions, an error is logged.
 *
 * @param time Current ROS time.
 * @param period Time since the last call to this function.
 */
void TinymovrJoint::read(const ros::Time& time, const ros::Duration& period)
{
    try {
        for (int i=0; i<servos.size(); i++)
        {
            const double ticks_to_rads = 1.0/rads_to_ticks[i];
            joint_position_state[i] = servos[i].sensors.user_frame.get_position_estimate() * ticks_to_rads;
            joint_velocity_state[i] = servos[i].sensors.user_frame.get_velocity_estimate() * ticks_to_rads;
            joint_effort_state[i] = servos[i].controller.current.get_Iq_estimate();
        }
    }
    catch(const std::exception& e)
    {
        ROS_ERROR_STREAM("Error while reading Tinymovr CAN:\n" << e.what());
    }
}

/**
 * @brief Writes command values to each servo in the TinymovrJoint.
 * 
 * This function iterates over each servo connected to the TinymovrJoint 
 * and sets the position, velocity, and effort (current) setpoints 
 * as per the current command values.
 * In case of any communication or other exceptions, an error is logged.
 *
 * @param time Current ROS time.
 * @param period Time since the last call to this function.
 */
void TinymovrJoint::write(const ros::Time& time, const ros::Duration& period)
{
    try {
        for (int i=0; i<servos.size(); i++)
        {
            servos[i].controller.position.set_setpoint(joint_position_command[i] * rads_to_ticks[i]);
            servos[i].controller.velocity.set_setpoint(joint_velocity_command[i] * rads_to_ticks[i]);
            servos[i].controller.current.set_Iq_setpoint(joint_effort_command[i]);
        }
    }
    catch(const std::exception& e)
    {
        ROS_ERROR_STREAM("Error while writing Tinymovr CAN:\n" << e.what());
    }
}

void TinymovrJoint::shutdown() 
{
    ROS_INFO("Explicitly shutting down Tinymovr instances from hardware interface.");
    for (int i=0; i<num_joints; i++)
    { 
        servos[i].controller.set_state(0);
        ros::Duration(0.001).sleep();
    }
}

}