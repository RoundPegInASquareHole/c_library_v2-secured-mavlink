#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE MEMINFO PACKING

#define MAVLINK_MSG_ID_MEMINFO 152


typedef struct __mavlink_meminfo_t {
 uint16_t brkval; /*<  Heap top.*/
 uint16_t freemem; /*< [bytes] Free memory.*/
 uint32_t freemem32; /*< [bytes] Free memory (32 bit).*/
} mavlink_meminfo_t;

#define MAVLINK_MSG_ID_MEMINFO_LEN 8
#define MAVLINK_MSG_ID_MEMINFO_MIN_LEN 4
#define MAVLINK_MSG_ID_152_LEN 8
#define MAVLINK_MSG_ID_152_MIN_LEN 4

#define MAVLINK_MSG_ID_MEMINFO_CRC 208
#define MAVLINK_MSG_ID_152_CRC 208



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MEMINFO { \
    152, \
    "MEMINFO", \
    3, \
    {  { "brkval", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_meminfo_t, brkval) }, \
         { "freemem", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_meminfo_t, freemem) }, \
         { "freemem32", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_meminfo_t, freemem32) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MEMINFO { \
    "MEMINFO", \
    3, \
    {  { "brkval", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_meminfo_t, brkval) }, \
         { "freemem", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_meminfo_t, freemem) }, \
         { "freemem32", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_meminfo_t, freemem32) }, \
         } \
}
#endif

/**
 * @brief Pack a meminfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param brkval  Heap top.
 * @param freemem [bytes] Free memory.
 * @param freemem32 [bytes] Free memory (32 bit).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_meminfo_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t brkval, uint16_t freemem, uint32_t freemem32)
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
    char buf[MAVLINK_MSG_ID_MEMINFO_LEN];
    _mav_put_uint16_t(buf, 0, brkval);
    _mav_put_uint16_t(buf, 2, freemem);
    _mav_put_uint32_t(buf, 4, freemem32);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MEMINFO_LEN);
#else
    mavlink_meminfo_t packet;
    packet.brkval = brkval;
    packet.freemem = freemem;
    packet.freemem32 = freemem32;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_MEMINFO_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_MEMINFO_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_meminfo_t* meminfo_final = (mavlink_meminfo_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), meminfo_final, MAVLINK_MSG_ID_MEMINFO_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_MEMINFO;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MEMINFO_MIN_LEN, MAVLINK_MSG_ID_MEMINFO_LEN, MAVLINK_MSG_ID_MEMINFO_CRC);
}

/**
 * @brief Pack a meminfo message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param brkval  Heap top.
 * @param freemem [bytes] Free memory.
 * @param freemem32 [bytes] Free memory (32 bit).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_meminfo_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t brkval,uint16_t freemem,uint32_t freemem32)
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
    char buf[MAVLINK_MSG_ID_MEMINFO_LEN];
    _mav_put_uint16_t(buf, 0, brkval);
    _mav_put_uint16_t(buf, 2, freemem);
    _mav_put_uint32_t(buf, 4, freemem32);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MEMINFO_LEN);
#else
    mavlink_meminfo_t packet;
    packet.brkval = brkval;
    packet.freemem = freemem;
    packet.freemem32 = freemem32;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_MEMINFO_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_MEMINFO_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_meminfo_t* meminfo_final = (mavlink_meminfo_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), meminfo_final, MAVLINK_MSG_ID_MEMINFO_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_MEMINFO;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MEMINFO_MIN_LEN, MAVLINK_MSG_ID_MEMINFO_LEN, MAVLINK_MSG_ID_MEMINFO_CRC);
}

/**
 * @brief Encode a meminfo struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param meminfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_meminfo_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_meminfo_t* meminfo)
{
    return mavlink_msg_meminfo_pack(system_id, component_id, msg, meminfo->brkval, meminfo->freemem, meminfo->freemem32);
}

/**
 * @brief Encode a meminfo struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param meminfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_meminfo_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_meminfo_t* meminfo)
{
    return mavlink_msg_meminfo_pack_chan(system_id, component_id, chan, msg, meminfo->brkval, meminfo->freemem, meminfo->freemem32);
}

/**
 * @brief Send a meminfo message
 * @param chan MAVLink channel to send the message
 *
 * @param brkval  Heap top.
 * @param freemem [bytes] Free memory.
 * @param freemem32 [bytes] Free memory (32 bit).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_meminfo_send(mavlink_channel_t chan, uint16_t brkval, uint16_t freemem, uint32_t freemem32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MEMINFO_LEN];
    _mav_put_uint16_t(buf, 0, brkval);
    _mav_put_uint16_t(buf, 2, freemem);
    _mav_put_uint32_t(buf, 4, freemem32);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEMINFO, buf, MAVLINK_MSG_ID_MEMINFO_MIN_LEN, MAVLINK_MSG_ID_MEMINFO_LEN, MAVLINK_MSG_ID_MEMINFO_CRC);
#else
    mavlink_meminfo_t packet;
    packet.brkval = brkval;
    packet.freemem = freemem;
    packet.freemem32 = freemem32;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEMINFO, (const char *)&packet, MAVLINK_MSG_ID_MEMINFO_MIN_LEN, MAVLINK_MSG_ID_MEMINFO_LEN, MAVLINK_MSG_ID_MEMINFO_CRC);
#endif
}

/**
 * @brief Send a meminfo message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_meminfo_send_struct(mavlink_channel_t chan, const mavlink_meminfo_t* meminfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_meminfo_send(chan, meminfo->brkval, meminfo->freemem, meminfo->freemem32);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEMINFO, (const char *)meminfo, MAVLINK_MSG_ID_MEMINFO_MIN_LEN, MAVLINK_MSG_ID_MEMINFO_LEN, MAVLINK_MSG_ID_MEMINFO_CRC);
#endif
}

#if MAVLINK_MSG_ID_MEMINFO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_meminfo_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t brkval, uint16_t freemem, uint32_t freemem32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, brkval);
    _mav_put_uint16_t(buf, 2, freemem);
    _mav_put_uint32_t(buf, 4, freemem32);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEMINFO, buf, MAVLINK_MSG_ID_MEMINFO_MIN_LEN, MAVLINK_MSG_ID_MEMINFO_LEN, MAVLINK_MSG_ID_MEMINFO_CRC);
#else
    mavlink_meminfo_t *packet = (mavlink_meminfo_t *)msgbuf;
    packet->brkval = brkval;
    packet->freemem = freemem;
    packet->freemem32 = freemem32;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MEMINFO, (const char *)packet, MAVLINK_MSG_ID_MEMINFO_MIN_LEN, MAVLINK_MSG_ID_MEMINFO_LEN, MAVLINK_MSG_ID_MEMINFO_CRC);
#endif
}
#endif

#endif

// MESSAGE MEMINFO UNPACKING


/**
 * @brief Get field brkval from meminfo message
 *
 * @return  Heap top.
 */
static inline uint16_t mavlink_msg_meminfo_get_brkval(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field freemem from meminfo message
 *
 * @return [bytes] Free memory.
 */
static inline uint16_t mavlink_msg_meminfo_get_freemem(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field freemem32 from meminfo message
 *
 * @return [bytes] Free memory (32 bit).
 */
static inline uint32_t mavlink_msg_meminfo_get_freemem32(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Decode a meminfo message into a struct
 *
 * @param msg The message to decode
 * @param meminfo C-struct to decode the message contents into
 */
static inline void mavlink_msg_meminfo_decode(const mavlink_message_t* msg, mavlink_meminfo_t* meminfo)
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
    meminfo->brkval = mavlink_msg_meminfo_get_brkval(msg);
    meminfo->freemem = mavlink_msg_meminfo_get_freemem(msg);
    meminfo->freemem32 = mavlink_msg_meminfo_get_freemem32(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_MEMINFO_LEN? msg->len : MAVLINK_MSG_ID_MEMINFO_LEN;
    memset(meminfo, 0, MAVLINK_MSG_ID_MEMINFO_LEN);
    memcpy(meminfo, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(meminfo, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
