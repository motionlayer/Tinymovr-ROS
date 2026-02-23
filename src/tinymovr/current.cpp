/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <current.hpp>

float Current_::get_Iq_setpoint(void)
{
    float value = 0;
    this->send(33, this->_data, 0, true);
    if (this->recv(33, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_Iq_setpoint(float value)
{
    write_le(value, this->_data);
    this->send(33, this->_data, sizeof(float), false);
}

float Current_::get_Id_setpoint(void)
{
    float value = 0;
    this->send(34, this->_data, 0, true);
    if (this->recv(34, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Current_::get_Iq_limit(void)
{
    float value = 0;
    this->send(35, this->_data, 0, true);
    if (this->recv(35, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_Iq_limit(float value)
{
    write_le(value, this->_data);
    this->send(35, this->_data, sizeof(float), false);
}

float Current_::get_Iq_estimate(void)
{
    float value = 0;
    this->send(36, this->_data, 0, true);
    if (this->recv(36, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Current_::get_bandwidth(void)
{
    float value = 0;
    this->send(37, this->_data, 0, true);
    if (this->recv(37, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_bandwidth(float value)
{
    write_le(value, this->_data);
    this->send(37, this->_data, sizeof(float), false);
}

float Current_::get_Iq_p_gain(void)
{
    float value = 0;
    this->send(38, this->_data, 0, true);
    if (this->recv(38, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Current_::get_max_Ibus_regen(void)
{
    float value = 0;
    this->send(39, this->_data, 0, true);
    if (this->recv(39, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_max_Ibus_regen(float value)
{
    write_le(value, this->_data);
    this->send(39, this->_data, sizeof(float), false);
}

float Current_::get_max_Ibrake(void)
{
    float value = 0;
    this->send(40, this->_data, 0, true);
    if (this->recv(40, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_max_Ibrake(float value)
{
    write_le(value, this->_data);
    this->send(40, this->_data, sizeof(float), false);
}

