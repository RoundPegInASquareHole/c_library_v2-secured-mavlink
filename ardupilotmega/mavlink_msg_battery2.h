#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE BATTERY2 PACKING

#define MAVLINK_MSG_ID_BATTERY2 181


typedef struct __mavlink_battery2_t {
 uint16_t voltage; /*< [mV] Voltage.*/
 int16_t current_battery; /*< [cA] Battery current, -1: autopilot does not measure the current.*/
} mavlink_battery2_t;

#define MAVLINK_MSG_ID_BATTERY2_LEN 4
#define MAVLINK_MSG_ID_BATTERY2_MIN_LEN 4
#define MAVLINK_MSG_ID_181_LEN 4
#define MAVLINK_MSG_ID_181_MIN_LEN 4

#define MAVLINK_MSG_ID_BATTERY2_CRC 174
#define MAVLINK_MSG_ID_181_CRC 174



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_BATTERY2 { \
    181, \
    "BATTERY2", \
    2, \
    {  { "voltage", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_battery2_t, voltage) }, \
         { "current_battery", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_battery2_t, current_battery) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_BATTERY2 { \
    "BATTERY2", \
    2, \
    {  { "voltage", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_battery2_t, voltage) }, \
         { "current_battery", NULL, MAVLINK_TYPE_INT16_T, 0, 2, offsetof(mavlink_battery2_t, current_battery) }, \
         } \
}
#endif

/**
 * @brief Pack a battery2 message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param voltage [mV] Voltage.
 * @param current_battery [cA] Battery current, -1: autopilot does not measure the current.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery2_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t voltage, int16_t current_battery)
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
    char buf[MAVLINK_MSG_ID_BATTERY2_LEN];
    _mav_put_uint16_t(buf, 0, voltage);
    _mav_put_int16_t(buf, 2, current_battery);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY2_LEN);
#else
    mavlink_battery2_t packet;
    packet.voltage = voltage;
    packet.current_battery = current_battery;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_BATTERY2_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_BATTERY2_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_battery2_t* battery2_final = (mavlink_battery2_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), battery2_final, MAVLINK_MSG_ID_BATTERY2_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_BATTERY2;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_BATTERY2_MIN_LEN, MAVLINK_MSG_ID_BATTERY2_LEN, MAVLINK_MSG_ID_BATTERY2_CRC);
}

/**
 * @brief Pack a battery2 message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param voltage [mV] Voltage.
 * @param current_battery [cA] Battery current, -1: autopilot does not measure the current.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_battery2_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t voltage,int16_t current_battery)
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
    char buf[MAVLINK_MSG_ID_BATTERY2_LEN];
    _mav_put_uint16_t(buf, 0, voltage);
    _mav_put_int16_t(buf, 2, current_battery);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_BATTERY2_LEN);
#else
    mavlink_battery2_t packet;
    packet.voltage = voltage;
    packet.current_battery = current_battery;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_BATTERY2_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_BATTERY2_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_battery2_t* battery2_final = (mavlink_battery2_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), battery2_final, MAVLINK_MSG_ID_BATTERY2_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_BATTERY2;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_BATTERY2_MIN_LEN, MAVLINK_MSG_ID_BATTERY2_LEN, MAVLINK_MSG_ID_BATTERY2_CRC);
}

/**
 * @brief Encode a battery2 struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param battery2 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battery2_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_battery2_t* battery2)
{
    return mavlink_msg_battery2_pack(system_id, component_id, msg, battery2->voltage, battery2->current_battery);
}

/**
 * @brief Encode a battery2 struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param battery2 C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_battery2_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_battery2_t* battery2)
{
    return mavlink_msg_battery2_pack_chan(system_id, component_id, chan, msg, battery2->voltage, battery2->current_battery);
}

/**
 * @brief Send a battery2 message
 * @param chan MAVLink channel to send the message
 *
 * @param voltage [mV] Voltage.
 * @param current_battery [cA] Battery current, -1: autopilot does not measure the current.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_battery2_send(mavlink_channel_t chan, uint16_t voltage, int16_t current_battery)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_BATTERY2_LEN];
    _mav_put_uint16_t(buf, 0, voltage);
    _mav_put_int16_t(buf, 2, current_battery);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY2, buf, MAVLINK_MSG_ID_BATTERY2_MIN_LEN, MAVLINK_MSG_ID_BATTERY2_LEN, MAVLINK_MSG_ID_BATTERY2_CRC);
#else
    mavlink_battery2_t packet;
    packet.voltage = voltage;
    packet.current_battery = current_battery;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY2, (const char *)&packet, MAVLINK_MSG_ID_BATTERY2_MIN_LEN, MAVLINK_MSG_ID_BATTERY2_LEN, MAVLINK_MSG_ID_BATTERY2_CRC);
#endif
}

/**
 * @brief Send a battery2 message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_battery2_send_struct(mavlink_channel_t chan, const mavlink_battery2_t* battery2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_battery2_send(chan, battery2->voltage, battery2->current_battery);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY2, (const char *)battery2, MAVLINK_MSG_ID_BATTERY2_MIN_LEN, MAVLINK_MSG_ID_BATTERY2_LEN, MAVLINK_MSG_ID_BATTERY2_CRC);
#endif
}

#if MAVLINK_MSG_ID_BATTERY2_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_battery2_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t voltage, int16_t current_battery)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, voltage);
    _mav_put_int16_t(buf, 2, current_battery);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY2, buf, MAVLINK_MSG_ID_BATTERY2_MIN_LEN, MAVLINK_MSG_ID_BATTERY2_LEN, MAVLINK_MSG_ID_BATTERY2_CRC);
#else
    mavlink_battery2_t *packet = (mavlink_battery2_t *)msgbuf;
    packet->voltage = voltage;
    packet->current_battery = current_battery;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_BATTERY2, (const char *)packet, MAVLINK_MSG_ID_BATTERY2_MIN_LEN, MAVLINK_MSG_ID_BATTERY2_LEN, MAVLINK_MSG_ID_BATTERY2_CRC);
#endif
}
#endif

#endif

// MESSAGE BATTERY2 UNPACKING


/**
 * @brief Get field voltage from battery2 message
 *
 * @return [mV] Voltage.
 */
static inline uint16_t mavlink_msg_battery2_get_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field current_battery from battery2 message
 *
 * @return [cA] Battery current, -1: autopilot does not measure the current.
 */
static inline int16_t mavlink_msg_battery2_get_current_battery(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  2);
}

/**
 * @brief Decode a battery2 message into a struct
 *
 * @param msg The message to decode
 * @param battery2 C-struct to decode the message contents into
 */
static inline void mavlink_msg_battery2_decode(const mavlink_message_t* msg, mavlink_battery2_t* battery2)
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
    battery2->voltage = mavlink_msg_battery2_get_voltage(msg);
    battery2->current_battery = mavlink_msg_battery2_get_current_battery(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_BATTERY2_LEN? msg->len : MAVLINK_MSG_ID_BATTERY2_LEN;
    memset(battery2, 0, MAVLINK_MSG_ID_BATTERY2_LEN);
    memcpy(battery2, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(battery2, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
