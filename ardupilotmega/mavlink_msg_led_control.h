#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE LED_CONTROL PACKING

#define MAVLINK_MSG_ID_LED_CONTROL 186


typedef struct __mavlink_led_control_t {
 uint8_t target_system; /*<  System ID.*/
 uint8_t target_component; /*<  Component ID.*/
 uint8_t instance; /*<  Instance (LED instance to control or 255 for all LEDs).*/
 uint8_t pattern; /*<  Pattern (see LED_PATTERN_ENUM).*/
 uint8_t custom_len; /*<  Custom Byte Length.*/
 uint8_t custom_bytes[24]; /*<  Custom Bytes.*/
} mavlink_led_control_t;

#define MAVLINK_MSG_ID_LED_CONTROL_LEN 29
#define MAVLINK_MSG_ID_LED_CONTROL_MIN_LEN 29
#define MAVLINK_MSG_ID_186_LEN 29
#define MAVLINK_MSG_ID_186_MIN_LEN 29

#define MAVLINK_MSG_ID_LED_CONTROL_CRC 72
#define MAVLINK_MSG_ID_186_CRC 72

#define MAVLINK_MSG_LED_CONTROL_FIELD_CUSTOM_BYTES_LEN 24

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LED_CONTROL { \
    186, \
    "LED_CONTROL", \
    6, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_led_control_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_led_control_t, target_component) }, \
         { "instance", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_led_control_t, instance) }, \
         { "pattern", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_led_control_t, pattern) }, \
         { "custom_len", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_led_control_t, custom_len) }, \
         { "custom_bytes", NULL, MAVLINK_TYPE_UINT8_T, 24, 5, offsetof(mavlink_led_control_t, custom_bytes) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LED_CONTROL { \
    "LED_CONTROL", \
    6, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_led_control_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_led_control_t, target_component) }, \
         { "instance", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_led_control_t, instance) }, \
         { "pattern", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_led_control_t, pattern) }, \
         { "custom_len", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_led_control_t, custom_len) }, \
         { "custom_bytes", NULL, MAVLINK_TYPE_UINT8_T, 24, 5, offsetof(mavlink_led_control_t, custom_bytes) }, \
         } \
}
#endif

/**
 * @brief Pack a led_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param instance  Instance (LED instance to control or 255 for all LEDs).
 * @param pattern  Pattern (see LED_PATTERN_ENUM).
 * @param custom_len  Custom Byte Length.
 * @param custom_bytes  Custom Bytes.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint8_t instance, uint8_t pattern, uint8_t custom_len, const uint8_t *custom_bytes)
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
    char buf[MAVLINK_MSG_ID_LED_CONTROL_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, instance);
    _mav_put_uint8_t(buf, 3, pattern);
    _mav_put_uint8_t(buf, 4, custom_len);
    _mav_put_uint8_t_array(buf, 5, custom_bytes, 24);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#else
    mavlink_led_control_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.instance = instance;
    packet.pattern = pattern;
    packet.custom_len = custom_len;
    mav_array_memcpy(packet.custom_bytes, custom_bytes, sizeof(uint8_t)*24);
            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_LED_CONTROL_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_LED_CONTROL_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_led_control_t* led_control_final = (mavlink_led_control_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), led_control_final, MAVLINK_MSG_ID_LED_CONTROL_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_LED_CONTROL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LED_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
}

/**
 * @brief Pack a led_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param instance  Instance (LED instance to control or 255 for all LEDs).
 * @param pattern  Pattern (see LED_PATTERN_ENUM).
 * @param custom_len  Custom Byte Length.
 * @param custom_bytes  Custom Bytes.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint8_t instance,uint8_t pattern,uint8_t custom_len,const uint8_t *custom_bytes)
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
    char buf[MAVLINK_MSG_ID_LED_CONTROL_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, instance);
    _mav_put_uint8_t(buf, 3, pattern);
    _mav_put_uint8_t(buf, 4, custom_len);
    _mav_put_uint8_t_array(buf, 5, custom_bytes, 24);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#else
    mavlink_led_control_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.instance = instance;
    packet.pattern = pattern;
    packet.custom_len = custom_len;
    mav_array_memcpy(packet.custom_bytes, custom_bytes, sizeof(uint8_t)*24);
        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_LED_CONTROL_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_LED_CONTROL_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_led_control_t* led_control_final = (mavlink_led_control_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), led_control_final, MAVLINK_MSG_ID_LED_CONTROL_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_LED_CONTROL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LED_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
}

/**
 * @brief Encode a led_control struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param led_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_led_control_t* led_control)
{
    return mavlink_msg_led_control_pack(system_id, component_id, msg, led_control->target_system, led_control->target_component, led_control->instance, led_control->pattern, led_control->custom_len, led_control->custom_bytes);
}

/**
 * @brief Encode a led_control struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param led_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_control_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_led_control_t* led_control)
{
    return mavlink_msg_led_control_pack_chan(system_id, component_id, chan, msg, led_control->target_system, led_control->target_component, led_control->instance, led_control->pattern, led_control->custom_len, led_control->custom_bytes);
}

/**
 * @brief Send a led_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param instance  Instance (LED instance to control or 255 for all LEDs).
 * @param pattern  Pattern (see LED_PATTERN_ENUM).
 * @param custom_len  Custom Byte Length.
 * @param custom_bytes  Custom Bytes.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_led_control_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t instance, uint8_t pattern, uint8_t custom_len, const uint8_t *custom_bytes)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LED_CONTROL_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, instance);
    _mav_put_uint8_t(buf, 3, pattern);
    _mav_put_uint8_t(buf, 4, custom_len);
    _mav_put_uint8_t_array(buf, 5, custom_bytes, 24);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, buf, MAVLINK_MSG_ID_LED_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    mavlink_led_control_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.instance = instance;
    packet.pattern = pattern;
    packet.custom_len = custom_len;
    mav_array_memcpy(packet.custom_bytes, custom_bytes, sizeof(uint8_t)*24);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_LED_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#endif
}

/**
 * @brief Send a led_control message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_led_control_send_struct(mavlink_channel_t chan, const mavlink_led_control_t* led_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_led_control_send(chan, led_control->target_system, led_control->target_component, led_control->instance, led_control->pattern, led_control->custom_len, led_control->custom_bytes);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, (const char *)led_control, MAVLINK_MSG_ID_LED_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#endif
}

#if MAVLINK_MSG_ID_LED_CONTROL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_led_control_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t instance, uint8_t pattern, uint8_t custom_len, const uint8_t *custom_bytes)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, instance);
    _mav_put_uint8_t(buf, 3, pattern);
    _mav_put_uint8_t(buf, 4, custom_len);
    _mav_put_uint8_t_array(buf, 5, custom_bytes, 24);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, buf, MAVLINK_MSG_ID_LED_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    mavlink_led_control_t *packet = (mavlink_led_control_t *)msgbuf;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->instance = instance;
    packet->pattern = pattern;
    packet->custom_len = custom_len;
    mav_array_memcpy(packet->custom_bytes, custom_bytes, sizeof(uint8_t)*24);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, (const char *)packet, MAVLINK_MSG_ID_LED_CONTROL_MIN_LEN, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#endif
}
#endif

#endif

// MESSAGE LED_CONTROL UNPACKING


/**
 * @brief Get field target_system from led_control message
 *
 * @return  System ID.
 */
static inline uint8_t mavlink_msg_led_control_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from led_control message
 *
 * @return  Component ID.
 */
static inline uint8_t mavlink_msg_led_control_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field instance from led_control message
 *
 * @return  Instance (LED instance to control or 255 for all LEDs).
 */
static inline uint8_t mavlink_msg_led_control_get_instance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field pattern from led_control message
 *
 * @return  Pattern (see LED_PATTERN_ENUM).
 */
static inline uint8_t mavlink_msg_led_control_get_pattern(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field custom_len from led_control message
 *
 * @return  Custom Byte Length.
 */
static inline uint8_t mavlink_msg_led_control_get_custom_len(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field custom_bytes from led_control message
 *
 * @return  Custom Bytes.
 */
static inline uint16_t mavlink_msg_led_control_get_custom_bytes(const mavlink_message_t* msg, uint8_t *custom_bytes)
{
    return _MAV_RETURN_uint8_t_array(msg, custom_bytes, 24,  5);
}

/**
 * @brief Decode a led_control message into a struct
 *
 * @param msg The message to decode
 * @param led_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_led_control_decode(const mavlink_message_t* msg, mavlink_led_control_t* led_control)
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
    led_control->target_system = mavlink_msg_led_control_get_target_system(msg);
    led_control->target_component = mavlink_msg_led_control_get_target_component(msg);
    led_control->instance = mavlink_msg_led_control_get_instance(msg);
    led_control->pattern = mavlink_msg_led_control_get_pattern(msg);
    led_control->custom_len = mavlink_msg_led_control_get_custom_len(msg);
    mavlink_msg_led_control_get_custom_bytes(msg, led_control->custom_bytes);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_LED_CONTROL_LEN? msg->len : MAVLINK_MSG_ID_LED_CONTROL_LEN;
    memset(led_control, 0, MAVLINK_MSG_ID_LED_CONTROL_LEN);
    memcpy(led_control, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(led_control, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
