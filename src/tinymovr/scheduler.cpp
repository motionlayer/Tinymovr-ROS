/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <scheduler.hpp>

uint32_t Scheduler_::get_load(void)
{
    uint32_t value = 0;
    this->send(19, this->_data, 0, true);
    if (this->recv(19, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t Scheduler_::get_warnings(void)
{
    uint8_t value = 0;
    this->send(20, this->_data, 0, true);
    if (this->recv(20, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

