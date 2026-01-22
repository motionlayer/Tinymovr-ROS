/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <tm_helpers.hpp>
#include <position.hpp>
#include <velocity.hpp>
#include <current.hpp>
#include <voltage.hpp>

class Controller_ : Node
{
    public:

        Controller_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , position(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , velocity(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , current(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , voltage(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        uint8_t get_state(void);
        void set_state(uint8_t value);
        uint8_t get_mode(void);
        void set_mode(uint8_t value);
        uint8_t get_warnings(void);
        uint8_t get_errors(void);
        Position_ position;
        Velocity_ velocity;
        Current_ current;
        Voltage_ voltage;
        void calibrate();
        void idle();
        void position_mode();
        void velocity_mode();
        void current_mode();
        float set_pos_vel_setpoints(float pos_setpoint, float vel_setpoint);

};
