/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <homing.hpp>

float Homing_::get_velocity(void)
{
    float value = 0;
    this->send(86, this->_data, 0, true);
    if (this->recv(86, this->_data, &(this->_dlc), this->delay_us_value)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Homing_::set_velocity(float value)
{
    write_le(value, this->_data);
    this->send(86, this->_data, sizeof(float), false);
}

float Homing_::get_max_homing_t(void)
{
    float value = 0;
    this->send(87, this->_data, 0, true);
    if (this->recv(87, this->_data, &(this->_dlc), this->delay_us_value)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Homing_::set_max_homing_t(float value)
{
    write_le(value, this->_data);
    this->send(87, this->_data, sizeof(float), false);
}

float Homing_::get_retract_dist(void)
{
    float value = 0;
    this->send(88, this->_data, 0, true);
    if (this->recv(88, this->_data, &(this->_dlc), this->delay_us_value)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Homing_::set_retract_dist(float value)
{
    write_le(value, this->_data);
    this->send(88, this->_data, sizeof(float), false);
}

uint8_t Homing_::get_warnings(void)
{
    uint8_t value = 0;
    this->send(89, this->_data, 0, true);
    if (this->recv(89, this->_data, &(this->_dlc), this->delay_us_value)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}


void Homing_::home()
{
    this->send(93, this->_data, 0, true);
}


