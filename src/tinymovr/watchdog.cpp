/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <watchdog.hpp>

bool Watchdog_::get_enabled(void)
{
    bool value = 0;
    this->send(97, this->_data, 0, true);
    if (this->recv(97, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Watchdog_::set_enabled(bool value)
{
    write_le(value, this->_data);
    this->send(97, this->_data, sizeof(bool), false);
}

bool Watchdog_::get_triggered(void)
{
    bool value = 0;
    this->send(98, this->_data, 0, true);
    if (this->recv(98, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Watchdog_::get_timeout(void)
{
    float value = 0;
    this->send(99, this->_data, 0, true);
    if (this->recv(99, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Watchdog_::set_timeout(float value)
{
    write_le(value, this->_data);
    this->send(99, this->_data, sizeof(float), false);
}

