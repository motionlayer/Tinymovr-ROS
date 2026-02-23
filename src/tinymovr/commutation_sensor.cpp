/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <commutation_sensor.hpp>

uint8_t Commutation_sensor_::get_connection(void)
{
    uint8_t value = 0;
    this->send(75, this->_data, 0, true);
    if (this->recv(75, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Commutation_sensor_::set_connection(uint8_t value)
{
    write_le(value, this->_data);
    this->send(75, this->_data, sizeof(uint8_t), false);
}

float Commutation_sensor_::get_bandwidth(void)
{
    float value = 0;
    this->send(76, this->_data, 0, true);
    if (this->recv(76, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Commutation_sensor_::set_bandwidth(float value)
{
    write_le(value, this->_data);
    this->send(76, this->_data, sizeof(float), false);
}

int32_t Commutation_sensor_::get_raw_angle(void)
{
    int32_t value = 0;
    this->send(77, this->_data, 0, true);
    if (this->recv(77, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Commutation_sensor_::get_position_estimate(void)
{
    float value = 0;
    this->send(78, this->_data, 0, true);
    if (this->recv(78, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Commutation_sensor_::get_velocity_estimate(void)
{
    float value = 0;
    this->send(79, this->_data, 0, true);
    if (this->recv(79, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

