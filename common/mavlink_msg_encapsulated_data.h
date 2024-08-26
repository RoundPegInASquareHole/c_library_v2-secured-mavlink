#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE ENCAPSULATED_DATA PACKING

#define MAVLINK_MSG_ID_ENCAPSULATED_DATA 131


typedef struct __mavlink_encapsulated_data_t {
 uint16_t seqnr; /*<  sequence number (starting with 0 on every transmission)*/
 uint8_t data[253]; /*<  image data bytes*/
} mavlink_encapsulated_data_t;

#define MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN 255
#define MAVLINK_MSG_ID_ENCAPSULATED_DATA_MIN_LEN 255
#define MAVLINK_MSG_ID_131_LEN 255
#define MAVLINK_MSG_ID_131_MIN_LEN 255

#define MAVLINK_MSG_ID_ENCAPSULATED_DATA_CRC 223
#define MAVLINK_MSG_ID_131_CRC 223

#define MAVLINK_MSG_ENCAPSULATED_DATA_FIELD_DATA_LEN 253

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ENCAPSULATED_DATA { \
    131, \
    "ENCAPSULATED_DATA", \
    2, \
    {  { "seqnr", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_encapsulated_data_t, seqnr) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 253, 2, offsetof(mavlink_encapsulated_data_t, data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ENCAPSULATED_DATA { \
    "ENCAPSULATED_DATA", \
    2, \
    {  { "seqnr", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_encapsulated_data_t, seqnr) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 253, 2, offsetof(mavlink_encapsulated_data_t, data) }, \
         } \
}
#endif

/**
 * @brief Pack a encapsulated_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param seqnr  sequence number (starting with 0 on every transmission)
 * @param data  image data bytes
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_encapsulated_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t seqnr, const uint8_t *data)
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
    char buf[MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN];
    _mav_put_uint16_t(buf, 0, seqnr);
    _mav_put_uint8_t_array(buf, 2, data, 253);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN);
#else
    mavlink_encapsulated_data_t packet;
    packet.seqnr = seqnr;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*253);
            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_encapsulated_data_t* encapsulated_data_final = (mavlink_encapsulated_data_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), encapsulated_data_final, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_ENCAPSULATED_DATA;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ENCAPSULATED_DATA_MIN_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_CRC);
}

/**
 * @brief Pack a encapsulated_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param seqnr  sequence number (starting with 0 on every transmission)
 * @param data  image data bytes
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_encapsulated_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t seqnr,const uint8_t *data)
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
    char buf[MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN];
    _mav_put_uint16_t(buf, 0, seqnr);
    _mav_put_uint8_t_array(buf, 2, data, 253);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN);
#else
    mavlink_encapsulated_data_t packet;
    packet.seqnr = seqnr;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*253);
        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_encapsulated_data_t* encapsulated_data_final = (mavlink_encapsulated_data_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), encapsulated_data_final, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_ENCAPSULATED_DATA;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ENCAPSULATED_DATA_MIN_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_CRC);
}

/**
 * @brief Encode a encapsulated_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param encapsulated_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_encapsulated_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_encapsulated_data_t* encapsulated_data)
{
    return mavlink_msg_encapsulated_data_pack(system_id, component_id, msg, encapsulated_data->seqnr, encapsulated_data->data);
}

/**
 * @brief Encode a encapsulated_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param encapsulated_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_encapsulated_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_encapsulated_data_t* encapsulated_data)
{
    return mavlink_msg_encapsulated_data_pack_chan(system_id, component_id, chan, msg, encapsulated_data->seqnr, encapsulated_data->data);
}

/**
 * @brief Send a encapsulated_data message
 * @param chan MAVLink channel to send the message
 *
 * @param seqnr  sequence number (starting with 0 on every transmission)
 * @param data  image data bytes
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_encapsulated_data_send(mavlink_channel_t chan, uint16_t seqnr, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN];
    _mav_put_uint16_t(buf, 0, seqnr);
    _mav_put_uint8_t_array(buf, 2, data, 253);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCAPSULATED_DATA, buf, MAVLINK_MSG_ID_ENCAPSULATED_DATA_MIN_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_CRC);
#else
    mavlink_encapsulated_data_t packet;
    packet.seqnr = seqnr;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*253);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCAPSULATED_DATA, (const char *)&packet, MAVLINK_MSG_ID_ENCAPSULATED_DATA_MIN_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_CRC);
#endif
}

/**
 * @brief Send a encapsulated_data message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_encapsulated_data_send_struct(mavlink_channel_t chan, const mavlink_encapsulated_data_t* encapsulated_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_encapsulated_data_send(chan, encapsulated_data->seqnr, encapsulated_data->data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCAPSULATED_DATA, (const char *)encapsulated_data, MAVLINK_MSG_ID_ENCAPSULATED_DATA_MIN_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_CRC);
#endif
}

#if MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_encapsulated_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t seqnr, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, seqnr);
    _mav_put_uint8_t_array(buf, 2, data, 253);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCAPSULATED_DATA, buf, MAVLINK_MSG_ID_ENCAPSULATED_DATA_MIN_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_CRC);
#else
    mavlink_encapsulated_data_t *packet = (mavlink_encapsulated_data_t *)msgbuf;
    packet->seqnr = seqnr;
    mav_array_memcpy(packet->data, data, sizeof(uint8_t)*253);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ENCAPSULATED_DATA, (const char *)packet, MAVLINK_MSG_ID_ENCAPSULATED_DATA_MIN_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN, MAVLINK_MSG_ID_ENCAPSULATED_DATA_CRC);
#endif
}
#endif

#endif

// MESSAGE ENCAPSULATED_DATA UNPACKING


/**
 * @brief Get field seqnr from encapsulated_data message
 *
 * @return  sequence number (starting with 0 on every transmission)
 */
static inline uint16_t mavlink_msg_encapsulated_data_get_seqnr(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field data from encapsulated_data message
 *
 * @return  image data bytes
 */
static inline uint16_t mavlink_msg_encapsulated_data_get_data(const mavlink_message_t* msg, uint8_t *data)
{
    return _MAV_RETURN_uint8_t_array(msg, data, 253,  2);
}

/**
 * @brief Decode a encapsulated_data message into a struct
 *
 * @param msg The message to decode
 * @param encapsulated_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_encapsulated_data_decode(const mavlink_message_t* msg, mavlink_encapsulated_data_t* encapsulated_data)
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
    encapsulated_data->seqnr = mavlink_msg_encapsulated_data_get_seqnr(msg);
    mavlink_msg_encapsulated_data_get_data(msg, encapsulated_data->data);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN? msg->len : MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN;
    memset(encapsulated_data, 0, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN);
    memcpy(encapsulated_data, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(encapsulated_data, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
