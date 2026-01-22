/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <encoder.hpp>

float Encoder_::get_position_estimate(void)
{
    float value = 0;
    this->send(53, this->_data, 0, true);
    if (this->recv(53, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Encoder_::get_velocity_estimate(void)
{
    float value = 0;
    this->send(54, this->_data, 0, true);
    if (this->recv(54, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t Encoder_::get_type(void)
{
    uint8_t value = 0;
    this->send(55, this->_data, 0, true);
    if (this->recv(55, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Encoder_::set_type(uint8_t value)
{
    write_le(value, this->_data);
    this->send(55, this->_data, sizeof(uint8_t), false);
}

float Encoder_::get_bandwidth(void)
{
    float value = 0;
    this->send(56, this->_data, 0, true);
    if (this->recv(56, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Encoder_::set_bandwidth(float value)
{
    write_le(value, this->_data);
    this->send(56, this->_data, sizeof(float), false);
}

bool Encoder_::get_calibrated(void)
{
    bool value = 0;
    this->send(57, this->_data, 0, true);
    if (this->recv(57, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t Encoder_::get_errors(void)
{
    uint8_t value = 0;
    this->send(58, this->_data, 0, true);
    if (this->recv(58, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

