/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>

class User_frame_ : Node
{
    public:

        User_frame_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        float get_position_estimate(void);
        float get_velocity_estimate(void);
        float get_offset(void);
        void set_offset(float value);
        float get_multiplier(void);
        void set_multiplier(float value);

};
