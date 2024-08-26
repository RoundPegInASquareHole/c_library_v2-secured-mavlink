#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE SET_MAG_OFFSETS PACKING

#define MAVLINK_MSG_ID_SET_MAG_OFFSETS 151


typedef struct __mavlink_set_mag_offsets_t {
 int16_t mag_ofs_x; /*<  Magnetometer X offset.*/
 int16_t mag_ofs_y; /*<  Magnetometer Y offset.*/
 int16_t mag_ofs_z; /*<  Magnetometer Z offset.*/
 uint8_t target_system; /*<  System ID.*/
 uint8_t target_component; /*<  Component ID.*/
} mavlink_set_mag_offsets_t;

#define MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN 8
#define MAVLINK_MSG_ID_SET_MAG_OFFSETS_MIN_LEN 8
#define MAVLINK_MSG_ID_151_LEN 8
#define MAVLINK_MSG_ID_151_MIN_LEN 8

#define MAVLINK_MSG_ID_SET_MAG_OFFSETS_CRC 219
#define MAVLINK_MSG_ID_151_CRC 219



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_MAG_OFFSETS { \
    151, \
    "SET_MAG_OFFSETS", \
    5, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_set_mag_offsets_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_set_mag_offsets_t, target_component) }, \
         { "mag_ofs_x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_set_mag_offsets_t, mag_ofs_x) }, \
         { "mag_ofs_y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_set_mag_offsets_t, mag_ofs_y) }, \
         { "mag_ofs_z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_set_mag_offsets_t, mag_ofs_z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_MAG_OFFSETS { \
    "SET_MAG_OFFSETS", \
    5, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_set_mag_offsets_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_set_mag_offsets_t, target_component) }, \
         { "mag_ofs_x", NULL, MAVLINK_TYPE_INT16_T, 0, 0, offsetof(mavlink_set_mag_offsets_t, mag_ofs_x) }, \
         { "mag_ofs_y", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_set_mag_offsets_t, mag_ofs_y) }, \
         { "mag_ofs_z", NULL, MAVLINK_TYPE_INT16_T, 0, 4, offsetof(mavlink_set_mag_offsets_t, mag_ofs_z) }, \
         } \
}
#endif

/**
 * @brief Pack a set_mag_offsets message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param mag_ofs_x  Magnetometer X offset.
 * @param mag_ofs_y  Magnetometer Y offset.
 * @param mag_ofs_z  Magnetometer Z offset.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_mag_offsets_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, int16_t mag_ofs_x, int16_t mag_ofs_y, int16_t mag_ofs_z)
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
    char buf[MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN];
    _mav_put_int16_t(buf, 0, mag_ofs_x);
    _mav_put_int16_t(buf, 2, mag_ofs_y);
    _mav_put_int16_t(buf, 4, mag_ofs_z);
    _mav_put_uint8_t(buf, 6, target_system);
    _mav_put_uint8_t(buf, 7, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN);
#else
    mavlink_set_mag_offsets_t packet;
    packet.mag_ofs_x = mag_ofs_x;
    packet.mag_ofs_y = mag_ofs_y;
    packet.mag_ofs_z = mag_ofs_z;
    packet.target_system = target_system;
    packet.target_component = target_component;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_set_mag_offsets_t* set_mag_offsets_final = (mavlink_set_mag_offsets_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), set_mag_offsets_final, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_MAG_OFFSETS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_MAG_OFFSETS_MIN_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_CRC);
}

/**
 * @brief Pack a set_mag_offsets message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param mag_ofs_x  Magnetometer X offset.
 * @param mag_ofs_y  Magnetometer Y offset.
 * @param mag_ofs_z  Magnetometer Z offset.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_mag_offsets_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,int16_t mag_ofs_x,int16_t mag_ofs_y,int16_t mag_ofs_z)
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
    char buf[MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN];
    _mav_put_int16_t(buf, 0, mag_ofs_x);
    _mav_put_int16_t(buf, 2, mag_ofs_y);
    _mav_put_int16_t(buf, 4, mag_ofs_z);
    _mav_put_uint8_t(buf, 6, target_system);
    _mav_put_uint8_t(buf, 7, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN);
#else
    mavlink_set_mag_offsets_t packet;
    packet.mag_ofs_x = mag_ofs_x;
    packet.mag_ofs_y = mag_ofs_y;
    packet.mag_ofs_z = mag_ofs_z;
    packet.target_system = target_system;
    packet.target_component = target_component;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_set_mag_offsets_t* set_mag_offsets_final = (mavlink_set_mag_offsets_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), set_mag_offsets_final, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_MAG_OFFSETS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_MAG_OFFSETS_MIN_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_CRC);
}

/**
 * @brief Encode a set_mag_offsets struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_mag_offsets C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_mag_offsets_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_mag_offsets_t* set_mag_offsets)
{
    return mavlink_msg_set_mag_offsets_pack(system_id, component_id, msg, set_mag_offsets->target_system, set_mag_offsets->target_component, set_mag_offsets->mag_ofs_x, set_mag_offsets->mag_ofs_y, set_mag_offsets->mag_ofs_z);
}

/**
 * @brief Encode a set_mag_offsets struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_mag_offsets C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_mag_offsets_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_mag_offsets_t* set_mag_offsets)
{
    return mavlink_msg_set_mag_offsets_pack_chan(system_id, component_id, chan, msg, set_mag_offsets->target_system, set_mag_offsets->target_component, set_mag_offsets->mag_ofs_x, set_mag_offsets->mag_ofs_y, set_mag_offsets->mag_ofs_z);
}

/**
 * @brief Send a set_mag_offsets message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param mag_ofs_x  Magnetometer X offset.
 * @param mag_ofs_y  Magnetometer Y offset.
 * @param mag_ofs_z  Magnetometer Z offset.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_mag_offsets_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, int16_t mag_ofs_x, int16_t mag_ofs_y, int16_t mag_ofs_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN];
    _mav_put_int16_t(buf, 0, mag_ofs_x);
    _mav_put_int16_t(buf, 2, mag_ofs_y);
    _mav_put_int16_t(buf, 4, mag_ofs_z);
    _mav_put_uint8_t(buf, 6, target_system);
    _mav_put_uint8_t(buf, 7, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MAG_OFFSETS, buf, MAVLINK_MSG_ID_SET_MAG_OFFSETS_MIN_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_CRC);
#else
    mavlink_set_mag_offsets_t packet;
    packet.mag_ofs_x = mag_ofs_x;
    packet.mag_ofs_y = mag_ofs_y;
    packet.mag_ofs_z = mag_ofs_z;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MAG_OFFSETS, (const char *)&packet, MAVLINK_MSG_ID_SET_MAG_OFFSETS_MIN_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_CRC);
#endif
}

/**
 * @brief Send a set_mag_offsets message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_mag_offsets_send_struct(mavlink_channel_t chan, const mavlink_set_mag_offsets_t* set_mag_offsets)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_mag_offsets_send(chan, set_mag_offsets->target_system, set_mag_offsets->target_component, set_mag_offsets->mag_ofs_x, set_mag_offsets->mag_ofs_y, set_mag_offsets->mag_ofs_z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MAG_OFFSETS, (const char *)set_mag_offsets, MAVLINK_MSG_ID_SET_MAG_OFFSETS_MIN_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_mag_offsets_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, int16_t mag_ofs_x, int16_t mag_ofs_y, int16_t mag_ofs_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int16_t(buf, 0, mag_ofs_x);
    _mav_put_int16_t(buf, 2, mag_ofs_y);
    _mav_put_int16_t(buf, 4, mag_ofs_z);
    _mav_put_uint8_t(buf, 6, target_system);
    _mav_put_uint8_t(buf, 7, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MAG_OFFSETS, buf, MAVLINK_MSG_ID_SET_MAG_OFFSETS_MIN_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_CRC);
#else
    mavlink_set_mag_offsets_t *packet = (mavlink_set_mag_offsets_t *)msgbuf;
    packet->mag_ofs_x = mag_ofs_x;
    packet->mag_ofs_y = mag_ofs_y;
    packet->mag_ofs_z = mag_ofs_z;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_MAG_OFFSETS, (const char *)packet, MAVLINK_MSG_ID_SET_MAG_OFFSETS_MIN_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN, MAVLINK_MSG_ID_SET_MAG_OFFSETS_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_MAG_OFFSETS UNPACKING


/**
 * @brief Get field target_system from set_mag_offsets message
 *
 * @return  System ID.
 */
static inline uint8_t mavlink_msg_set_mag_offsets_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field target_component from set_mag_offsets message
 *
 * @return  Component ID.
 */
static inline uint8_t mavlink_msg_set_mag_offsets_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field mag_ofs_x from set_mag_offsets message
 *
 * @return  Magnetometer X offset.
 */
static inline int16_t mavlink_msg_set_mag_offsets_get_mag_ofs_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  0);
}

/**
 * @brief Get field mag_ofs_y from set_mag_offsets message
 *
 * @return  Magnetometer Y offset.
 */
static inline int16_t mavlink_msg_set_mag_offsets_get_mag_ofs_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Get field mag_ofs_z from set_mag_offsets message
 *
 * @return  Magnetometer Z offset.
 */
static inline int16_t mavlink_msg_set_mag_offsets_get_mag_ofs_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  4);
}

/**
 * @brief Decode a set_mag_offsets message into a struct
 *
 * @param msg The message to decode
 * @param set_mag_offsets C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_mag_offsets_decode(const mavlink_message_t* msg, mavlink_set_mag_offsets_t* set_mag_offsets)
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
    set_mag_offsets->mag_ofs_x = mavlink_msg_set_mag_offsets_get_mag_ofs_x(msg);
    set_mag_offsets->mag_ofs_y = mavlink_msg_set_mag_offsets_get_mag_ofs_y(msg);
    set_mag_offsets->mag_ofs_z = mavlink_msg_set_mag_offsets_get_mag_ofs_z(msg);
    set_mag_offsets->target_system = mavlink_msg_set_mag_offsets_get_target_system(msg);
    set_mag_offsets->target_component = mavlink_msg_set_mag_offsets_get_target_component(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN? msg->len : MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN;
    memset(set_mag_offsets, 0, MAVLINK_MSG_ID_SET_MAG_OFFSETS_LEN);
    memcpy(set_mag_offsets, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(set_mag_offsets, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
