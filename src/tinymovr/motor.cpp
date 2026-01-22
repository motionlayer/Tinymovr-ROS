/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <motor.hpp>

float Motor_::get_R(void)
{
    float value = 0;
    this->send(44, this->_data, 0, true);
    if (this->recv(44, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_R(float value)
{
    write_le(value, this->_data);
    this->send(44, this->_data, sizeof(float), false);
}

float Motor_::get_L(void)
{
    float value = 0;
    this->send(45, this->_data, 0, true);
    if (this->recv(45, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_L(float value)
{
    write_le(value, this->_data);
    this->send(45, this->_data, sizeof(float), false);
}

uint8_t Motor_::get_pole_pairs(void)
{
    uint8_t value = 0;
    this->send(46, this->_data, 0, true);
    if (this->recv(46, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_pole_pairs(uint8_t value)
{
    write_le(value, this->_data);
    this->send(46, this->_data, sizeof(uint8_t), false);
}

uint8_t Motor_::get_type(void)
{
    uint8_t value = 0;
    this->send(47, this->_data, 0, true);
    if (this->recv(47, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_type(uint8_t value)
{
    write_le(value, this->_data);
    this->send(47, this->_data, sizeof(uint8_t), false);
}

float Motor_::get_offset(void)
{
    float value = 0;
    this->send(48, this->_data, 0, true);
    if (this->recv(48, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_offset(float value)
{
    write_le(value, this->_data);
    this->send(48, this->_data, sizeof(float), false);
}

int8_t Motor_::get_direction(void)
{
    int8_t value = 0;
    this->send(49, this->_data, 0, true);
    if (this->recv(49, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_direction(int8_t value)
{
    write_le(value, this->_data);
    this->send(49, this->_data, sizeof(int8_t), false);
}

bool Motor_::get_calibrated(void)
{
    bool value = 0;
    this->send(50, this->_data, 0, true);
    if (this->recv(50, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Motor_::get_I_cal(void)
{
    float value = 0;
    this->send(51, this->_data, 0, true);
    if (this->recv(51, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_I_cal(float value)
{
    write_le(value, this->_data);
    this->send(51, this->_data, sizeof(float), false);
}

uint8_t Motor_::get_errors(void)
{
    uint8_t value = 0;
    this->send(52, this->_data, 0, true);
    if (this->recv(52, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

