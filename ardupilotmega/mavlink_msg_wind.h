#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE WIND PACKING

#define MAVLINK_MSG_ID_WIND 168


typedef struct __mavlink_wind_t {
 float direction; /*< [deg] Wind direction (that wind is coming from).*/
 float speed; /*< [m/s] Wind speed in ground plane.*/
 float speed_z; /*< [m/s] Vertical wind speed.*/
} mavlink_wind_t;

#define MAVLINK_MSG_ID_WIND_LEN 12
#define MAVLINK_MSG_ID_WIND_MIN_LEN 12
#define MAVLINK_MSG_ID_168_LEN 12
#define MAVLINK_MSG_ID_168_MIN_LEN 12

#define MAVLINK_MSG_ID_WIND_CRC 1
#define MAVLINK_MSG_ID_168_CRC 1



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_WIND { \
    168, \
    "WIND", \
    3, \
    {  { "direction", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_wind_t, direction) }, \
         { "speed", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_wind_t, speed) }, \
         { "speed_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_wind_t, speed_z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_WIND { \
    "WIND", \
    3, \
    {  { "direction", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_wind_t, direction) }, \
         { "speed", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_wind_t, speed) }, \
         { "speed_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_wind_t, speed_z) }, \
         } \
}
#endif

/**
 * @brief Pack a wind message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param direction [deg] Wind direction (that wind is coming from).
 * @param speed [m/s] Wind speed in ground plane.
 * @param speed_z [m/s] Vertical wind speed.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wind_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float direction, float speed, float speed_z)
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
    char buf[MAVLINK_MSG_ID_WIND_LEN];
    _mav_put_float(buf, 0, direction);
    _mav_put_float(buf, 4, speed);
    _mav_put_float(buf, 8, speed_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIND_LEN);
#else
    mavlink_wind_t packet;
    packet.direction = direction;
    packet.speed = speed;
    packet.speed_z = speed_z;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_WIND_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_WIND_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_wind_t* wind_final = (mavlink_wind_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), wind_final, MAVLINK_MSG_ID_WIND_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_WIND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_WIND_MIN_LEN, MAVLINK_MSG_ID_WIND_LEN, MAVLINK_MSG_ID_WIND_CRC);
}

/**
 * @brief Pack a wind message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param direction [deg] Wind direction (that wind is coming from).
 * @param speed [m/s] Wind speed in ground plane.
 * @param speed_z [m/s] Vertical wind speed.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wind_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float direction,float speed,float speed_z)
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
    char buf[MAVLINK_MSG_ID_WIND_LEN];
    _mav_put_float(buf, 0, direction);
    _mav_put_float(buf, 4, speed);
    _mav_put_float(buf, 8, speed_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIND_LEN);
#else
    mavlink_wind_t packet;
    packet.direction = direction;
    packet.speed = speed;
    packet.speed_z = speed_z;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_WIND_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_WIND_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_wind_t* wind_final = (mavlink_wind_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), wind_final, MAVLINK_MSG_ID_WIND_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_WIND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_WIND_MIN_LEN, MAVLINK_MSG_ID_WIND_LEN, MAVLINK_MSG_ID_WIND_CRC);
}

/**
 * @brief Encode a wind struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param wind C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wind_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_wind_t* wind)
{
    return mavlink_msg_wind_pack(system_id, component_id, msg, wind->direction, wind->speed, wind->speed_z);
}

/**
 * @brief Encode a wind struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param wind C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wind_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_wind_t* wind)
{
    return mavlink_msg_wind_pack_chan(system_id, component_id, chan, msg, wind->direction, wind->speed, wind->speed_z);
}

/**
 * @brief Send a wind message
 * @param chan MAVLink channel to send the message
 *
 * @param direction [deg] Wind direction (that wind is coming from).
 * @param speed [m/s] Wind speed in ground plane.
 * @param speed_z [m/s] Vertical wind speed.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_wind_send(mavlink_channel_t chan, float direction, float speed, float speed_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIND_LEN];
    _mav_put_float(buf, 0, direction);
    _mav_put_float(buf, 4, speed);
    _mav_put_float(buf, 8, speed_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND, buf, MAVLINK_MSG_ID_WIND_MIN_LEN, MAVLINK_MSG_ID_WIND_LEN, MAVLINK_MSG_ID_WIND_CRC);
#else
    mavlink_wind_t packet;
    packet.direction = direction;
    packet.speed = speed;
    packet.speed_z = speed_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND, (const char *)&packet, MAVLINK_MSG_ID_WIND_MIN_LEN, MAVLINK_MSG_ID_WIND_LEN, MAVLINK_MSG_ID_WIND_CRC);
#endif
}

/**
 * @brief Send a wind message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_wind_send_struct(mavlink_channel_t chan, const mavlink_wind_t* wind)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_wind_send(chan, wind->direction, wind->speed, wind->speed_z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND, (const char *)wind, MAVLINK_MSG_ID_WIND_MIN_LEN, MAVLINK_MSG_ID_WIND_LEN, MAVLINK_MSG_ID_WIND_CRC);
#endif
}

#if MAVLINK_MSG_ID_WIND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_wind_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float direction, float speed, float speed_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, direction);
    _mav_put_float(buf, 4, speed);
    _mav_put_float(buf, 8, speed_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND, buf, MAVLINK_MSG_ID_WIND_MIN_LEN, MAVLINK_MSG_ID_WIND_LEN, MAVLINK_MSG_ID_WIND_CRC);
#else
    mavlink_wind_t *packet = (mavlink_wind_t *)msgbuf;
    packet->direction = direction;
    packet->speed = speed;
    packet->speed_z = speed_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIND, (const char *)packet, MAVLINK_MSG_ID_WIND_MIN_LEN, MAVLINK_MSG_ID_WIND_LEN, MAVLINK_MSG_ID_WIND_CRC);
#endif
}
#endif

#endif

// MESSAGE WIND UNPACKING


/**
 * @brief Get field direction from wind message
 *
 * @return [deg] Wind direction (that wind is coming from).
 */
static inline float mavlink_msg_wind_get_direction(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field speed from wind message
 *
 * @return [m/s] Wind speed in ground plane.
 */
static inline float mavlink_msg_wind_get_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field speed_z from wind message
 *
 * @return [m/s] Vertical wind speed.
 */
static inline float mavlink_msg_wind_get_speed_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a wind message into a struct
 *
 * @param msg The message to decode
 * @param wind C-struct to decode the message contents into
 */
static inline void mavlink_msg_wind_decode(const mavlink_message_t* msg, mavlink_wind_t* wind)
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
    wind->direction = mavlink_msg_wind_get_direction(msg);
    wind->speed = mavlink_msg_wind_get_speed(msg);
    wind->speed_z = mavlink_msg_wind_get_speed_z(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_WIND_LEN? msg->len : MAVLINK_MSG_ID_WIND_LEN;
    memset(wind, 0, MAVLINK_MSG_ID_WIND_LEN);
    memcpy(wind, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(wind, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
