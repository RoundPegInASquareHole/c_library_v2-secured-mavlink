#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE GIMBAL_CONTROL PACKING

#define MAVLINK_MSG_ID_GIMBAL_CONTROL 201


typedef struct __mavlink_gimbal_control_t {
 float demanded_rate_x; /*< [rad/s] Demanded angular rate X.*/
 float demanded_rate_y; /*< [rad/s] Demanded angular rate Y.*/
 float demanded_rate_z; /*< [rad/s] Demanded angular rate Z.*/
 uint8_t target_system; /*<  System ID.*/
 uint8_t target_component; /*<  Component ID.*/
} mavlink_gimbal_control_t;

#define MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN 14
#define MAVLINK_MSG_ID_GIMBAL_CONTROL_MIN_LEN 14
#define MAVLINK_MSG_ID_201_LEN 14
#define MAVLINK_MSG_ID_201_MIN_LEN 14

#define MAVLINK_MSG_ID_GIMBAL_CONTROL_CRC 205
#define MAVLINK_MSG_ID_201_CRC 205



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_GIMBAL_CONTROL { \
    201, \
    "GIMBAL_CONTROL", \
    5, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_gimbal_control_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_gimbal_control_t, target_component) }, \
         { "demanded_rate_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_gimbal_control_t, demanded_rate_x) }, \
         { "demanded_rate_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_gimbal_control_t, demanded_rate_y) }, \
         { "demanded_rate_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_gimbal_control_t, demanded_rate_z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_GIMBAL_CONTROL { \
    "GIMBAL_CONTROL", \
    5, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_gimbal_control_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_gimbal_control_t, target_component) }, \
         { "demanded_rate_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_gimbal_control_t, demanded_rate_x) }, \
         { "demanded_rate_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_gimbal_control_t, demanded_rate_y) }, \
         { "demanded_rate_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_gimbal_control_t, demanded_rate_z) }, \
         } \
}
#endif

/**
 * @brief Pack a gimbal_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param demanded_rate_x [rad/s] Demanded angular rate X.
 * @param demanded_rate_y [rad/s] Demanded angular rate Y.
 * @param demanded_rate_z [rad/s] Demanded angular rate Z.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gimbal_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, float demanded_rate_x, float demanded_rate_y, float demanded_rate_z)
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
    char buf[MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN];
    _mav_put_float(buf, 0, demanded_rate_x);
    _mav_put_float(buf, 4, demanded_rate_y);
    _mav_put_float(buf, 8, demanded_rate_z);
    _mav_put_uint8_t(buf, 12, target_system);
    _mav_put_uint8_t(buf, 13, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN);
#else
    mavlink_gimbal_control_t packet;
    packet.demanded_rate_x = demanded_rate_x;
    packet.demanded_rate_y = demanded_rate_y;
    packet.demanded_rate_z = demanded_rate_z;
    packet.target_system = target_system;
    packet.target_component = target_component;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_gimbal_control_t* gimbal_control_final = (mavlink_gimbal_control_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), gimbal_control_final, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_GIMBAL_CONTROL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_CRC);
}

/**
 * @brief Pack a gimbal_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param demanded_rate_x [rad/s] Demanded angular rate X.
 * @param demanded_rate_y [rad/s] Demanded angular rate Y.
 * @param demanded_rate_z [rad/s] Demanded angular rate Z.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gimbal_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,float demanded_rate_x,float demanded_rate_y,float demanded_rate_z)
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
    char buf[MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN];
    _mav_put_float(buf, 0, demanded_rate_x);
    _mav_put_float(buf, 4, demanded_rate_y);
    _mav_put_float(buf, 8, demanded_rate_z);
    _mav_put_uint8_t(buf, 12, target_system);
    _mav_put_uint8_t(buf, 13, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN);
#else
    mavlink_gimbal_control_t packet;
    packet.demanded_rate_x = demanded_rate_x;
    packet.demanded_rate_y = demanded_rate_y;
    packet.demanded_rate_z = demanded_rate_z;
    packet.target_system = target_system;
    packet.target_component = target_component;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_gimbal_control_t* gimbal_control_final = (mavlink_gimbal_control_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), gimbal_control_final, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_GIMBAL_CONTROL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_CRC);
}

/**
 * @brief Encode a gimbal_control struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gimbal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gimbal_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gimbal_control_t* gimbal_control)
{
    return mavlink_msg_gimbal_control_pack(system_id, component_id, msg, gimbal_control->target_system, gimbal_control->target_component, gimbal_control->demanded_rate_x, gimbal_control->demanded_rate_y, gimbal_control->demanded_rate_z);
}

/**
 * @brief Encode a gimbal_control struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gimbal_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gimbal_control_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_gimbal_control_t* gimbal_control)
{
    return mavlink_msg_gimbal_control_pack_chan(system_id, component_id, chan, msg, gimbal_control->target_system, gimbal_control->target_component, gimbal_control->demanded_rate_x, gimbal_control->demanded_rate_y, gimbal_control->demanded_rate_z);
}

/**
 * @brief Send a gimbal_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param demanded_rate_x [rad/s] Demanded angular rate X.
 * @param demanded_rate_y [rad/s] Demanded angular rate Y.
 * @param demanded_rate_z [rad/s] Demanded angular rate Z.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gimbal_control_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, float demanded_rate_x, float demanded_rate_y, float demanded_rate_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN];
    _mav_put_float(buf, 0, demanded_rate_x);
    _mav_put_float(buf, 4, demanded_rate_y);
    _mav_put_float(buf, 8, demanded_rate_z);
    _mav_put_uint8_t(buf, 12, target_system);
    _mav_put_uint8_t(buf, 13, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GIMBAL_CONTROL, buf, MAVLINK_MSG_ID_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_CRC);
#else
    mavlink_gimbal_control_t packet;
    packet.demanded_rate_x = demanded_rate_x;
    packet.demanded_rate_y = demanded_rate_y;
    packet.demanded_rate_z = demanded_rate_z;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GIMBAL_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_CRC);
#endif
}

/**
 * @brief Send a gimbal_control message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_gimbal_control_send_struct(mavlink_channel_t chan, const mavlink_gimbal_control_t* gimbal_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_gimbal_control_send(chan, gimbal_control->target_system, gimbal_control->target_component, gimbal_control->demanded_rate_x, gimbal_control->demanded_rate_y, gimbal_control->demanded_rate_z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GIMBAL_CONTROL, (const char *)gimbal_control, MAVLINK_MSG_ID_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_CRC);
#endif
}

#if MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_gimbal_control_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, float demanded_rate_x, float demanded_rate_y, float demanded_rate_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, demanded_rate_x);
    _mav_put_float(buf, 4, demanded_rate_y);
    _mav_put_float(buf, 8, demanded_rate_z);
    _mav_put_uint8_t(buf, 12, target_system);
    _mav_put_uint8_t(buf, 13, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GIMBAL_CONTROL, buf, MAVLINK_MSG_ID_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_CRC);
#else
    mavlink_gimbal_control_t *packet = (mavlink_gimbal_control_t *)msgbuf;
    packet->demanded_rate_x = demanded_rate_x;
    packet->demanded_rate_y = demanded_rate_y;
    packet->demanded_rate_z = demanded_rate_z;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GIMBAL_CONTROL, (const char *)packet, MAVLINK_MSG_ID_GIMBAL_CONTROL_MIN_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN, MAVLINK_MSG_ID_GIMBAL_CONTROL_CRC);
#endif
}
#endif

#endif

// MESSAGE GIMBAL_CONTROL UNPACKING


/**
 * @brief Get field target_system from gimbal_control message
 *
 * @return  System ID.
 */
static inline uint8_t mavlink_msg_gimbal_control_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field target_component from gimbal_control message
 *
 * @return  Component ID.
 */
static inline uint8_t mavlink_msg_gimbal_control_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field demanded_rate_x from gimbal_control message
 *
 * @return [rad/s] Demanded angular rate X.
 */
static inline float mavlink_msg_gimbal_control_get_demanded_rate_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field demanded_rate_y from gimbal_control message
 *
 * @return [rad/s] Demanded angular rate Y.
 */
static inline float mavlink_msg_gimbal_control_get_demanded_rate_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field demanded_rate_z from gimbal_control message
 *
 * @return [rad/s] Demanded angular rate Z.
 */
static inline float mavlink_msg_gimbal_control_get_demanded_rate_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a gimbal_control message into a struct
 *
 * @param msg The message to decode
 * @param gimbal_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_gimbal_control_decode(const mavlink_message_t* msg, mavlink_gimbal_control_t* gimbal_control)
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
    gimbal_control->demanded_rate_x = mavlink_msg_gimbal_control_get_demanded_rate_x(msg);
    gimbal_control->demanded_rate_y = mavlink_msg_gimbal_control_get_demanded_rate_y(msg);
    gimbal_control->demanded_rate_z = mavlink_msg_gimbal_control_get_demanded_rate_z(msg);
    gimbal_control->target_system = mavlink_msg_gimbal_control_get_target_system(msg);
    gimbal_control->target_component = mavlink_msg_gimbal_control_get_target_component(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN? msg->len : MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN;
    memset(gimbal_control, 0, MAVLINK_MSG_ID_GIMBAL_CONTROL_LEN);
    memcpy(gimbal_control, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(gimbal_control, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
