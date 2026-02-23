/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>
#include <nvm.hpp>
#include <scheduler.hpp>
#include <controller.hpp>
#include <comms.hpp>
#include <motor.hpp>
#include <sensors.hpp>
#include <traj_planner.hpp>
#include <homing.hpp>
#include <watchdog.hpp>

static uint32_t avlos_proto_hash = 3999954334;

enum errors_flags
{
    ERRORS_NONE = 0,
    ERRORS_UNDERVOLTAGE = (1 << 0)
};

enum warnings_flags
{
    WARNINGS_NONE = 0,
    WARNINGS_DRIVER_FAULT = (1 << 0), 
    WARNINGS_CHARGE_PUMP_FAULT_STAT = (1 << 1), 
    WARNINGS_CHARGE_PUMP_FAULT = (1 << 2), 
    WARNINGS_DRV10_DISABLE = (1 << 3), 
    WARNINGS_DRV32_DISABLE = (1 << 4), 
    WARNINGS_DRV54_DISABLE = (1 << 5)
};

enum scheduler_warnings_flags
{
    SCHEDULER_WARNINGS_NONE = 0,
    SCHEDULER_WARNINGS_CONTROL_BLOCK_REENTERED = (1 << 0)
};

enum controller_warnings_flags
{
    CONTROLLER_WARNINGS_NONE = 0,
    CONTROLLER_WARNINGS_VELOCITY_LIMITED = (1 << 0), 
    CONTROLLER_WARNINGS_CURRENT_LIMITED = (1 << 1), 
    CONTROLLER_WARNINGS_MODULATION_LIMITED = (1 << 2)
};

enum controller_errors_flags
{
    CONTROLLER_ERRORS_NONE = 0,
    CONTROLLER_ERRORS_CURRENT_LIMIT_EXCEEDED = (1 << 0), 
    CONTROLLER_ERRORS_PRE_CL_I_SD_EXCEEDED = (1 << 1)
};

enum motor_errors_flags
{
    MOTOR_ERRORS_NONE = 0,
    MOTOR_ERRORS_PHASE_RESISTANCE_OUT_OF_RANGE = (1 << 0), 
    MOTOR_ERRORS_PHASE_INDUCTANCE_OUT_OF_RANGE = (1 << 1), 
    MOTOR_ERRORS_POLE_PAIRS_CALCULATION_DID_NOT_CONVERGE = (1 << 2), 
    MOTOR_ERRORS_POLE_PAIRS_OUT_OF_RANGE = (1 << 3), 
    MOTOR_ERRORS_ABNORMAL_CALIBRATION_VOLTAGE = (1 << 4)
};

enum sensors_setup_onboard_errors_flags
{
    SENSORS_SETUP_ONBOARD_ERRORS_NONE = 0,
    SENSORS_SETUP_ONBOARD_ERRORS_CALIBRATION_FAILED = (1 << 0), 
    SENSORS_SETUP_ONBOARD_ERRORS_READING_UNSTABLE = (1 << 1)
};

enum sensors_setup_external_spi_errors_flags
{
    SENSORS_SETUP_EXTERNAL_SPI_ERRORS_NONE = 0,
    SENSORS_SETUP_EXTERNAL_SPI_ERRORS_CALIBRATION_FAILED = (1 << 0), 
    SENSORS_SETUP_EXTERNAL_SPI_ERRORS_READING_UNSTABLE = (1 << 1)
};

enum sensors_setup_hall_errors_flags
{
    SENSORS_SETUP_HALL_ERRORS_NONE = 0,
    SENSORS_SETUP_HALL_ERRORS_CALIBRATION_FAILED = (1 << 0), 
    SENSORS_SETUP_HALL_ERRORS_READING_UNSTABLE = (1 << 1)
};

enum traj_planner_errors_flags
{
    TRAJ_PLANNER_ERRORS_NONE = 0,
    TRAJ_PLANNER_ERRORS_INVALID_INPUT = (1 << 0), 
    TRAJ_PLANNER_ERRORS_VCRUISE_OVER_LIMIT = (1 << 1)
};

enum homing_warnings_flags
{
    HOMING_WARNINGS_NONE = 0,
    HOMING_WARNINGS_HOMING_TIMEOUT = (1 << 0)
};

enum controller_state_options
{
    CONTROLLER_STATE_IDLE = 0, 
    CONTROLLER_STATE_CALIBRATE = 1, 
    CONTROLLER_STATE_CL_CONTROL = 2
};

enum controller_mode_options
{
    CONTROLLER_MODE_CURRENT = 0, 
    CONTROLLER_MODE_VELOCITY = 1, 
    CONTROLLER_MODE_POSITION = 2, 
    CONTROLLER_MODE_TRAJECTORY = 3, 
    CONTROLLER_MODE_HOMING = 4
};

enum motor_type_options
{
    MOTOR_TYPE_HIGH_CURRENT = 0, 
    MOTOR_TYPE_GIMBAL = 1
};

enum sensors_setup_external_spi_type_options
{
    SENSORS_SETUP_EXTERNAL_SPI_TYPE_MA7XX = 0, 
    SENSORS_SETUP_EXTERNAL_SPI_TYPE_AS5047 = 1, 
    SENSORS_SETUP_EXTERNAL_SPI_TYPE_AMT22 = 2
};

enum sensors_setup_external_spi_rate_options
{
    SENSORS_SETUP_EXTERNAL_SPI_RATE_1_5Mbps = 0, 
    SENSORS_SETUP_EXTERNAL_SPI_RATE_3Mbps = 1, 
    SENSORS_SETUP_EXTERNAL_SPI_RATE_6Mbps = 2, 
    SENSORS_SETUP_EXTERNAL_SPI_RATE_8Mbps = 3, 
    SENSORS_SETUP_EXTERNAL_SPI_RATE_12Mbps = 4
};

enum sensors_select_position_sensor_connection_options
{
    SENSORS_SELECT_POSITION_SENSOR_CONNECTION_ONBOARD = 0, 
    SENSORS_SELECT_POSITION_SENSOR_CONNECTION_EXTERNAL_SPI = 1, 
    SENSORS_SELECT_POSITION_SENSOR_CONNECTION_HALL = 2
};

enum sensors_select_commutation_sensor_connection_options
{
    SENSORS_SELECT_COMMUTATION_SENSOR_CONNECTION_ONBOARD = 0, 
    SENSORS_SELECT_COMMUTATION_SENSOR_CONNECTION_EXTERNAL_SPI = 1, 
    SENSORS_SELECT_COMMUTATION_SENSOR_CONNECTION_HALL = 2
};

class Tinymovr : Node
{
    public:

        Tinymovr(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , nvm(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , scheduler(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , controller(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , comms(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , motor(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , sensors(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , traj_planner(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , homing(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , watchdog(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        uint32_t get_protocol_hash(void);
        uint32_t get_uid(void);
        void get_fw_version(char out_value[]);
        uint32_t get_hw_revision(void);
        float get_Vbus(void);
        float get_Ibus(void);
        float get_power(void);
        float get_temp(void);
        bool get_calibrated(void);
        uint8_t get_errors(void);
        uint8_t get_warnings(void);
        void save_config();
        void erase_config();
        Nvm_ nvm;
        void reset();
        void enter_dfu();
        uint32_t get_config_size(void);
        Scheduler_ scheduler;
        Controller_ controller;
        Comms_ comms;
        Motor_ motor;
        Sensors_ sensors;
        Traj_planner_ traj_planner;
        Homing_ homing;
        Watchdog_ watchdog;

};
