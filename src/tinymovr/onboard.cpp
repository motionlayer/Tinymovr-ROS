/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <onboard.hpp>

bool Onboard_::get_calibrated(void)
{
    bool value = 0;
    this->send(62, this->_data, 0, true);
    if (this->recv(62, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t Onboard_::get_errors(void)
{
    uint8_t value = 0;
    this->send(63, this->_data, 0, true);
    if (this->recv(63, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

