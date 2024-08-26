#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE LOGGING_DATA_ACKED PACKING

#define MAVLINK_MSG_ID_LOGGING_DATA_ACKED 267


typedef struct __mavlink_logging_data_acked_t {
 uint16_t sequence; /*<  sequence number (can wrap)*/
 uint8_t target_system; /*<  system ID of the target*/
 uint8_t target_component; /*<  component ID of the target*/
 uint8_t length; /*< [bytes] data length*/
 uint8_t first_message_offset; /*< [bytes] offset into data where first message starts. This can be used for recovery, when a previous message got lost (set to UINT8_MAX if no start exists).*/
 uint8_t data[249]; /*<  logged data*/
} mavlink_logging_data_acked_t;

#define MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN 255
#define MAVLINK_MSG_ID_LOGGING_DATA_ACKED_MIN_LEN 255
#define MAVLINK_MSG_ID_267_LEN 255
#define MAVLINK_MSG_ID_267_MIN_LEN 255

#define MAVLINK_MSG_ID_LOGGING_DATA_ACKED_CRC 35
#define MAVLINK_MSG_ID_267_CRC 35

#define MAVLINK_MSG_LOGGING_DATA_ACKED_FIELD_DATA_LEN 249

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LOGGING_DATA_ACKED { \
    267, \
    "LOGGING_DATA_ACKED", \
    6, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_logging_data_acked_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_logging_data_acked_t, target_component) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_logging_data_acked_t, sequence) }, \
         { "length", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_logging_data_acked_t, length) }, \
         { "first_message_offset", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_logging_data_acked_t, first_message_offset) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 249, 6, offsetof(mavlink_logging_data_acked_t, data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LOGGING_DATA_ACKED { \
    "LOGGING_DATA_ACKED", \
    6, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_logging_data_acked_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_logging_data_acked_t, target_component) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_logging_data_acked_t, sequence) }, \
         { "length", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_logging_data_acked_t, length) }, \
         { "first_message_offset", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_logging_data_acked_t, first_message_offset) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 249, 6, offsetof(mavlink_logging_data_acked_t, data) }, \
         } \
}
#endif

/**
 * @brief Pack a logging_data_acked message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  system ID of the target
 * @param target_component  component ID of the target
 * @param sequence  sequence number (can wrap)
 * @param length [bytes] data length
 * @param first_message_offset [bytes] offset into data where first message starts. This can be used for recovery, when a previous message got lost (set to UINT8_MAX if no start exists).
 * @param data  logged data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_logging_data_acked_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint16_t sequence, uint8_t length, uint8_t first_message_offset, const uint8_t *data)
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
    char buf[MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN];
    _mav_put_uint16_t(buf, 0, sequence);
    _mav_put_uint8_t(buf, 2, target_system);
    _mav_put_uint8_t(buf, 3, target_component);
    _mav_put_uint8_t(buf, 4, length);
    _mav_put_uint8_t(buf, 5, first_message_offset);
    _mav_put_uint8_t_array(buf, 6, data, 249);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN);
#else
    mavlink_logging_data_acked_t packet;
    packet.sequence = sequence;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.length = length;
    packet.first_message_offset = first_message_offset;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*249);
            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_logging_data_acked_t* logging_data_acked_final = (mavlink_logging_data_acked_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), logging_data_acked_final, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_LOGGING_DATA_ACKED;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_MIN_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_CRC);
}

/**
 * @brief Pack a logging_data_acked message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  system ID of the target
 * @param target_component  component ID of the target
 * @param sequence  sequence number (can wrap)
 * @param length [bytes] data length
 * @param first_message_offset [bytes] offset into data where first message starts. This can be used for recovery, when a previous message got lost (set to UINT8_MAX if no start exists).
 * @param data  logged data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_logging_data_acked_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint16_t sequence,uint8_t length,uint8_t first_message_offset,const uint8_t *data)
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
    char buf[MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN];
    _mav_put_uint16_t(buf, 0, sequence);
    _mav_put_uint8_t(buf, 2, target_system);
    _mav_put_uint8_t(buf, 3, target_component);
    _mav_put_uint8_t(buf, 4, length);
    _mav_put_uint8_t(buf, 5, first_message_offset);
    _mav_put_uint8_t_array(buf, 6, data, 249);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN);
#else
    mavlink_logging_data_acked_t packet;
    packet.sequence = sequence;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.length = length;
    packet.first_message_offset = first_message_offset;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*249);
        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_logging_data_acked_t* logging_data_acked_final = (mavlink_logging_data_acked_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), logging_data_acked_final, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_LOGGING_DATA_ACKED;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_MIN_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_CRC);
}

/**
 * @brief Encode a logging_data_acked struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param logging_data_acked C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_logging_data_acked_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_logging_data_acked_t* logging_data_acked)
{
    return mavlink_msg_logging_data_acked_pack(system_id, component_id, msg, logging_data_acked->target_system, logging_data_acked->target_component, logging_data_acked->sequence, logging_data_acked->length, logging_data_acked->first_message_offset, logging_data_acked->data);
}

/**
 * @brief Encode a logging_data_acked struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param logging_data_acked C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_logging_data_acked_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_logging_data_acked_t* logging_data_acked)
{
    return mavlink_msg_logging_data_acked_pack_chan(system_id, component_id, chan, msg, logging_data_acked->target_system, logging_data_acked->target_component, logging_data_acked->sequence, logging_data_acked->length, logging_data_acked->first_message_offset, logging_data_acked->data);
}

/**
 * @brief Send a logging_data_acked message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  system ID of the target
 * @param target_component  component ID of the target
 * @param sequence  sequence number (can wrap)
 * @param length [bytes] data length
 * @param first_message_offset [bytes] offset into data where first message starts. This can be used for recovery, when a previous message got lost (set to UINT8_MAX if no start exists).
 * @param data  logged data
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_logging_data_acked_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t sequence, uint8_t length, uint8_t first_message_offset, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN];
    _mav_put_uint16_t(buf, 0, sequence);
    _mav_put_uint8_t(buf, 2, target_system);
    _mav_put_uint8_t(buf, 3, target_component);
    _mav_put_uint8_t(buf, 4, length);
    _mav_put_uint8_t(buf, 5, first_message_offset);
    _mav_put_uint8_t_array(buf, 6, data, 249);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOGGING_DATA_ACKED, buf, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_MIN_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_CRC);
#else
    mavlink_logging_data_acked_t packet;
    packet.sequence = sequence;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.length = length;
    packet.first_message_offset = first_message_offset;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*249);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOGGING_DATA_ACKED, (const char *)&packet, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_MIN_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_CRC);
#endif
}

/**
 * @brief Send a logging_data_acked message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_logging_data_acked_send_struct(mavlink_channel_t chan, const mavlink_logging_data_acked_t* logging_data_acked)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_logging_data_acked_send(chan, logging_data_acked->target_system, logging_data_acked->target_component, logging_data_acked->sequence, logging_data_acked->length, logging_data_acked->first_message_offset, logging_data_acked->data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOGGING_DATA_ACKED, (const char *)logging_data_acked, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_MIN_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_CRC);
#endif
}

#if MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_logging_data_acked_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint16_t sequence, uint8_t length, uint8_t first_message_offset, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, sequence);
    _mav_put_uint8_t(buf, 2, target_system);
    _mav_put_uint8_t(buf, 3, target_component);
    _mav_put_uint8_t(buf, 4, length);
    _mav_put_uint8_t(buf, 5, first_message_offset);
    _mav_put_uint8_t_array(buf, 6, data, 249);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOGGING_DATA_ACKED, buf, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_MIN_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_CRC);
#else
    mavlink_logging_data_acked_t *packet = (mavlink_logging_data_acked_t *)msgbuf;
    packet->sequence = sequence;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->length = length;
    packet->first_message_offset = first_message_offset;
    mav_array_memcpy(packet->data, data, sizeof(uint8_t)*249);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOGGING_DATA_ACKED, (const char *)packet, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_MIN_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_CRC);
#endif
}
#endif

#endif

// MESSAGE LOGGING_DATA_ACKED UNPACKING


/**
 * @brief Get field target_system from logging_data_acked message
 *
 * @return  system ID of the target
 */
static inline uint8_t mavlink_msg_logging_data_acked_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field target_component from logging_data_acked message
 *
 * @return  component ID of the target
 */
static inline uint8_t mavlink_msg_logging_data_acked_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field sequence from logging_data_acked message
 *
 * @return  sequence number (can wrap)
 */
static inline uint16_t mavlink_msg_logging_data_acked_get_sequence(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field length from logging_data_acked message
 *
 * @return [bytes] data length
 */
static inline uint8_t mavlink_msg_logging_data_acked_get_length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field first_message_offset from logging_data_acked message
 *
 * @return [bytes] offset into data where first message starts. This can be used for recovery, when a previous message got lost (set to UINT8_MAX if no start exists).
 */
static inline uint8_t mavlink_msg_logging_data_acked_get_first_message_offset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field data from logging_data_acked message
 *
 * @return  logged data
 */
static inline uint16_t mavlink_msg_logging_data_acked_get_data(const mavlink_message_t* msg, uint8_t *data)
{
    return _MAV_RETURN_uint8_t_array(msg, data, 249,  6);
}

/**
 * @brief Decode a logging_data_acked message into a struct
 *
 * @param msg The message to decode
 * @param logging_data_acked C-struct to decode the message contents into
 */
static inline void mavlink_msg_logging_data_acked_decode(const mavlink_message_t* msg, mavlink_logging_data_acked_t* logging_data_acked)
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
    logging_data_acked->sequence = mavlink_msg_logging_data_acked_get_sequence(msg);
    logging_data_acked->target_system = mavlink_msg_logging_data_acked_get_target_system(msg);
    logging_data_acked->target_component = mavlink_msg_logging_data_acked_get_target_component(msg);
    logging_data_acked->length = mavlink_msg_logging_data_acked_get_length(msg);
    logging_data_acked->first_message_offset = mavlink_msg_logging_data_acked_get_first_message_offset(msg);
    mavlink_msg_logging_data_acked_get_data(msg, logging_data_acked->data);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN? msg->len : MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN;
    memset(logging_data_acked, 0, MAVLINK_MSG_ID_LOGGING_DATA_ACKED_LEN);
    memcpy(logging_data_acked, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(logging_data_acked, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
