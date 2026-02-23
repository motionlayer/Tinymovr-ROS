/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <hall.hpp>

bool Hall_::get_calibrated(void)
{
    bool value = 0;
    this->send(68, this->_data, 0, true);
    if (this->recv(68, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t Hall_::get_errors(void)
{
    uint8_t value = 0;
    this->send(69, this->_data, 0, true);
    if (this->recv(69, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

