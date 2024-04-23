/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>

class Can_ : Node
{
    public:

        Can_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        uint32_t get_rate(void);
        void set_rate(uint32_t value);
        uint32_t get_id(void);
        void set_id(uint32_t value);
        bool get_heartbeat(void);
        void set_heartbeat(bool value);

};
