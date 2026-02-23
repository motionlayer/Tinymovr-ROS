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
    this->send(51, this->_data, 0, true);
    if (this->recv(51, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_R(float value)
{
    write_le(value, this->_data);
    this->send(51, this->_data, sizeof(float), false);
}

float Motor_::get_L(void)
{
    float value = 0;
    this->send(52, this->_data, 0, true);
    if (this->recv(52, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_L(float value)
{
    write_le(value, this->_data);
    this->send(52, this->_data, sizeof(float), false);
}

uint8_t Motor_::get_pole_pairs(void)
{
    uint8_t value = 0;
    this->send(53, this->_data, 0, true);
    if (this->recv(53, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_pole_pairs(uint8_t value)
{
    write_le(value, this->_data);
    this->send(53, this->_data, sizeof(uint8_t), false);
}

uint8_t Motor_::get_type(void)
{
    uint8_t value = 0;
    this->send(54, this->_data, 0, true);
    if (this->recv(54, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_type(uint8_t value)
{
    write_le(value, this->_data);
    this->send(54, this->_data, sizeof(uint8_t), false);
}

bool Motor_::get_calibrated(void)
{
    bool value = 0;
    this->send(55, this->_data, 0, true);
    if (this->recv(55, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Motor_::get_I_cal(void)
{
    float value = 0;
    this->send(56, this->_data, 0, true);
    if (this->recv(56, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Motor_::set_I_cal(float value)
{
    write_le(value, this->_data);
    this->send(56, this->_data, sizeof(float), false);
}

uint8_t Motor_::get_errors(void)
{
    uint8_t value = 0;
    this->send(57, this->_data, 0, true);
    if (this->recv(57, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

