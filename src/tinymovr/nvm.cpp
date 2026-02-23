/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <nvm.hpp>

uint8_t Nvm_::get_num_slots(void)
{
    uint8_t value = 0;
    this->send(13, this->_data, 0, true);
    if (this->recv(13, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t Nvm_::get_current_slot(void)
{
    uint8_t value = 0;
    this->send(14, this->_data, 0, true);
    if (this->recv(14, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint32_t Nvm_::get_write_count(void)
{
    uint32_t value = 0;
    this->send(15, this->_data, 0, true);
    if (this->recv(15, this->_data, &(this->_dlc), this->delay_us_value))
    {
        read_le(&value, this->_data);
    }
    return value;
}

