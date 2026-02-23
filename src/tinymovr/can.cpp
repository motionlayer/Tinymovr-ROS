/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <can.hpp>

uint32_t Can_::get_rate(void)
{
    uint32_t value = 0;
    this->send(48, this->_data, 0, true);
    if (this->recv(48, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Can_::set_rate(uint32_t value)
{
    write_le(value, this->_data);
    this->send(48, this->_data, sizeof(uint32_t), false);
}

uint32_t Can_::get_id(void)
{
    uint32_t value = 0;
    this->send(49, this->_data, 0, true);
    if (this->recv(49, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Can_::set_id(uint32_t value)
{
    write_le(value, this->_data);
    this->send(49, this->_data, sizeof(uint32_t), false);
}

bool Can_::get_heartbeat(void)
{
    bool value = 0;
    this->send(50, this->_data, 0, true);
    if (this->recv(50, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Can_::set_heartbeat(bool value)
{
    write_le(value, this->_data);
    this->send(50, this->_data, sizeof(bool), false);
}

