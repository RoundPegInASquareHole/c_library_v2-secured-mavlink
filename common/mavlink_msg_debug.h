#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE DEBUG PACKING

#define MAVLINK_MSG_ID_DEBUG 254


typedef struct __mavlink_debug_t {
 uint32_t time_boot_ms; /*< [ms] Timestamp (time since system boot).*/
 float value; /*<  DEBUG value*/
 uint8_t ind; /*<  index of debug variable*/
} mavlink_debug_t;

#define MAVLINK_MSG_ID_DEBUG_LEN 9
#define MAVLINK_MSG_ID_DEBUG_MIN_LEN 9
#define MAVLINK_MSG_ID_254_LEN 9
#define MAVLINK_MSG_ID_254_MIN_LEN 9

#define MAVLINK_MSG_ID_DEBUG_CRC 46
#define MAVLINK_MSG_ID_254_CRC 46



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_DEBUG { \
    254, \
    "DEBUG", \
    3, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_debug_t, time_boot_ms) }, \
         { "ind", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_debug_t, ind) }, \
         { "value", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_debug_t, value) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_DEBUG { \
    "DEBUG", \
    3, \
    {  { "time_boot_ms", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_debug_t, time_boot_ms) }, \
         { "ind", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_debug_t, ind) }, \
         { "value", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_debug_t, value) }, \
         } \
}
#endif

/**
 * @brief Pack a debug message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param ind  index of debug variable
 * @param value  DEBUG value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_debug_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time_boot_ms, uint8_t ind, float value)
{
    /// \todo define the key and the nonce in the algorithm file and make them accessible for this file
    // 256-bit key
    uint8_t chacha20_key[] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13,
        0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b,
        0x1c, 0x1d, 0x1e, 0x1f
    };

    // 96-bit nonce
    uint8_t nonce[] = {
        0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x4a, 
        0x00, 0x00, 0x00, 0x00
    };
    
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEBUG_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_float(buf, 4, value);
    _mav_put_uint8_t(buf, 8, ind);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DEBUG_LEN);
#else
    mavlink_debug_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.value = value;
    packet.ind = ind;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_DEBUG_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_DEBUG_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_debug_t* debug_final = (mavlink_debug_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), debug_final, MAVLINK_MSG_ID_DEBUG_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_DEBUG;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_DEBUG_MIN_LEN, MAVLINK_MSG_ID_DEBUG_LEN, MAVLINK_MSG_ID_DEBUG_CRC);
}

/**
 * @brief Pack a debug message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param ind  index of debug variable
 * @param value  DEBUG value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_debug_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time_boot_ms,uint8_t ind,float value)
{

    /// \todo define the key and the nonce in the algorithm file and make them accessible for this file
    // 256-bit key
    uint8_t chacha20_key[] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13,
        0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b,
        0x1c, 0x1d, 0x1e, 0x1f
    };

    // 96-bit nonce
    uint8_t nonce[] = {
        0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x4a, 
        0x00, 0x00, 0x00, 0x00
    };
        
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEBUG_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_float(buf, 4, value);
    _mav_put_uint8_t(buf, 8, ind);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_DEBUG_LEN);
#else
    mavlink_debug_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.value = value;
    packet.ind = ind;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_DEBUG_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_DEBUG_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_debug_t* debug_final = (mavlink_debug_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), debug_final, MAVLINK_MSG_ID_DEBUG_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_DEBUG;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_DEBUG_MIN_LEN, MAVLINK_MSG_ID_DEBUG_LEN, MAVLINK_MSG_ID_DEBUG_CRC);
}

/**
 * @brief Encode a debug struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param debug C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_debug_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_debug_t* debug)
{
    return mavlink_msg_debug_pack(system_id, component_id, msg, debug->time_boot_ms, debug->ind, debug->value);
}

/**
 * @brief Encode a debug struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param debug C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_debug_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_debug_t* debug)
{
    return mavlink_msg_debug_pack_chan(system_id, component_id, chan, msg, debug->time_boot_ms, debug->ind, debug->value);
}

/**
 * @brief Send a debug message
 * @param chan MAVLink channel to send the message
 *
 * @param time_boot_ms [ms] Timestamp (time since system boot).
 * @param ind  index of debug variable
 * @param value  DEBUG value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_debug_send(mavlink_channel_t chan, uint32_t time_boot_ms, uint8_t ind, float value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_DEBUG_LEN];
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_float(buf, 4, value);
    _mav_put_uint8_t(buf, 8, ind);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEBUG, buf, MAVLINK_MSG_ID_DEBUG_MIN_LEN, MAVLINK_MSG_ID_DEBUG_LEN, MAVLINK_MSG_ID_DEBUG_CRC);
#else
    mavlink_debug_t packet;
    packet.time_boot_ms = time_boot_ms;
    packet.value = value;
    packet.ind = ind;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEBUG, (const char *)&packet, MAVLINK_MSG_ID_DEBUG_MIN_LEN, MAVLINK_MSG_ID_DEBUG_LEN, MAVLINK_MSG_ID_DEBUG_CRC);
#endif
}

/**
 * @brief Send a debug message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_debug_send_struct(mavlink_channel_t chan, const mavlink_debug_t* debug)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_debug_send(chan, debug->time_boot_ms, debug->ind, debug->value);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEBUG, (const char *)debug, MAVLINK_MSG_ID_DEBUG_MIN_LEN, MAVLINK_MSG_ID_DEBUG_LEN, MAVLINK_MSG_ID_DEBUG_CRC);
#endif
}

#if MAVLINK_MSG_ID_DEBUG_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_debug_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time_boot_ms, uint8_t ind, float value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, time_boot_ms);
    _mav_put_float(buf, 4, value);
    _mav_put_uint8_t(buf, 8, ind);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEBUG, buf, MAVLINK_MSG_ID_DEBUG_MIN_LEN, MAVLINK_MSG_ID_DEBUG_LEN, MAVLINK_MSG_ID_DEBUG_CRC);
#else
    mavlink_debug_t *packet = (mavlink_debug_t *)msgbuf;
    packet->time_boot_ms = time_boot_ms;
    packet->value = value;
    packet->ind = ind;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_DEBUG, (const char *)packet, MAVLINK_MSG_ID_DEBUG_MIN_LEN, MAVLINK_MSG_ID_DEBUG_LEN, MAVLINK_MSG_ID_DEBUG_CRC);
#endif
}
#endif

#endif

// MESSAGE DEBUG UNPACKING


/**
 * @brief Get field time_boot_ms from debug message
 *
 * @return [ms] Timestamp (time since system boot).
 */
static inline uint32_t mavlink_msg_debug_get_time_boot_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field ind from debug message
 *
 * @return  index of debug variable
 */
static inline uint8_t mavlink_msg_debug_get_ind(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field value from debug message
 *
 * @return  DEBUG value
 */
static inline float mavlink_msg_debug_get_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a debug message into a struct
 *
 * @param msg The message to decode
 * @param debug C-struct to decode the message contents into
 */
static inline void mavlink_msg_debug_decode(const mavlink_message_t* msg, mavlink_debug_t* debug)
{
    /// \todo define the key and the nonce in the algorithm file and make them accessible for this file
    // 256-bit key
    //uint8_t chacha20_key[] = {
     //   0x00, 0x01, 0x02, 0x03,
     //   0x04, 0x05, 0x06, 0x07,
     //   0x08, 0x09, 0x0a, 0x0b,
     //   0x0c, 0x0d, 0x0e, 0x0f,
      //  0x10, 0x11, 0x12, 0x13,
      //  0x14, 0x15, 0x16, 0x17,
      //  0x18, 0x19, 0x1a, 0x1b,
     //   0x1c, 0x1d, 0x1e, 0x1f
    //};

    // 96-bit nonce
   // uint8_t nonce[] = {
    //    0x00, 0x00, 0x00, 0x00, 
   //     0x00, 0x00, 0x00, 0x4a, 
   //     0x00, 0x00, 0x00, 0x00
   // };

#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    debug->time_boot_ms = mavlink_msg_debug_get_time_boot_ms(msg);
    debug->value = mavlink_msg_debug_get_value(msg);
    debug->ind = mavlink_msg_debug_get_ind(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_DEBUG_LEN? msg->len : MAVLINK_MSG_ID_DEBUG_LEN;
    memset(debug, 0, MAVLINK_MSG_ID_DEBUG_LEN);
    memcpy(debug, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(debug, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
