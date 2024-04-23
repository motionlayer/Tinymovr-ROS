/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>

class External_spi_ : Node
{
    public:

        External_spi_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        uint8_t get_type(void);
        void set_type(uint8_t value);
        uint8_t get_rate(void);
        void set_rate(uint8_t value);
        bool get_calibrated(void);
        uint8_t get_errors(void);

};
