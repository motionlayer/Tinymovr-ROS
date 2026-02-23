/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <user_frame.hpp>

float User_frame_::get_position_estimate(void)
{
    float value = 0;
    this->send(58, this->_data, 0, true);
    if (this->recv(58, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float User_frame_::get_velocity_estimate(void)
{
    float value = 0;
    this->send(59, this->_data, 0, true);
    if (this->recv(59, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float User_frame_::get_offset(void)
{
    float value = 0;
    this->send(60, this->_data, 0, true);
    if (this->recv(60, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void User_frame_::set_offset(float value)
{
    write_le(value, this->_data);
    this->send(60, this->_data, sizeof(float), false);
}

float User_frame_::get_multiplier(void)
{
    float value = 0;
    this->send(61, this->_data, 0, true);
    if (this->recv(61, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void User_frame_::set_multiplier(float value)
{
    write_le(value, this->_data);
    this->send(61, this->_data, sizeof(float), false);
}

