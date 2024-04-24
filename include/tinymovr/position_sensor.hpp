/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>

class Position_sensor_ : Node
{
    public:

        Position_sensor_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        uint8_t get_connection(void);
        void set_connection(uint8_t value);
        float get_bandwidth(void);
        void set_bandwidth(float value);
        int32_t get_raw_angle(void);
        float get_position_estimate(void);
        float get_velocity_estimate(void);

};
