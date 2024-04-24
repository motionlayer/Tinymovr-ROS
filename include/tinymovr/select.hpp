/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>
#include <position_sensor.hpp>
#include <commutation_sensor.hpp>

class Select_ : Node
{
    public:

        Select_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , position_sensor(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value)
            , commutation_sensor(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        Position_sensor_ position_sensor;
        Commutation_sensor_ commutation_sensor;

};
