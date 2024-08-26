#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE CHANGE_OPERATOR_CONTROL_ACK PACKING

#define MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK 6


typedef struct __mavlink_change_operator_control_ack_t {
 uint8_t gcs_system_id; /*<  ID of the GCS this message */
 uint8_t control_request; /*<  0: request control of this MAV, 1: Release control of this MAV*/
 uint8_t ack; /*<  0: ACK, 1: NACK: Wrong passkey, 2: NACK: Unsupported passkey encryption method, 3: NACK: Already under control*/
} mavlink_change_operator_control_ack_t;

#define MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN 3
#define MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_MIN_LEN 3
#define MAVLINK_MSG_ID_6_LEN 3
#define MAVLINK_MSG_ID_6_MIN_LEN 3

#define MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_CRC 104
#define MAVLINK_MSG_ID_6_CRC 104



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CHANGE_OPERATOR_CONTROL_ACK { \
    6, \
    "CHANGE_OPERATOR_CONTROL_ACK", \
    3, \
    {  { "gcs_system_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_change_operator_control_ack_t, gcs_system_id) }, \
         { "control_request", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_change_operator_control_ack_t, control_request) }, \
         { "ack", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_change_operator_control_ack_t, ack) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CHANGE_OPERATOR_CONTROL_ACK { \
    "CHANGE_OPERATOR_CONTROL_ACK", \
    3, \
    {  { "gcs_system_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_change_operator_control_ack_t, gcs_system_id) }, \
         { "control_request", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_change_operator_control_ack_t, control_request) }, \
         { "ack", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_change_operator_control_ack_t, ack) }, \
         } \
}
#endif

/**
 * @brief Pack a change_operator_control_ack message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param gcs_system_id  ID of the GCS this message 
 * @param control_request  0: request control of this MAV, 1: Release control of this MAV
 * @param ack  0: ACK, 1: NACK: Wrong passkey, 2: NACK: Unsupported passkey encryption method, 3: NACK: Already under control
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_change_operator_control_ack_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t gcs_system_id, uint8_t control_request, uint8_t ack)
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
    char buf[MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN];
    _mav_put_uint8_t(buf, 0, gcs_system_id);
    _mav_put_uint8_t(buf, 1, control_request);
    _mav_put_uint8_t(buf, 2, ack);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN);
#else
    mavlink_change_operator_control_ack_t packet;
    packet.gcs_system_id = gcs_system_id;
    packet.control_request = control_request;
    packet.ack = ack;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_change_operator_control_ack_t* change_operator_control_ack_final = (mavlink_change_operator_control_ack_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), change_operator_control_ack_final, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_MIN_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_CRC);
}

/**
 * @brief Pack a change_operator_control_ack message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param gcs_system_id  ID of the GCS this message 
 * @param control_request  0: request control of this MAV, 1: Release control of this MAV
 * @param ack  0: ACK, 1: NACK: Wrong passkey, 2: NACK: Unsupported passkey encryption method, 3: NACK: Already under control
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_change_operator_control_ack_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t gcs_system_id,uint8_t control_request,uint8_t ack)
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
    char buf[MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN];
    _mav_put_uint8_t(buf, 0, gcs_system_id);
    _mav_put_uint8_t(buf, 1, control_request);
    _mav_put_uint8_t(buf, 2, ack);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN);
#else
    mavlink_change_operator_control_ack_t packet;
    packet.gcs_system_id = gcs_system_id;
    packet.control_request = control_request;
    packet.ack = ack;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_change_operator_control_ack_t* change_operator_control_ack_final = (mavlink_change_operator_control_ack_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), change_operator_control_ack_final, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_MIN_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_CRC);
}

/**
 * @brief Encode a change_operator_control_ack struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param change_operator_control_ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_change_operator_control_ack_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_change_operator_control_ack_t* change_operator_control_ack)
{
    return mavlink_msg_change_operator_control_ack_pack(system_id, component_id, msg, change_operator_control_ack->gcs_system_id, change_operator_control_ack->control_request, change_operator_control_ack->ack);
}

/**
 * @brief Encode a change_operator_control_ack struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param change_operator_control_ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_change_operator_control_ack_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_change_operator_control_ack_t* change_operator_control_ack)
{
    return mavlink_msg_change_operator_control_ack_pack_chan(system_id, component_id, chan, msg, change_operator_control_ack->gcs_system_id, change_operator_control_ack->control_request, change_operator_control_ack->ack);
}

/**
 * @brief Send a change_operator_control_ack message
 * @param chan MAVLink channel to send the message
 *
 * @param gcs_system_id  ID of the GCS this message 
 * @param control_request  0: request control of this MAV, 1: Release control of this MAV
 * @param ack  0: ACK, 1: NACK: Wrong passkey, 2: NACK: Unsupported passkey encryption method, 3: NACK: Already under control
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_change_operator_control_ack_send(mavlink_channel_t chan, uint8_t gcs_system_id, uint8_t control_request, uint8_t ack)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN];
    _mav_put_uint8_t(buf, 0, gcs_system_id);
    _mav_put_uint8_t(buf, 1, control_request);
    _mav_put_uint8_t(buf, 2, ack);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK, buf, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_MIN_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_CRC);
#else
    mavlink_change_operator_control_ack_t packet;
    packet.gcs_system_id = gcs_system_id;
    packet.control_request = control_request;
    packet.ack = ack;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK, (const char *)&packet, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_MIN_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_CRC);
#endif
}

/**
 * @brief Send a change_operator_control_ack message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_change_operator_control_ack_send_struct(mavlink_channel_t chan, const mavlink_change_operator_control_ack_t* change_operator_control_ack)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_change_operator_control_ack_send(chan, change_operator_control_ack->gcs_system_id, change_operator_control_ack->control_request, change_operator_control_ack->ack);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK, (const char *)change_operator_control_ack, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_MIN_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_CRC);
#endif
}

#if MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_change_operator_control_ack_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t gcs_system_id, uint8_t control_request, uint8_t ack)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, gcs_system_id);
    _mav_put_uint8_t(buf, 1, control_request);
    _mav_put_uint8_t(buf, 2, ack);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK, buf, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_MIN_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_CRC);
#else
    mavlink_change_operator_control_ack_t *packet = (mavlink_change_operator_control_ack_t *)msgbuf;
    packet->gcs_system_id = gcs_system_id;
    packet->control_request = control_request;
    packet->ack = ack;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK, (const char *)packet, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_MIN_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_CRC);
#endif
}
#endif

#endif

// MESSAGE CHANGE_OPERATOR_CONTROL_ACK UNPACKING


/**
 * @brief Get field gcs_system_id from change_operator_control_ack message
 *
 * @return  ID of the GCS this message 
 */
static inline uint8_t mavlink_msg_change_operator_control_ack_get_gcs_system_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field control_request from change_operator_control_ack message
 *
 * @return  0: request control of this MAV, 1: Release control of this MAV
 */
static inline uint8_t mavlink_msg_change_operator_control_ack_get_control_request(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field ack from change_operator_control_ack message
 *
 * @return  0: ACK, 1: NACK: Wrong passkey, 2: NACK: Unsupported passkey encryption method, 3: NACK: Already under control
 */
static inline uint8_t mavlink_msg_change_operator_control_ack_get_ack(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a change_operator_control_ack message into a struct
 *
 * @param msg The message to decode
 * @param change_operator_control_ack C-struct to decode the message contents into
 */
static inline void mavlink_msg_change_operator_control_ack_decode(const mavlink_message_t* msg, mavlink_change_operator_control_ack_t* change_operator_control_ack)
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
    change_operator_control_ack->gcs_system_id = mavlink_msg_change_operator_control_ack_get_gcs_system_id(msg);
    change_operator_control_ack->control_request = mavlink_msg_change_operator_control_ack_get_control_request(msg);
    change_operator_control_ack->ack = mavlink_msg_change_operator_control_ack_get_ack(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN? msg->len : MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN;
    memset(change_operator_control_ack, 0, MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK_LEN);
    memcpy(change_operator_control_ack, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(change_operator_control_ack, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
