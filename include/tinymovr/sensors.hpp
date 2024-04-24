/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>
#include <user_frame.hpp>
#include <setup.hpp>
#include <select.hpp>

class Sensors_ : Node
{
    public:

        Sensors_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , user_frame(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , setup(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , select(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        User_frame_ user_frame;
        Setup_ setup;
        Select_ select;

};
