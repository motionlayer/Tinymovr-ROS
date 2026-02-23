/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <controller.hpp>

uint8_t Controller_::get_state(void)
{
    uint8_t value = 0;
    this->send(21, this->_data, 0, true);
    if (this->recv(21, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Controller_::set_state(uint8_t value)
{
    write_le(value, this->_data);
    this->send(21, this->_data, sizeof(uint8_t), false);
}

uint8_t Controller_::get_mode(void)
{
    uint8_t value = 0;
    this->send(22, this->_data, 0, true);
    if (this->recv(22, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Controller_::set_mode(uint8_t value)
{
    write_le(value, this->_data);
    this->send(22, this->_data, sizeof(uint8_t), false);
}

uint8_t Controller_::get_warnings(void)
{
    uint8_t value = 0;
    this->send(23, this->_data, 0, true);
    if (this->recv(23, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t Controller_::get_errors(void)
{
    uint8_t value = 0;
    this->send(24, this->_data, 0, true);
    if (this->recv(24, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}


void Controller_::calibrate()
{
    this->send(42, this->_data, 0, true);
}

void Controller_::idle()
{
    this->send(43, this->_data, 0, true);
}

void Controller_::position_mode()
{
    this->send(44, this->_data, 0, true);
}

void Controller_::velocity_mode()
{
    this->send(45, this->_data, 0, true);
}

void Controller_::current_mode()
{
    this->send(46, this->_data, 0, true);
}

float Controller_::set_pos_vel_setpoints(float pos_setpoint, float vel_setpoint)
{
    uint8_t data_len = 0;
    write_le(pos_setpoint, this->_data + data_len);
    data_len += sizeof(pos_setpoint);
    write_le(vel_setpoint, this->_data + data_len);
    data_len += sizeof(vel_setpoint);

    this->send(47, this->_data, data_len, false);
    float value = 0;
    this->send(17, this->_data, 0, true);
    if (this->recv(17, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
