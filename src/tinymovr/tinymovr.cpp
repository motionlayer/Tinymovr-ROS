/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/
#include <tinymovr.hpp>
uint32_t Tinymovr::get_protocol_hash(void)
{
    uint32_t value = 0;
    this->send(0, this->_data, 0, true);
    if (this->recv(0, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
uint32_t Tinymovr::get_uid(void)
{
    uint32_t value = 0;
    this->send(1, this->_data, 0, true);
    if (this->recv(1, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
void Tinymovr::get_fw_version(char out_value[])
{
    this->send(2, this->_data, 0, true);
    this->_dlc = 0;
    if (this->recv(2, this->_data, &(this->_dlc), this->delay_us_value))
    {
        memcpy(out_value, this->_data, this->_dlc);
    }
}
uint32_t Tinymovr::get_hw_revision(void)
{
    uint32_t value = 0;
    this->send(3, this->_data, 0, true);
    if (this->recv(3, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
float Tinymovr::get_Vbus(void)
{
    float value = 0;
    this->send(4, this->_data, 0, true);
    if (this->recv(4, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
float Tinymovr::get_Ibus(void)
{
    float value = 0;
    this->send(5, this->_data, 0, true);
    if (this->recv(5, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
float Tinymovr::get_power(void)
{
    float value = 0;
    this->send(6, this->_data, 0, true);
    if (this->recv(6, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
float Tinymovr::get_temp(void)
{
    float value = 0;
    this->send(7, this->_data, 0, true);
    if (this->recv(7, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
bool Tinymovr::get_calibrated(void)
{
    bool value = 0;
    this->send(8, this->_data, 0, true);
    if (this->recv(8, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
uint8_t Tinymovr::get_errors(void)
{
    uint8_t value = 0;
    this->send(9, this->_data, 0, true);
    if (this->recv(9, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
uint8_t Tinymovr::get_warnings(void)
{
    uint8_t value = 0;
    this->send(10, this->_data, 0, true);
    if (this->recv(10, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Tinymovr::save_config()
{
    this->send(11, this->_data, 0, true);
}

void Tinymovr::erase_config()
{
    this->send(12, this->_data, 0, true);
}

void Tinymovr::reset()
{
    this->send(16, this->_data, 0, true);
}

void Tinymovr::enter_dfu()
{
    this->send(17, this->_data, 0, true);
}
uint32_t Tinymovr::get_config_size(void)
{
    uint32_t value = 0;
    this->send(18, this->_data, 0, true);
    if (this->recv(18, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}
