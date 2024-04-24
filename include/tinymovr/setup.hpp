/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>
#include <onboard.hpp>
#include <external_spi.hpp>
#include <hall.hpp>

class Setup_ : Node
{
    public:

        Setup_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , onboard(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , external_spi(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , hall(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        Onboard_ onboard;
        External_spi_ external_spi;
        Hall_ hall;

};
