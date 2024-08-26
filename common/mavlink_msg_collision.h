#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE COLLISION PACKING

#define MAVLINK_MSG_ID_COLLISION 247


typedef struct __mavlink_collision_t {
 uint32_t id; /*<  Unique identifier, domain based on src field*/
 float time_to_minimum_delta; /*< [s] Estimated time until collision occurs*/
 float altitude_minimum_delta; /*< [m] Closest vertical distance between vehicle and object*/
 float horizontal_minimum_delta; /*< [m] Closest horizontal distance between vehicle and object*/
 uint8_t src; /*<  Collision data source*/
 uint8_t action; /*<  Action that is being taken to avoid this collision*/
 uint8_t threat_level; /*<  How concerned the aircraft is about this collision*/
} mavlink_collision_t;

#define MAVLINK_MSG_ID_COLLISION_LEN 19
#define MAVLINK_MSG_ID_COLLISION_MIN_LEN 19
#define MAVLINK_MSG_ID_247_LEN 19
#define MAVLINK_MSG_ID_247_MIN_LEN 19

#define MAVLINK_MSG_ID_COLLISION_CRC 81
#define MAVLINK_MSG_ID_247_CRC 81



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_COLLISION { \
    247, \
    "COLLISION", \
    7, \
    {  { "src", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_collision_t, src) }, \
         { "id", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_collision_t, id) }, \
         { "action", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_collision_t, action) }, \
         { "threat_level", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_collision_t, threat_level) }, \
         { "time_to_minimum_delta", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_collision_t, time_to_minimum_delta) }, \
         { "altitude_minimum_delta", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_collision_t, altitude_minimum_delta) }, \
         { "horizontal_minimum_delta", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_collision_t, horizontal_minimum_delta) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_COLLISION { \
    "COLLISION", \
    7, \
    {  { "src", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_collision_t, src) }, \
         { "id", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_collision_t, id) }, \
         { "action", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_collision_t, action) }, \
         { "threat_level", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_collision_t, threat_level) }, \
         { "time_to_minimum_delta", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_collision_t, time_to_minimum_delta) }, \
         { "altitude_minimum_delta", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_collision_t, altitude_minimum_delta) }, \
         { "horizontal_minimum_delta", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_collision_t, horizontal_minimum_delta) }, \
         } \
}
#endif

/**
 * @brief Pack a collision message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param src  Collision data source
 * @param id  Unique identifier, domain based on src field
 * @param action  Action that is being taken to avoid this collision
 * @param threat_level  How concerned the aircraft is about this collision
 * @param time_to_minimum_delta [s] Estimated time until collision occurs
 * @param altitude_minimum_delta [m] Closest vertical distance between vehicle and object
 * @param horizontal_minimum_delta [m] Closest horizontal distance between vehicle and object
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_collision_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t src, uint32_t id, uint8_t action, uint8_t threat_level, float time_to_minimum_delta, float altitude_minimum_delta, float horizontal_minimum_delta)
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
    char buf[MAVLINK_MSG_ID_COLLISION_LEN];
    _mav_put_uint32_t(buf, 0, id);
    _mav_put_float(buf, 4, time_to_minimum_delta);
    _mav_put_float(buf, 8, altitude_minimum_delta);
    _mav_put_float(buf, 12, horizontal_minimum_delta);
    _mav_put_uint8_t(buf, 16, src);
    _mav_put_uint8_t(buf, 17, action);
    _mav_put_uint8_t(buf, 18, threat_level);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COLLISION_LEN);
#else
    mavlink_collision_t packet;
    packet.id = id;
    packet.time_to_minimum_delta = time_to_minimum_delta;
    packet.altitude_minimum_delta = altitude_minimum_delta;
    packet.horizontal_minimum_delta = horizontal_minimum_delta;
    packet.src = src;
    packet.action = action;
    packet.threat_level = threat_level;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_COLLISION_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_COLLISION_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_collision_t* collision_final = (mavlink_collision_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), collision_final, MAVLINK_MSG_ID_COLLISION_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_COLLISION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_COLLISION_MIN_LEN, MAVLINK_MSG_ID_COLLISION_LEN, MAVLINK_MSG_ID_COLLISION_CRC);
}

/**
 * @brief Pack a collision message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param src  Collision data source
 * @param id  Unique identifier, domain based on src field
 * @param action  Action that is being taken to avoid this collision
 * @param threat_level  How concerned the aircraft is about this collision
 * @param time_to_minimum_delta [s] Estimated time until collision occurs
 * @param altitude_minimum_delta [m] Closest vertical distance between vehicle and object
 * @param horizontal_minimum_delta [m] Closest horizontal distance between vehicle and object
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_collision_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t src,uint32_t id,uint8_t action,uint8_t threat_level,float time_to_minimum_delta,float altitude_minimum_delta,float horizontal_minimum_delta)
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
    char buf[MAVLINK_MSG_ID_COLLISION_LEN];
    _mav_put_uint32_t(buf, 0, id);
    _mav_put_float(buf, 4, time_to_minimum_delta);
    _mav_put_float(buf, 8, altitude_minimum_delta);
    _mav_put_float(buf, 12, horizontal_minimum_delta);
    _mav_put_uint8_t(buf, 16, src);
    _mav_put_uint8_t(buf, 17, action);
    _mav_put_uint8_t(buf, 18, threat_level);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COLLISION_LEN);
#else
    mavlink_collision_t packet;
    packet.id = id;
    packet.time_to_minimum_delta = time_to_minimum_delta;
    packet.altitude_minimum_delta = altitude_minimum_delta;
    packet.horizontal_minimum_delta = horizontal_minimum_delta;
    packet.src = src;
    packet.action = action;
    packet.threat_level = threat_level;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_COLLISION_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_COLLISION_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_collision_t* collision_final = (mavlink_collision_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), collision_final, MAVLINK_MSG_ID_COLLISION_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_COLLISION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_COLLISION_MIN_LEN, MAVLINK_MSG_ID_COLLISION_LEN, MAVLINK_MSG_ID_COLLISION_CRC);
}

/**
 * @brief Encode a collision struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param collision C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_collision_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_collision_t* collision)
{
    return mavlink_msg_collision_pack(system_id, component_id, msg, collision->src, collision->id, collision->action, collision->threat_level, collision->time_to_minimum_delta, collision->altitude_minimum_delta, collision->horizontal_minimum_delta);
}

/**
 * @brief Encode a collision struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param collision C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_collision_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_collision_t* collision)
{
    return mavlink_msg_collision_pack_chan(system_id, component_id, chan, msg, collision->src, collision->id, collision->action, collision->threat_level, collision->time_to_minimum_delta, collision->altitude_minimum_delta, collision->horizontal_minimum_delta);
}

/**
 * @brief Send a collision message
 * @param chan MAVLink channel to send the message
 *
 * @param src  Collision data source
 * @param id  Unique identifier, domain based on src field
 * @param action  Action that is being taken to avoid this collision
 * @param threat_level  How concerned the aircraft is about this collision
 * @param time_to_minimum_delta [s] Estimated time until collision occurs
 * @param altitude_minimum_delta [m] Closest vertical distance between vehicle and object
 * @param horizontal_minimum_delta [m] Closest horizontal distance between vehicle and object
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_collision_send(mavlink_channel_t chan, uint8_t src, uint32_t id, uint8_t action, uint8_t threat_level, float time_to_minimum_delta, float altitude_minimum_delta, float horizontal_minimum_delta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COLLISION_LEN];
    _mav_put_uint32_t(buf, 0, id);
    _mav_put_float(buf, 4, time_to_minimum_delta);
    _mav_put_float(buf, 8, altitude_minimum_delta);
    _mav_put_float(buf, 12, horizontal_minimum_delta);
    _mav_put_uint8_t(buf, 16, src);
    _mav_put_uint8_t(buf, 17, action);
    _mav_put_uint8_t(buf, 18, threat_level);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COLLISION, buf, MAVLINK_MSG_ID_COLLISION_MIN_LEN, MAVLINK_MSG_ID_COLLISION_LEN, MAVLINK_MSG_ID_COLLISION_CRC);
#else
    mavlink_collision_t packet;
    packet.id = id;
    packet.time_to_minimum_delta = time_to_minimum_delta;
    packet.altitude_minimum_delta = altitude_minimum_delta;
    packet.horizontal_minimum_delta = horizontal_minimum_delta;
    packet.src = src;
    packet.action = action;
    packet.threat_level = threat_level;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COLLISION, (const char *)&packet, MAVLINK_MSG_ID_COLLISION_MIN_LEN, MAVLINK_MSG_ID_COLLISION_LEN, MAVLINK_MSG_ID_COLLISION_CRC);
#endif
}

/**
 * @brief Send a collision message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_collision_send_struct(mavlink_channel_t chan, const mavlink_collision_t* collision)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_collision_send(chan, collision->src, collision->id, collision->action, collision->threat_level, collision->time_to_minimum_delta, collision->altitude_minimum_delta, collision->horizontal_minimum_delta);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COLLISION, (const char *)collision, MAVLINK_MSG_ID_COLLISION_MIN_LEN, MAVLINK_MSG_ID_COLLISION_LEN, MAVLINK_MSG_ID_COLLISION_CRC);
#endif
}

#if MAVLINK_MSG_ID_COLLISION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_collision_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t src, uint32_t id, uint8_t action, uint8_t threat_level, float time_to_minimum_delta, float altitude_minimum_delta, float horizontal_minimum_delta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, id);
    _mav_put_float(buf, 4, time_to_minimum_delta);
    _mav_put_float(buf, 8, altitude_minimum_delta);
    _mav_put_float(buf, 12, horizontal_minimum_delta);
    _mav_put_uint8_t(buf, 16, src);
    _mav_put_uint8_t(buf, 17, action);
    _mav_put_uint8_t(buf, 18, threat_level);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COLLISION, buf, MAVLINK_MSG_ID_COLLISION_MIN_LEN, MAVLINK_MSG_ID_COLLISION_LEN, MAVLINK_MSG_ID_COLLISION_CRC);
#else
    mavlink_collision_t *packet = (mavlink_collision_t *)msgbuf;
    packet->id = id;
    packet->time_to_minimum_delta = time_to_minimum_delta;
    packet->altitude_minimum_delta = altitude_minimum_delta;
    packet->horizontal_minimum_delta = horizontal_minimum_delta;
    packet->src = src;
    packet->action = action;
    packet->threat_level = threat_level;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COLLISION, (const char *)packet, MAVLINK_MSG_ID_COLLISION_MIN_LEN, MAVLINK_MSG_ID_COLLISION_LEN, MAVLINK_MSG_ID_COLLISION_CRC);
#endif
}
#endif

#endif

// MESSAGE COLLISION UNPACKING


/**
 * @brief Get field src from collision message
 *
 * @return  Collision data source
 */
static inline uint8_t mavlink_msg_collision_get_src(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field id from collision message
 *
 * @return  Unique identifier, domain based on src field
 */
static inline uint32_t mavlink_msg_collision_get_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field action from collision message
 *
 * @return  Action that is being taken to avoid this collision
 */
static inline uint8_t mavlink_msg_collision_get_action(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Get field threat_level from collision message
 *
 * @return  How concerned the aircraft is about this collision
 */
static inline uint8_t mavlink_msg_collision_get_threat_level(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Get field time_to_minimum_delta from collision message
 *
 * @return [s] Estimated time until collision occurs
 */
static inline float mavlink_msg_collision_get_time_to_minimum_delta(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field altitude_minimum_delta from collision message
 *
 * @return [m] Closest vertical distance between vehicle and object
 */
static inline float mavlink_msg_collision_get_altitude_minimum_delta(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field horizontal_minimum_delta from collision message
 *
 * @return [m] Closest horizontal distance between vehicle and object
 */
static inline float mavlink_msg_collision_get_horizontal_minimum_delta(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a collision message into a struct
 *
 * @param msg The message to decode
 * @param collision C-struct to decode the message contents into
 */
static inline void mavlink_msg_collision_decode(const mavlink_message_t* msg, mavlink_collision_t* collision)
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
    collision->id = mavlink_msg_collision_get_id(msg);
    collision->time_to_minimum_delta = mavlink_msg_collision_get_time_to_minimum_delta(msg);
    collision->altitude_minimum_delta = mavlink_msg_collision_get_altitude_minimum_delta(msg);
    collision->horizontal_minimum_delta = mavlink_msg_collision_get_horizontal_minimum_delta(msg);
    collision->src = mavlink_msg_collision_get_src(msg);
    collision->action = mavlink_msg_collision_get_action(msg);
    collision->threat_level = mavlink_msg_collision_get_threat_level(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_COLLISION_LEN? msg->len : MAVLINK_MSG_ID_COLLISION_LEN;
    memset(collision, 0, MAVLINK_MSG_ID_COLLISION_LEN);
    memcpy(collision, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(collision, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
