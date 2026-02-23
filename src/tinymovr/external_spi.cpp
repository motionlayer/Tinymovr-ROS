/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <external_spi.hpp>

uint8_t External_spi_::get_type(void)
{
    uint8_t value = 0;
    this->send(64, this->_data, 0, true);
    if (this->recv(64, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void External_spi_::set_type(uint8_t value)
{
    write_le(value, this->_data);
    this->send(64, this->_data, sizeof(uint8_t), false);
}

uint8_t External_spi_::get_rate(void)
{
    uint8_t value = 0;
    this->send(65, this->_data, 0, true);
    if (this->recv(65, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

void External_spi_::set_rate(uint8_t value)
{
    write_le(value, this->_data);
    this->send(65, this->_data, sizeof(uint8_t), false);
}

bool External_spi_::get_calibrated(void)
{
    bool value = 0;
    this->send(66, this->_data, 0, true);
    if (this->recv(66, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t External_spi_::get_errors(void)
{
    uint8_t value = 0;
    this->send(67, this->_data, 0, true);
    if (this->recv(67, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

