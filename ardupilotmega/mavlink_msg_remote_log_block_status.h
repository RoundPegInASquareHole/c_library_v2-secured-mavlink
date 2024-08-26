#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE REMOTE_LOG_BLOCK_STATUS PACKING

#define MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS 185


typedef struct __mavlink_remote_log_block_status_t {
 uint32_t seqno; /*<  Log data block sequence number.*/
 uint8_t target_system; /*<  System ID.*/
 uint8_t target_component; /*<  Component ID.*/
 uint8_t status; /*<  Log data block status.*/
} mavlink_remote_log_block_status_t;

#define MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN 7
#define MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_MIN_LEN 7
#define MAVLINK_MSG_ID_185_LEN 7
#define MAVLINK_MSG_ID_185_MIN_LEN 7

#define MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_CRC 186
#define MAVLINK_MSG_ID_185_CRC 186



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_REMOTE_LOG_BLOCK_STATUS { \
    185, \
    "REMOTE_LOG_BLOCK_STATUS", \
    4, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_remote_log_block_status_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_remote_log_block_status_t, target_component) }, \
         { "seqno", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_remote_log_block_status_t, seqno) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_remote_log_block_status_t, status) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_REMOTE_LOG_BLOCK_STATUS { \
    "REMOTE_LOG_BLOCK_STATUS", \
    4, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_remote_log_block_status_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_remote_log_block_status_t, target_component) }, \
         { "seqno", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_remote_log_block_status_t, seqno) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_remote_log_block_status_t, status) }, \
         } \
}
#endif

/**
 * @brief Pack a remote_log_block_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param seqno  Log data block sequence number.
 * @param status  Log data block status.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_remote_log_block_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint32_t seqno, uint8_t status)
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
    char buf[MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, seqno);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);
    _mav_put_uint8_t(buf, 6, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN);
#else
    mavlink_remote_log_block_status_t packet;
    packet.seqno = seqno;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.status = status;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_remote_log_block_status_t* remote_log_block_status_final = (mavlink_remote_log_block_status_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), remote_log_block_status_final, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_CRC);
}

/**
 * @brief Pack a remote_log_block_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param seqno  Log data block sequence number.
 * @param status  Log data block status.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_remote_log_block_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint32_t seqno,uint8_t status)
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
    char buf[MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, seqno);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);
    _mav_put_uint8_t(buf, 6, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN);
#else
    mavlink_remote_log_block_status_t packet;
    packet.seqno = seqno;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.status = status;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_remote_log_block_status_t* remote_log_block_status_final = (mavlink_remote_log_block_status_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), remote_log_block_status_final, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_CRC);
}

/**
 * @brief Encode a remote_log_block_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param remote_log_block_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_remote_log_block_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_remote_log_block_status_t* remote_log_block_status)
{
    return mavlink_msg_remote_log_block_status_pack(system_id, component_id, msg, remote_log_block_status->target_system, remote_log_block_status->target_component, remote_log_block_status->seqno, remote_log_block_status->status);
}

/**
 * @brief Encode a remote_log_block_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param remote_log_block_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_remote_log_block_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_remote_log_block_status_t* remote_log_block_status)
{
    return mavlink_msg_remote_log_block_status_pack_chan(system_id, component_id, chan, msg, remote_log_block_status->target_system, remote_log_block_status->target_component, remote_log_block_status->seqno, remote_log_block_status->status);
}

/**
 * @brief Send a remote_log_block_status message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID.
 * @param target_component  Component ID.
 * @param seqno  Log data block sequence number.
 * @param status  Log data block status.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_remote_log_block_status_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint32_t seqno, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, seqno);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);
    _mav_put_uint8_t(buf, 6, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS, buf, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_CRC);
#else
    mavlink_remote_log_block_status_t packet;
    packet.seqno = seqno;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS, (const char *)&packet, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_CRC);
#endif
}

/**
 * @brief Send a remote_log_block_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_remote_log_block_status_send_struct(mavlink_channel_t chan, const mavlink_remote_log_block_status_t* remote_log_block_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_remote_log_block_status_send(chan, remote_log_block_status->target_system, remote_log_block_status->target_component, remote_log_block_status->seqno, remote_log_block_status->status);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS, (const char *)remote_log_block_status, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_remote_log_block_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint32_t seqno, uint8_t status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, seqno);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);
    _mav_put_uint8_t(buf, 6, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS, buf, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_CRC);
#else
    mavlink_remote_log_block_status_t *packet = (mavlink_remote_log_block_status_t *)msgbuf;
    packet->seqno = seqno;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS, (const char *)packet, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE REMOTE_LOG_BLOCK_STATUS UNPACKING


/**
 * @brief Get field target_system from remote_log_block_status message
 *
 * @return  System ID.
 */
static inline uint8_t mavlink_msg_remote_log_block_status_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field target_component from remote_log_block_status message
 *
 * @return  Component ID.
 */
static inline uint8_t mavlink_msg_remote_log_block_status_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field seqno from remote_log_block_status message
 *
 * @return  Log data block sequence number.
 */
static inline uint32_t mavlink_msg_remote_log_block_status_get_seqno(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field status from remote_log_block_status message
 *
 * @return  Log data block status.
 */
static inline uint8_t mavlink_msg_remote_log_block_status_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Decode a remote_log_block_status message into a struct
 *
 * @param msg The message to decode
 * @param remote_log_block_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_remote_log_block_status_decode(const mavlink_message_t* msg, mavlink_remote_log_block_status_t* remote_log_block_status)
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
    remote_log_block_status->seqno = mavlink_msg_remote_log_block_status_get_seqno(msg);
    remote_log_block_status->target_system = mavlink_msg_remote_log_block_status_get_target_system(msg);
    remote_log_block_status->target_component = mavlink_msg_remote_log_block_status_get_target_component(msg);
    remote_log_block_status->status = mavlink_msg_remote_log_block_status_get_status(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN? msg->len : MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN;
    memset(remote_log_block_status, 0, MAVLINK_MSG_ID_REMOTE_LOG_BLOCK_STATUS_LEN);
    memcpy(remote_log_block_status, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(remote_log_block_status, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
