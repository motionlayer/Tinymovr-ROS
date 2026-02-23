/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <velocity.hpp>

float Velocity_::get_setpoint(void)
{
    float value = 0;
    this->send(27, this->_data, 0, true);
    if (this->recv(27, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Velocity_::set_setpoint(float value)
{
    write_le(value, this->_data);
    this->send(27, this->_data, sizeof(float), false);
}

float Velocity_::get_limit(void)
{
    float value = 0;
    this->send(28, this->_data, 0, true);
    if (this->recv(28, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Velocity_::set_limit(float value)
{
    write_le(value, this->_data);
    this->send(28, this->_data, sizeof(float), false);
}

float Velocity_::get_p_gain(void)
{
    float value = 0;
    this->send(29, this->_data, 0, true);
    if (this->recv(29, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Velocity_::set_p_gain(float value)
{
    write_le(value, this->_data);
    this->send(29, this->_data, sizeof(float), false);
}

float Velocity_::get_i_gain(void)
{
    float value = 0;
    this->send(30, this->_data, 0, true);
    if (this->recv(30, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Velocity_::set_i_gain(float value)
{
    write_le(value, this->_data);
    this->send(30, this->_data, sizeof(float), false);
}

float Velocity_::get_deadband(void)
{
    float value = 0;
    this->send(31, this->_data, 0, true);
    if (this->recv(31, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Velocity_::set_deadband(float value)
{
    write_le(value, this->_data);
    this->send(31, this->_data, sizeof(float), false);
}

float Velocity_::get_increment(void)
{
    float value = 0;
    this->send(32, this->_data, 0, true);
    if (this->recv(32, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Velocity_::set_increment(float value)
{
    write_le(value, this->_data);
    this->send(32, this->_data, sizeof(float), false);
}

