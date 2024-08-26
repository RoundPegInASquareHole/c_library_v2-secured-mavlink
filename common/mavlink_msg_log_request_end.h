#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE LOG_REQUEST_END PACKING

#define MAVLINK_MSG_ID_LOG_REQUEST_END 122


typedef struct __mavlink_log_request_end_t {
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
} mavlink_log_request_end_t;

#define MAVLINK_MSG_ID_LOG_REQUEST_END_LEN 2
#define MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN 2
#define MAVLINK_MSG_ID_122_LEN 2
#define MAVLINK_MSG_ID_122_MIN_LEN 2

#define MAVLINK_MSG_ID_LOG_REQUEST_END_CRC 203
#define MAVLINK_MSG_ID_122_CRC 203



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LOG_REQUEST_END { \
    122, \
    "LOG_REQUEST_END", \
    2, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_log_request_end_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_log_request_end_t, target_component) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LOG_REQUEST_END { \
    "LOG_REQUEST_END", \
    2, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_log_request_end_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_log_request_end_t, target_component) }, \
         } \
}
#endif

/**
 * @brief Pack a log_request_end message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_log_request_end_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component)
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
    char buf[MAVLINK_MSG_ID_LOG_REQUEST_END_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN);
#else
    mavlink_log_request_end_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_LOG_REQUEST_END_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_log_request_end_t* log_request_end_final = (mavlink_log_request_end_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), log_request_end_final, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_LOG_REQUEST_END;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_CRC);
}

/**
 * @brief Pack a log_request_end message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_log_request_end_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component)
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
    char buf[MAVLINK_MSG_ID_LOG_REQUEST_END_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN);
#else
    mavlink_log_request_end_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_LOG_REQUEST_END_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_log_request_end_t* log_request_end_final = (mavlink_log_request_end_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), log_request_end_final, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_LOG_REQUEST_END;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_CRC);
}

/**
 * @brief Encode a log_request_end struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param log_request_end C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_log_request_end_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_log_request_end_t* log_request_end)
{
    return mavlink_msg_log_request_end_pack(system_id, component_id, msg, log_request_end->target_system, log_request_end->target_component);
}

/**
 * @brief Encode a log_request_end struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param log_request_end C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_log_request_end_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_log_request_end_t* log_request_end)
{
    return mavlink_msg_log_request_end_pack_chan(system_id, component_id, chan, msg, log_request_end->target_system, log_request_end->target_component);
}

/**
 * @brief Send a log_request_end message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_log_request_end_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LOG_REQUEST_END_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_REQUEST_END, buf, MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_CRC);
#else
    mavlink_log_request_end_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_REQUEST_END, (const char *)&packet, MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_CRC);
#endif
}

/**
 * @brief Send a log_request_end message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_log_request_end_send_struct(mavlink_channel_t chan, const mavlink_log_request_end_t* log_request_end)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_log_request_end_send(chan, log_request_end->target_system, log_request_end->target_component);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_REQUEST_END, (const char *)log_request_end, MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_CRC);
#endif
}

#if MAVLINK_MSG_ID_LOG_REQUEST_END_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_log_request_end_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_REQUEST_END, buf, MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_CRC);
#else
    mavlink_log_request_end_t *packet = (mavlink_log_request_end_t *)msgbuf;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LOG_REQUEST_END, (const char *)packet, MAVLINK_MSG_ID_LOG_REQUEST_END_MIN_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN, MAVLINK_MSG_ID_LOG_REQUEST_END_CRC);
#endif
}
#endif

#endif

// MESSAGE LOG_REQUEST_END UNPACKING


/**
 * @brief Get field target_system from log_request_end message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_log_request_end_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from log_request_end message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_log_request_end_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a log_request_end message into a struct
 *
 * @param msg The message to decode
 * @param log_request_end C-struct to decode the message contents into
 */
static inline void mavlink_msg_log_request_end_decode(const mavlink_message_t* msg, mavlink_log_request_end_t* log_request_end)
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
    log_request_end->target_system = mavlink_msg_log_request_end_get_target_system(msg);
    log_request_end->target_component = mavlink_msg_log_request_end_get_target_component(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_LOG_REQUEST_END_LEN? msg->len : MAVLINK_MSG_ID_LOG_REQUEST_END_LEN;
    memset(log_request_end, 0, MAVLINK_MSG_ID_LOG_REQUEST_END_LEN);
    memcpy(log_request_end, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(log_request_end, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
