/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <tm_helpers.hpp>
#include <scheduler.hpp>
#include <controller.hpp>
#include <comms.hpp>
#include <motor.hpp>
#include <encoder.hpp>
#include <traj_planner.hpp>
#include <homing.hpp>
#include <watchdog.hpp>

static uint32_t avlos_proto_hash = 4118115615;

enum errors_flags
{
    ERRORS_NONE = 0,
    ERRORS_UNDERVOLTAGE = (1 << 0), 
    ERRORS_DRIVER_FAULT = (1 << 1), 
    ERRORS_CHARGE_PUMP_FAULT_STAT = (1 << 2), 
    ERRORS_CHARGE_PUMP_FAULT = (1 << 3), 
    ERRORS_DRV10_DISABLE = (1 << 4), 
    ERRORS_DRV32_DISABLE = (1 << 5), 
    ERRORS_DRV54_DISABLE = (1 << 6)
};

enum scheduler_errors_flags
{
    SCHEDULER_ERRORS_NONE = 0,
    SCHEDULER_ERRORS_CONTROL_BLOCK_REENTERED = (1 << 0)
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
    CONTROLLER_ERRORS_CURRENT_LIMIT_EXCEEDED = (1 << 0)
};

enum motor_errors_flags
{
    MOTOR_ERRORS_NONE = 0,
    MOTOR_ERRORS_PHASE_RESISTANCE_OUT_OF_RANGE = (1 << 0), 
    MOTOR_ERRORS_PHASE_INDUCTANCE_OUT_OF_RANGE = (1 << 1), 
    MOTOR_ERRORS_INVALID_POLE_PAIRS = (1 << 2)
};

enum encoder_errors_flags
{
    ENCODER_ERRORS_NONE = 0,
    ENCODER_ERRORS_CALIBRATION_FAILED = (1 << 0), 
    ENCODER_ERRORS_READING_UNSTABLE = (1 << 1)
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

enum motor_type_options
{
    MOTOR_TYPE_HIGH_CURRENT = 0, 
    MOTOR_TYPE_GIMBAL = 1
};

enum encoder_type_options
{
    ENCODER_TYPE_INTERNAL = 0, 
    ENCODER_TYPE_HALL = 1
};

class Tinymovr : Node
{
    public:

        Tinymovr(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , scheduler(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , controller(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , comms(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , motor(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , encoder(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
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
        void save_config();
        void erase_config();
        void reset();
        void enter_dfu();
        Scheduler_ scheduler;
        Controller_ controller;
        Comms_ comms;
        Motor_ motor;
        Encoder_ encoder;
        Traj_planner_ traj_planner;
        Homing_ homing;
        Watchdog_ watchdog;

};
