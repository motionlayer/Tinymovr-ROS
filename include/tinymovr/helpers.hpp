/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#if defined ARDUINO || __cplusplus < 201103L
#include <stdint.h>
#include <stddef.h>
#else
#include <cstdint>
#include <cstddef>
#include <cstring>
#endif

#if defined ARDUINO
#include "Arduino.h"
#endif

#define CAN_EP_SIZE (12)
#define CAN_EP_MASK ((1UL << CAN_EP_SIZE) - 1)
#define CAN_SEQ_SIZE (9)
#define CAN_SEQ_MASK (((1UL << CAN_SEQ_SIZE) - 1) << CAN_EP_SIZE)
#define CAN_DEV_SIZE (8)
#define CAN_DEV_MASK (((1UL << CAN_DEV_SIZE) - 1) << (CAN_EP_SIZE + CAN_SEQ_SIZE))

typedef void (*send_callback)(uint32_t arbitration_id, uint8_t *data, uint8_t dlc, bool rtr);
typedef bool (*recv_callback)(uint32_t *arbitration_id, uint8_t *data, uint8_t *dlc);
typedef void (*delay_us_callback)(uint32_t us);

class Node {
    public:

    Node(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb, delay_us_callback _delay_us_cb, uint32_t _delay_us_value):
        can_node_id(_can_node_id), send_cb(_send_cb), recv_cb(_recv_cb), delay_us_cb(_delay_us_cb), delay_us_value(_delay_us_value) {}

    protected:
    uint8_t can_node_id;
    send_callback send_cb;
    recv_callback recv_cb;
    delay_us_callback delay_us_cb;
    uint32_t delay_us_value;
    uint8_t _data[8];
    uint8_t _dlc;
    uint32_t get_arbitration_id(uint32_t cmd_id)
    {
        return ((((uint32_t)this->can_node_id) << (CAN_EP_SIZE + CAN_SEQ_SIZE)) & CAN_DEV_MASK) | (cmd_id & CAN_EP_MASK);
    }
    void send(uint32_t cmd_id, uint8_t *data, uint8_t data_size, bool rtr)
    {
        const uint32_t arb_id = this->get_arbitration_id(cmd_id);
        this->send_cb(arb_id, data, data_size, rtr);
    }

    bool recv(uint32_t cmd_id, uint8_t *data, uint8_t *data_size, uint16_t delay_us)
    {
        uint32_t _arbitration_id;
        uint8_t _data[8];
        uint8_t _data_size;
        // A delay of a few 100s of us needs to be inserted
        // to ensure the response has been transmitted.
        // TODO: Better handle this using an interrupt.
        if (delay_us > 0)
        {
           this->delay_us_cb(delay_us);
        }
        const uint32_t arb_id = this->get_arbitration_id(cmd_id);
        while (this->recv_cb(&_arbitration_id, _data, &_data_size))
        {
            if (_arbitration_id == arb_id)
            {
                memcpy(data, _data, _data_size);
                *data_size = _data_size;
                return true;
            }
        }
        return false;
    }
};

template<typename T>
inline size_t write_le(T value, uint8_t* buffer);

template<typename T>
inline size_t read_le(T* value, const uint8_t* buffer);

template<>
inline size_t write_le<bool>(bool value, uint8_t* buffer) {
    buffer[0] = value ? 1 : 0;
    return 1;
}

template<>
inline size_t write_le<uint8_t>(uint8_t value, uint8_t* buffer) {
    buffer[0] = value;
    return 1;
}

template<>
inline size_t write_le<int8_t>(int8_t value, uint8_t* buffer) {
    buffer[0] = value;
    return 1;
}

template<>
inline size_t write_le<uint16_t>(uint16_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    return 2;
}

template<>
inline size_t write_le<int16_t>(int16_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    return 2;
}

template<>
inline size_t write_le<uint32_t>(uint32_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    buffer[2] = (value >> 16) & 0xff;
    buffer[3] = (value >> 24) & 0xff;
    return 4;
}

template<>
inline size_t write_le<int32_t>(int32_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    buffer[2] = (value >> 16) & 0xff;
    buffer[3] = (value >> 24) & 0xff;
    return 4;
}

template<>
inline size_t write_le<uint64_t>(uint64_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    buffer[2] = (value >> 16) & 0xff;
    buffer[3] = (value >> 24) & 0xff;
    buffer[4] = (value >> 32) & 0xff;
    buffer[5] = (value >> 40) & 0xff;
    buffer[6] = (value >> 48) & 0xff;
    buffer[7] = (value >> 56) & 0xff;
    return 8;
}

template<>
inline size_t write_le<float>(float value, uint8_t* buffer) {
    //static_assert(CHAR_BIT * sizeof(float) == 32, "32 bit floating point expected");
    //static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 floating point expected");
    const uint32_t * value_as_uint32 = reinterpret_cast<const uint32_t*>(&value);
    return write_le<uint32_t>(*value_as_uint32, buffer);
}

template<>
inline size_t read_le<bool>(bool* value, const uint8_t* buffer) {
    *value = buffer[0];
    return 1;
}

template<>
inline size_t read_le<uint8_t>(uint8_t* value, const uint8_t* buffer) {
    *value = buffer[0];
    return 1;
}

template<>
inline size_t read_le<int8_t>(int8_t* value, const uint8_t* buffer) {
    *value = buffer[0];
    return 1;
}

template<>
inline size_t read_le<uint16_t>(uint16_t* value, const uint8_t* buffer) {
    *value = (static_cast<uint16_t>(buffer[0]) << 0) |
             (static_cast<uint16_t>(buffer[1]) << 8);
    return 2;
}

template<>
inline size_t read_le<int16_t>(int16_t* value, const uint8_t* buffer) {
    *value = (static_cast<uint16_t>(buffer[0]) << 0) |
             (static_cast<uint16_t>(buffer[1]) << 8);
    return 2;
}

template<>
inline size_t read_le<int32_t>(int32_t* value, const uint8_t* buffer) {
    *value = (static_cast<int32_t>(buffer[0]) << 0) |
             (static_cast<int32_t>(buffer[1]) << 8) |
             (static_cast<int32_t>(buffer[2]) << 16) |
             (static_cast<int32_t>(buffer[3]) << 24);
    return 4;
}

template<>
inline size_t read_le<uint32_t>(uint32_t* value, const uint8_t* buffer) {
    *value = (static_cast<uint32_t>(buffer[0]) << 0) |
             (static_cast<uint32_t>(buffer[1]) << 8) |
             (static_cast<uint32_t>(buffer[2]) << 16) |
             (static_cast<uint32_t>(buffer[3]) << 24);
    return 4;
}

template<>
inline size_t read_le<uint64_t>(uint64_t* value, const uint8_t* buffer) {
    *value = (static_cast<uint64_t>(buffer[0]) << 0) |
             (static_cast<uint64_t>(buffer[1]) << 8) |
             (static_cast<uint64_t>(buffer[2]) << 16) |
             (static_cast<uint64_t>(buffer[3]) << 24) |
             (static_cast<uint64_t>(buffer[4]) << 32) |
             (static_cast<uint64_t>(buffer[5]) << 40) |
             (static_cast<uint64_t>(buffer[6]) << 48) |
             (static_cast<uint64_t>(buffer[7]) << 56);
    return 8;
}

template<>
inline size_t read_le<float>(float* value, const uint8_t* buffer) {
    return read_le(reinterpret_cast<uint32_t*>(value), buffer);
}

// @brief Reads a value of type T from the buffer.
// @param buffer    Pointer to the buffer to be read. The pointer is updated by the number of bytes that were read.
// @param length    The number of available bytes in buffer. This value is updated to subtract the bytes that were read.
template<typename T>
static inline T read_le(const uint8_t** buffer, size_t* length) {
    T result;
    size_t cnt = read_le(&result, *buffer);
    *buffer += cnt;
    *length -= cnt;
    return result;
}
