#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE SUPPORTED_TUNES PACKING

#define MAVLINK_MSG_ID_SUPPORTED_TUNES 401


typedef struct __mavlink_supported_tunes_t {
 uint32_t format; /*<  Bitfield of supported tune formats.*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
} mavlink_supported_tunes_t;

#define MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN 6
#define MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN 6
#define MAVLINK_MSG_ID_401_LEN 6
#define MAVLINK_MSG_ID_401_MIN_LEN 6

#define MAVLINK_MSG_ID_SUPPORTED_TUNES_CRC 183
#define MAVLINK_MSG_ID_401_CRC 183



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SUPPORTED_TUNES { \
    401, \
    "SUPPORTED_TUNES", \
    3, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_supported_tunes_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_supported_tunes_t, target_component) }, \
         { "format", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_supported_tunes_t, format) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SUPPORTED_TUNES { \
    "SUPPORTED_TUNES", \
    3, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_supported_tunes_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_supported_tunes_t, target_component) }, \
         { "format", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_supported_tunes_t, format) }, \
         } \
}
#endif

/**
 * @brief Pack a supported_tunes message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param format  Bitfield of supported tune formats.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_supported_tunes_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint32_t format)
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
    char buf[MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN];
    _mav_put_uint32_t(buf, 0, format);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN);
#else
    mavlink_supported_tunes_t packet;
    packet.format = format;
    packet.target_system = target_system;
    packet.target_component = target_component;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_supported_tunes_t* supported_tunes_final = (mavlink_supported_tunes_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), supported_tunes_final, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_SUPPORTED_TUNES;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_CRC);
}

/**
 * @brief Pack a supported_tunes message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param format  Bitfield of supported tune formats.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_supported_tunes_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint32_t format)
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
    char buf[MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN];
    _mav_put_uint32_t(buf, 0, format);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN);
#else
    mavlink_supported_tunes_t packet;
    packet.format = format;
    packet.target_system = target_system;
    packet.target_component = target_component;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_supported_tunes_t* supported_tunes_final = (mavlink_supported_tunes_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), supported_tunes_final, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_SUPPORTED_TUNES;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_CRC);
}

/**
 * @brief Encode a supported_tunes struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param supported_tunes C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_supported_tunes_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_supported_tunes_t* supported_tunes)
{
    return mavlink_msg_supported_tunes_pack(system_id, component_id, msg, supported_tunes->target_system, supported_tunes->target_component, supported_tunes->format);
}

/**
 * @brief Encode a supported_tunes struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param supported_tunes C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_supported_tunes_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_supported_tunes_t* supported_tunes)
{
    return mavlink_msg_supported_tunes_pack_chan(system_id, component_id, chan, msg, supported_tunes->target_system, supported_tunes->target_component, supported_tunes->format);
}

/**
 * @brief Send a supported_tunes message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param format  Bitfield of supported tune formats.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_supported_tunes_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint32_t format)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN];
    _mav_put_uint32_t(buf, 0, format);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SUPPORTED_TUNES, buf, MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_CRC);
#else
    mavlink_supported_tunes_t packet;
    packet.format = format;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SUPPORTED_TUNES, (const char *)&packet, MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_CRC);
#endif
}

/**
 * @brief Send a supported_tunes message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_supported_tunes_send_struct(mavlink_channel_t chan, const mavlink_supported_tunes_t* supported_tunes)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_supported_tunes_send(chan, supported_tunes->target_system, supported_tunes->target_component, supported_tunes->format);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SUPPORTED_TUNES, (const char *)supported_tunes, MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_CRC);
#endif
}

#if MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_supported_tunes_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint32_t format)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, format);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SUPPORTED_TUNES, buf, MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_CRC);
#else
    mavlink_supported_tunes_t *packet = (mavlink_supported_tunes_t *)msgbuf;
    packet->format = format;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SUPPORTED_TUNES, (const char *)packet, MAVLINK_MSG_ID_SUPPORTED_TUNES_MIN_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN, MAVLINK_MSG_ID_SUPPORTED_TUNES_CRC);
#endif
}
#endif

#endif

// MESSAGE SUPPORTED_TUNES UNPACKING


/**
 * @brief Get field target_system from supported_tunes message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_supported_tunes_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field target_component from supported_tunes message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_supported_tunes_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field format from supported_tunes message
 *
 * @return  Bitfield of supported tune formats.
 */
static inline uint32_t mavlink_msg_supported_tunes_get_format(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a supported_tunes message into a struct
 *
 * @param msg The message to decode
 * @param supported_tunes C-struct to decode the message contents into
 */
static inline void mavlink_msg_supported_tunes_decode(const mavlink_message_t* msg, mavlink_supported_tunes_t* supported_tunes)
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
    supported_tunes->format = mavlink_msg_supported_tunes_get_format(msg);
    supported_tunes->target_system = mavlink_msg_supported_tunes_get_target_system(msg);
    supported_tunes->target_component = mavlink_msg_supported_tunes_get_target_component(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN? msg->len : MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN;
    memset(supported_tunes, 0, MAVLINK_MSG_ID_SUPPORTED_TUNES_LEN);
    memcpy(supported_tunes, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(supported_tunes, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
