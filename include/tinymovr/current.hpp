/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <tm_helpers.hpp>

class Current_ : Node
{
    public:

        Current_(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
            Node(_can_node_id, _send_cb, _recv_cb, _delay_us_cb, _delay_us_value) {};
        float get_Iq_setpoint(void);
        void set_Iq_setpoint(float value);
        float get_Id_setpoint(void);
        float get_Iq_limit(void);
        void set_Iq_limit(float value);
        float get_Iq_estimate(void);
        float get_bandwidth(void);
        void set_bandwidth(float value);
        float get_Iq_p_gain(void);
        float get_max_Ibus_regen(void);
        void set_max_Ibus_regen(float value);
        float get_max_Ibrake(void);
        void set_max_Ibrake(float value);

};
