/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <traj_planner.hpp>

float Traj_planner_::get_max_accel(void)
{
    float value = 0;
    this->send(59, this->_data, 0, true);
    if (this->recv(59, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Traj_planner_::set_max_accel(float value)
{
    write_le(value, this->_data);
    this->send(59, this->_data, sizeof(float), false);
}

float Traj_planner_::get_max_decel(void)
{
    float value = 0;
    this->send(60, this->_data, 0, true);
    if (this->recv(60, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Traj_planner_::set_max_decel(float value)
{
    write_le(value, this->_data);
    this->send(60, this->_data, sizeof(float), false);
}

float Traj_planner_::get_max_vel(void)
{
    float value = 0;
    this->send(61, this->_data, 0, true);
    if (this->recv(61, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Traj_planner_::set_max_vel(float value)
{
    write_le(value, this->_data);
    this->send(61, this->_data, sizeof(float), false);
}

float Traj_planner_::get_t_accel(void)
{
    float value = 0;
    this->send(62, this->_data, 0, true);
    if (this->recv(62, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Traj_planner_::set_t_accel(float value)
{
    write_le(value, this->_data);
    this->send(62, this->_data, sizeof(float), false);
}

float Traj_planner_::get_t_decel(void)
{
    float value = 0;
    this->send(63, this->_data, 0, true);
    if (this->recv(63, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Traj_planner_::set_t_decel(float value)
{
    write_le(value, this->_data);
    this->send(63, this->_data, sizeof(float), false);
}

float Traj_planner_::get_t_total(void)
{
    float value = 0;
    this->send(64, this->_data, 0, true);
    if (this->recv(64, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Traj_planner_::set_t_total(float value)
{
    write_le(value, this->_data);
    this->send(64, this->_data, sizeof(float), false);
}


void Traj_planner_::move_to(float pos_setpoint)
{
    uint8_t data_len = 0;
    write_le(pos_setpoint, this->_data + data_len);
    data_len += sizeof(pos_setpoint);

    this->send(65, this->_data, data_len, false);
}

void Traj_planner_::move_to_tlimit(float pos_setpoint)
{
    uint8_t data_len = 0;
    write_le(pos_setpoint, this->_data + data_len);
    data_len += sizeof(pos_setpoint);

    this->send(66, this->_data, data_len, false);
}
uint8_t Traj_planner_::get_errors(void)
{
    uint8_t value = 0;
    this->send(67, this->_data, 0, true);
    if (this->recv(67, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

