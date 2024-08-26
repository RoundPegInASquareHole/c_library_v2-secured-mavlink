#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE COMMAND_CANCEL PACKING

#define MAVLINK_MSG_ID_COMMAND_CANCEL 80


typedef struct __mavlink_command_cancel_t {
 uint16_t command; /*<  Command ID (of command to cancel).*/
 uint8_t target_system; /*<  System executing long running command. Should not be broadcast (0).*/
 uint8_t target_component; /*<  Component executing long running command.*/
} mavlink_command_cancel_t;

#define MAVLINK_MSG_ID_COMMAND_CANCEL_LEN 4
#define MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN 4
#define MAVLINK_MSG_ID_80_LEN 4
#define MAVLINK_MSG_ID_80_MIN_LEN 4

#define MAVLINK_MSG_ID_COMMAND_CANCEL_CRC 14
#define MAVLINK_MSG_ID_80_CRC 14



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_COMMAND_CANCEL { \
    80, \
    "COMMAND_CANCEL", \
    3, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_command_cancel_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_command_cancel_t, target_component) }, \
         { "command", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_command_cancel_t, command) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_COMMAND_CANCEL { \
    "COMMAND_CANCEL", \
    3, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_command_cancel_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_command_cancel_t, target_component) }, \
         { "command", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_command_cancel_t, command) }, \
         } \
}
#endif

/**
 * @brief Pack a command_cancel message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System executing long running command. Should not be broadcast (0).
 * @param target_component  Component executing long running command.
 * @param command  Command ID (of command to cancel).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_command_cancel_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint16_t command)
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
    char buf[MAVLINK_MSG_ID_COMMAND_CANCEL_LEN];
    _mav_put_uint16_t(buf, 0, command);
    _mav_put_uint8_t(buf, 2, target_system);
    _mav_put_uint8_t(buf, 3, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN);
#else
    mavlink_command_cancel_t packet;
    packet.command = command;
    packet.target_system = target_system;
    packet.target_component = target_component;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_COMMAND_CANCEL_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_command_cancel_t* command_cancel_final = (mavlink_command_cancel_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), command_cancel_final, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_COMMAND_CANCEL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_CRC);
}

/**
 * @brief Pack a command_cancel message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System executing long running command. Should not be broadcast (0).
 * @param target_component  Component executing long running command.
 * @param command  Command ID (of command to cancel).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_command_cancel_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint16_t command)
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
    char buf[MAVLINK_MSG_ID_COMMAND_CANCEL_LEN];
    _mav_put_uint16_t(buf, 0, command);
    _mav_put_uint8_t(buf, 2, target_system);
    _mav_put_uint8_t(buf, 3, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN);
#else
    mavlink_command_cancel_t packet;
    packet.command = command;
    packet.target_system = target_system;
    packet.target_component = target_component;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_COMMAND_CANCEL_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_command_cancel_t* command_cancel_final = (mavlink_command_cancel_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), command_cancel_final, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_COMMAND_CANCEL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_CRC);
}

/**
 * @brief Encode a command_cancel struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param command_cancel C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_command_cancel_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_command_cancel_t* command_cancel)
{
    return mavlink_msg_command_cancel_pack(system_id, component_id, msg, command_cancel->target_system, command_cancel->target_component, command_cancel->command);
}

/**
 * @brief Encode a command_cancel struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param command_cancel C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_command_cancel_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_command_cancel_t* command_cancel)
{
    return mavlink_msg_command_cancel_pack_chan(system_id, component_id, chan, msg, command_cancel->target_system, command_cancel->target_component, command_cancel->command);
}

/**
 * @brief Send a command_cancel message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System executing long running command. Should not be broadcast (0).
 * @param target_component  Component executing long running command.
 * @param command  Command ID (of command to cancel).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_command_cancel_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMMAND_CANCEL_LEN];
    _mav_put_uint16_t(buf, 0, command);
    _mav_put_uint8_t(buf, 2, target_system);
    _mav_put_uint8_t(buf, 3, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_CANCEL, buf, MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_CRC);
#else
    mavlink_command_cancel_t packet;
    packet.command = command;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_CANCEL, (const char *)&packet, MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_CRC);
#endif
}

/**
 * @brief Send a command_cancel message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_command_cancel_send_struct(mavlink_channel_t chan, const mavlink_command_cancel_t* command_cancel)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_command_cancel_send(chan, command_cancel->target_system, command_cancel->target_component, command_cancel->command);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_CANCEL, (const char *)command_cancel, MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_CRC);
#endif
}

#if MAVLINK_MSG_ID_COMMAND_CANCEL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_command_cancel_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint16_t command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, command);
    _mav_put_uint8_t(buf, 2, target_system);
    _mav_put_uint8_t(buf, 3, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_CANCEL, buf, MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_CRC);
#else
    mavlink_command_cancel_t *packet = (mavlink_command_cancel_t *)msgbuf;
    packet->command = command;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMMAND_CANCEL, (const char *)packet, MAVLINK_MSG_ID_COMMAND_CANCEL_MIN_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN, MAVLINK_MSG_ID_COMMAND_CANCEL_CRC);
#endif
}
#endif

#endif

// MESSAGE COMMAND_CANCEL UNPACKING


/**
 * @brief Get field target_system from command_cancel message
 *
 * @return  System executing long running command. Should not be broadcast (0).
 */
static inline uint8_t mavlink_msg_command_cancel_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field target_component from command_cancel message
 *
 * @return  Component executing long running command.
 */
static inline uint8_t mavlink_msg_command_cancel_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field command from command_cancel message
 *
 * @return  Command ID (of command to cancel).
 */
static inline uint16_t mavlink_msg_command_cancel_get_command(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a command_cancel message into a struct
 *
 * @param msg The message to decode
 * @param command_cancel C-struct to decode the message contents into
 */
static inline void mavlink_msg_command_cancel_decode(const mavlink_message_t* msg, mavlink_command_cancel_t* command_cancel)
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
    command_cancel->command = mavlink_msg_command_cancel_get_command(msg);
    command_cancel->target_system = mavlink_msg_command_cancel_get_target_system(msg);
    command_cancel->target_component = mavlink_msg_command_cancel_get_target_component(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_COMMAND_CANCEL_LEN? msg->len : MAVLINK_MSG_ID_COMMAND_CANCEL_LEN;
    memset(command_cancel, 0, MAVLINK_MSG_ID_COMMAND_CANCEL_LEN);
    memcpy(command_cancel, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(command_cancel, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
