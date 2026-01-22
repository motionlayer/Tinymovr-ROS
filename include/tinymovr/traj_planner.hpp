/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <tm_helpers.hpp>

class Traj_planner_ : Node
{
    public:

        Traj_planner_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        float get_max_accel(void);
        void set_max_accel(float value);
        float get_max_decel(void);
        void set_max_decel(float value);
        float get_max_vel(void);
        void set_max_vel(float value);
        float get_t_accel(void);
        void set_t_accel(float value);
        float get_t_decel(void);
        void set_t_decel(float value);
        float get_t_total(void);
        void set_t_total(float value);
        void move_to(float pos_setpoint);
        void move_to_tlimit(float pos_setpoint);
        uint8_t get_errors(void);

};
