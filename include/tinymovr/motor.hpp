/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <tm_helpers.hpp>

class Motor_ : Node
{
    public:

        Motor_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        float get_R(void);
        void set_R(float value);
        float get_L(void);
        void set_L(float value);
        uint8_t get_pole_pairs(void);
        void set_pole_pairs(uint8_t value);
        uint8_t get_type(void);
        void set_type(uint8_t value);
        float get_offset(void);
        void set_offset(float value);
        int8_t get_direction(void);
        void set_direction(int8_t value);
        bool get_calibrated(void);
        float get_I_cal(void);
        void set_I_cal(float value);
        uint8_t get_errors(void);

};
