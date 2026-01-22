/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <tm_helpers.hpp>
#include <stall_detect.hpp>

class Homing_ : Node
{
    public:

        Homing_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , stall_detect(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        float get_velocity(void);
        void set_velocity(float value);
        float get_max_homing_t(void);
        void set_max_homing_t(float value);
        float get_retract_dist(void);
        void set_retract_dist(float value);
        uint8_t get_warnings(void);
        Stall_detect_ stall_detect;
        void home();

};
