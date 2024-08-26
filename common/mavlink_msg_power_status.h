#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE POWER_STATUS PACKING

#define MAVLINK_MSG_ID_POWER_STATUS 125


typedef struct __mavlink_power_status_t {
 uint16_t Vcc; /*< [mV] 5V rail voltage.*/
 uint16_t Vservo; /*< [mV] Servo rail voltage.*/
 uint16_t flags; /*<  Bitmap of power supply status flags.*/
} mavlink_power_status_t;

#define MAVLINK_MSG_ID_POWER_STATUS_LEN 6
#define MAVLINK_MSG_ID_POWER_STATUS_MIN_LEN 6
#define MAVLINK_MSG_ID_125_LEN 6
#define MAVLINK_MSG_ID_125_MIN_LEN 6

#define MAVLINK_MSG_ID_POWER_STATUS_CRC 203
#define MAVLINK_MSG_ID_125_CRC 203



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_POWER_STATUS { \
    125, \
    "POWER_STATUS", \
    3, \
    {  { "Vcc", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_power_status_t, Vcc) }, \
         { "Vservo", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_power_status_t, Vservo) }, \
         { "flags", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_power_status_t, flags) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_POWER_STATUS { \
    "POWER_STATUS", \
    3, \
    {  { "Vcc", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_power_status_t, Vcc) }, \
         { "Vservo", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_power_status_t, Vservo) }, \
         { "flags", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_power_status_t, flags) }, \
         } \
}
#endif

/**
 * @brief Pack a power_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Vcc [mV] 5V rail voltage.
 * @param Vservo [mV] Servo rail voltage.
 * @param flags  Bitmap of power supply status flags.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_power_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t Vcc, uint16_t Vservo, uint16_t flags)
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
    char buf[MAVLINK_MSG_ID_POWER_STATUS_LEN];
    _mav_put_uint16_t(buf, 0, Vcc);
    _mav_put_uint16_t(buf, 2, Vservo);
    _mav_put_uint16_t(buf, 4, flags);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POWER_STATUS_LEN);
#else
    mavlink_power_status_t packet;
    packet.Vcc = Vcc;
    packet.Vservo = Vservo;
    packet.flags = flags;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_POWER_STATUS_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_POWER_STATUS_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_power_status_t* power_status_final = (mavlink_power_status_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), power_status_final, MAVLINK_MSG_ID_POWER_STATUS_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_POWER_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_POWER_STATUS_MIN_LEN, MAVLINK_MSG_ID_POWER_STATUS_LEN, MAVLINK_MSG_ID_POWER_STATUS_CRC);
}

/**
 * @brief Pack a power_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Vcc [mV] 5V rail voltage.
 * @param Vservo [mV] Servo rail voltage.
 * @param flags  Bitmap of power supply status flags.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_power_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t Vcc,uint16_t Vservo,uint16_t flags)
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
    char buf[MAVLINK_MSG_ID_POWER_STATUS_LEN];
    _mav_put_uint16_t(buf, 0, Vcc);
    _mav_put_uint16_t(buf, 2, Vservo);
    _mav_put_uint16_t(buf, 4, flags);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POWER_STATUS_LEN);
#else
    mavlink_power_status_t packet;
    packet.Vcc = Vcc;
    packet.Vservo = Vservo;
    packet.flags = flags;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_POWER_STATUS_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_POWER_STATUS_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_power_status_t* power_status_final = (mavlink_power_status_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), power_status_final, MAVLINK_MSG_ID_POWER_STATUS_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_POWER_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_POWER_STATUS_MIN_LEN, MAVLINK_MSG_ID_POWER_STATUS_LEN, MAVLINK_MSG_ID_POWER_STATUS_CRC);
}

/**
 * @brief Encode a power_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param power_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_power_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_power_status_t* power_status)
{
    return mavlink_msg_power_status_pack(system_id, component_id, msg, power_status->Vcc, power_status->Vservo, power_status->flags);
}

/**
 * @brief Encode a power_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param power_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_power_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_power_status_t* power_status)
{
    return mavlink_msg_power_status_pack_chan(system_id, component_id, chan, msg, power_status->Vcc, power_status->Vservo, power_status->flags);
}

/**
 * @brief Send a power_status message
 * @param chan MAVLink channel to send the message
 *
 * @param Vcc [mV] 5V rail voltage.
 * @param Vservo [mV] Servo rail voltage.
 * @param flags  Bitmap of power supply status flags.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_power_status_send(mavlink_channel_t chan, uint16_t Vcc, uint16_t Vservo, uint16_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POWER_STATUS_LEN];
    _mav_put_uint16_t(buf, 0, Vcc);
    _mav_put_uint16_t(buf, 2, Vservo);
    _mav_put_uint16_t(buf, 4, flags);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_STATUS, buf, MAVLINK_MSG_ID_POWER_STATUS_MIN_LEN, MAVLINK_MSG_ID_POWER_STATUS_LEN, MAVLINK_MSG_ID_POWER_STATUS_CRC);
#else
    mavlink_power_status_t packet;
    packet.Vcc = Vcc;
    packet.Vservo = Vservo;
    packet.flags = flags;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_STATUS, (const char *)&packet, MAVLINK_MSG_ID_POWER_STATUS_MIN_LEN, MAVLINK_MSG_ID_POWER_STATUS_LEN, MAVLINK_MSG_ID_POWER_STATUS_CRC);
#endif
}

/**
 * @brief Send a power_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_power_status_send_struct(mavlink_channel_t chan, const mavlink_power_status_t* power_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_power_status_send(chan, power_status->Vcc, power_status->Vservo, power_status->flags);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_STATUS, (const char *)power_status, MAVLINK_MSG_ID_POWER_STATUS_MIN_LEN, MAVLINK_MSG_ID_POWER_STATUS_LEN, MAVLINK_MSG_ID_POWER_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_POWER_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_power_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t Vcc, uint16_t Vservo, uint16_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, Vcc);
    _mav_put_uint16_t(buf, 2, Vservo);
    _mav_put_uint16_t(buf, 4, flags);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_STATUS, buf, MAVLINK_MSG_ID_POWER_STATUS_MIN_LEN, MAVLINK_MSG_ID_POWER_STATUS_LEN, MAVLINK_MSG_ID_POWER_STATUS_CRC);
#else
    mavlink_power_status_t *packet = (mavlink_power_status_t *)msgbuf;
    packet->Vcc = Vcc;
    packet->Vservo = Vservo;
    packet->flags = flags;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_STATUS, (const char *)packet, MAVLINK_MSG_ID_POWER_STATUS_MIN_LEN, MAVLINK_MSG_ID_POWER_STATUS_LEN, MAVLINK_MSG_ID_POWER_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE POWER_STATUS UNPACKING


/**
 * @brief Get field Vcc from power_status message
 *
 * @return [mV] 5V rail voltage.
 */
static inline uint16_t mavlink_msg_power_status_get_Vcc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field Vservo from power_status message
 *
 * @return [mV] Servo rail voltage.
 */
static inline uint16_t mavlink_msg_power_status_get_Vservo(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field flags from power_status message
 *
 * @return  Bitmap of power supply status flags.
 */
static inline uint16_t mavlink_msg_power_status_get_flags(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Decode a power_status message into a struct
 *
 * @param msg The message to decode
 * @param power_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_power_status_decode(const mavlink_message_t* msg, mavlink_power_status_t* power_status)
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
    power_status->Vcc = mavlink_msg_power_status_get_Vcc(msg);
    power_status->Vservo = mavlink_msg_power_status_get_Vservo(msg);
    power_status->flags = mavlink_msg_power_status_get_flags(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_POWER_STATUS_LEN? msg->len : MAVLINK_MSG_ID_POWER_STATUS_LEN;
    memset(power_status, 0, MAVLINK_MSG_ID_POWER_STATUS_LEN);
    memcpy(power_status, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(power_status, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
