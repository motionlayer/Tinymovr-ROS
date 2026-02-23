/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <voltage.hpp>

float Voltage_::get_Vq_setpoint(void)
{
    float value = 0;
    this->send(41, this->_data, 0, true);
    if (this->recv(41, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

