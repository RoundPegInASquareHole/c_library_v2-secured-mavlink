#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE GOPRO_GET_RESPONSE PACKING

#define MAVLINK_MSG_ID_GOPRO_GET_RESPONSE 217


typedef struct __mavlink_gopro_get_response_t {
 uint8_t cmd_id; /*<  Command ID.*/
 uint8_t status; /*<  Status.*/
 uint8_t value[4]; /*<  Value.*/
} mavlink_gopro_get_response_t;

#define MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN 6
#define MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_MIN_LEN 6
#define MAVLINK_MSG_ID_217_LEN 6
#define MAVLINK_MSG_ID_217_MIN_LEN 6

#define MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_CRC 202
#define MAVLINK_MSG_ID_217_CRC 202

#define MAVLINK_MSG_GOPRO_GET_RESPONSE_FIELD_VALUE_LEN 4

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_GOPRO_GET_RESPONSE { \
    217, \
    "GOPRO_GET_RESPONSE", \
    3, \
    {  { "cmd_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_gopro_get_response_t, cmd_id) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_gopro_get_response_t, status) }, \
         { "value", NULL, MAVLINK_TYPE_UINT8_T, 4, 2, offsetof(mavlink_gopro_get_response_t, value) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_GOPRO_GET_RESPONSE { \
    "GOPRO_GET_RESPONSE", \
    3, \
    {  { "cmd_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_gopro_get_response_t, cmd_id) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_gopro_get_response_t, status) }, \
         { "value", NULL, MAVLINK_TYPE_UINT8_T, 4, 2, offsetof(mavlink_gopro_get_response_t, value) }, \
         } \
}
#endif

/**
 * @brief Pack a gopro_get_response message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param cmd_id  Command ID.
 * @param status  Status.
 * @param value  Value.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gopro_get_response_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t cmd_id, uint8_t status, const uint8_t *value)
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
    char buf[MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN];
    _mav_put_uint8_t(buf, 0, cmd_id);
    _mav_put_uint8_t(buf, 1, status);
    _mav_put_uint8_t_array(buf, 2, value, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN);
#else
    mavlink_gopro_get_response_t packet;
    packet.cmd_id = cmd_id;
    packet.status = status;
    mav_array_memcpy(packet.value, value, sizeof(uint8_t)*4);
            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_gopro_get_response_t* gopro_get_response_final = (mavlink_gopro_get_response_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), gopro_get_response_final, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_GOPRO_GET_RESPONSE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_CRC);
}

/**
 * @brief Pack a gopro_get_response message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param cmd_id  Command ID.
 * @param status  Status.
 * @param value  Value.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gopro_get_response_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t cmd_id,uint8_t status,const uint8_t *value)
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
    char buf[MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN];
    _mav_put_uint8_t(buf, 0, cmd_id);
    _mav_put_uint8_t(buf, 1, status);
    _mav_put_uint8_t_array(buf, 2, value, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN);
#else
    mavlink_gopro_get_response_t packet;
    packet.cmd_id = cmd_id;
    packet.status = status;
    mav_array_memcpy(packet.value, value, sizeof(uint8_t)*4);
        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_gopro_get_response_t* gopro_get_response_final = (mavlink_gopro_get_response_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), gopro_get_response_final, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_GOPRO_GET_RESPONSE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_CRC);
}

/**
 * @brief Encode a gopro_get_response struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gopro_get_response C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gopro_get_response_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gopro_get_response_t* gopro_get_response)
{
    return mavlink_msg_gopro_get_response_pack(system_id, component_id, msg, gopro_get_response->cmd_id, gopro_get_response->status, gopro_get_response->value);
}

/**
 * @brief Encode a gopro_get_response struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gopro_get_response C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gopro_get_response_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gopro_get_response_t* gopro_get_response)
{
    return mavlink_msg_gopro_get_response_pack_chan(system_id, component_id, chan, msg, gopro_get_response->cmd_id, gopro_get_response->status, gopro_get_response->value);
}

/**
 * @brief Send a gopro_get_response message
 * @param chan MAVLink channel to send the message
 *
 * @param cmd_id  Command ID.
 * @param status  Status.
 * @param value  Value.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gopro_get_response_send(mavlink_channel_t chan, uint8_t cmd_id, uint8_t status, const uint8_t *value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN];
    _mav_put_uint8_t(buf, 0, cmd_id);
    _mav_put_uint8_t(buf, 1, status);
    _mav_put_uint8_t_array(buf, 2, value, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE, buf, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_CRC);
#else
    mavlink_gopro_get_response_t packet;
    packet.cmd_id = cmd_id;
    packet.status = status;
    mav_array_memcpy(packet.value, value, sizeof(uint8_t)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE, (const char *)&packet, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_CRC);
#endif
}

/**
 * @brief Send a gopro_get_response message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gopro_get_response_send_struct(mavlink_channel_t chan, const mavlink_gopro_get_response_t* gopro_get_response)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gopro_get_response_send(chan, gopro_get_response->cmd_id, gopro_get_response->status, gopro_get_response->value);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE, (const char *)gopro_get_response, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_CRC);
#endif
}

#if MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gopro_get_response_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t cmd_id, uint8_t status, const uint8_t *value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, cmd_id);
    _mav_put_uint8_t(buf, 1, status);
    _mav_put_uint8_t_array(buf, 2, value, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE, buf, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_CRC);
#else
    mavlink_gopro_get_response_t *packet = (mavlink_gopro_get_response_t *)msgbuf;
    packet->cmd_id = cmd_id;
    packet->status = status;
    mav_array_memcpy(packet->value, value, sizeof(uint8_t)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE, (const char *)packet, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_CRC);
#endif
}
#endif

#endif

// MESSAGE GOPRO_GET_RESPONSE UNPACKING


/**
 * @brief Get field cmd_id from gopro_get_response message
 *
 * @return  Command ID.
 */
static inline uint8_t mavlink_msg_gopro_get_response_get_cmd_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field status from gopro_get_response message
 *
 * @return  Status.
 */
static inline uint8_t mavlink_msg_gopro_get_response_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field value from gopro_get_response message
 *
 * @return  Value.
 */
static inline uint16_t mavlink_msg_gopro_get_response_get_value(const mavlink_message_t* msg, uint8_t *value)
{
    return _MAV_RETURN_uint8_t_array(msg, value, 4,  2);
}

/**
 * @brief Decode a gopro_get_response message into a struct
 *
 * @param msg The message to decode
 * @param gopro_get_response C-struct to decode the message contents into
 */
static inline void mavlink_msg_gopro_get_response_decode(const mavlink_message_t* msg, mavlink_gopro_get_response_t* gopro_get_response)
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
    gopro_get_response->cmd_id = mavlink_msg_gopro_get_response_get_cmd_id(msg);
    gopro_get_response->status = mavlink_msg_gopro_get_response_get_status(msg);
    mavlink_msg_gopro_get_response_get_value(msg, gopro_get_response->value);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN? msg->len : MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN;
    memset(gopro_get_response, 0, MAVLINK_MSG_ID_GOPRO_GET_RESPONSE_LEN);
    memcpy(gopro_get_response, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(gopro_get_response, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
