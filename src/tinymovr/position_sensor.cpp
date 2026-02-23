/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <position_sensor.hpp>

uint8_t Position_sensor_::get_connection(void)
{
    uint8_t value = 0;
    this->send(70, this->_data, 0, true);
    if (this->recv(70, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Position_sensor_::set_connection(uint8_t value)
{
    write_le(value, this->_data);
    this->send(70, this->_data, sizeof(uint8_t), false);
}

float Position_sensor_::get_bandwidth(void)
{
    float value = 0;
    this->send(71, this->_data, 0, true);
    if (this->recv(71, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Position_sensor_::set_bandwidth(float value)
{
    write_le(value, this->_data);
    this->send(71, this->_data, sizeof(float), false);
}

int32_t Position_sensor_::get_raw_angle(void)
{
    int32_t value = 0;
    this->send(72, this->_data, 0, true);
    if (this->recv(72, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Position_sensor_::get_position_estimate(void)
{
    float value = 0;
    this->send(73, this->_data, 0, true);
    if (this->recv(73, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Position_sensor_::get_velocity_estimate(void)
{
    float value = 0;
    this->send(74, this->_data, 0, true);
    if (this->recv(74, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

