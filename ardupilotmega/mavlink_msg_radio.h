#pragma once

#include <stdio.h>

/// \note Include encryption algorithms
#include "../chacha20.h"

// MESSAGE RADIO PACKING

#define MAVLINK_MSG_ID_RADIO 166


typedef struct __mavlink_radio_t {
 uint16_t rxerrors; /*<  Receive errors.*/
 uint16_t fixed; /*<  Count of error corrected packets.*/
 uint8_t rssi; /*<  Local signal strength.*/
 uint8_t remrssi; /*<  Remote signal strength.*/
 uint8_t txbuf; /*< [%] How full the tx buffer is.*/
 uint8_t noise; /*<  Background noise level.*/
 uint8_t remnoise; /*<  Remote background noise level.*/
} mavlink_radio_t;

#define MAVLINK_MSG_ID_RADIO_LEN 9
#define MAVLINK_MSG_ID_RADIO_MIN_LEN 9
#define MAVLINK_MSG_ID_166_LEN 9
#define MAVLINK_MSG_ID_166_MIN_LEN 9

#define MAVLINK_MSG_ID_RADIO_CRC 21
#define MAVLINK_MSG_ID_166_CRC 21



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_RADIO { \
    166, \
    "RADIO", \
    7, \
    {  { "rssi", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_radio_t, rssi) }, \
         { "remrssi", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_radio_t, remrssi) }, \
         { "txbuf", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_radio_t, txbuf) }, \
         { "noise", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_radio_t, noise) }, \
         { "remnoise", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_radio_t, remnoise) }, \
         { "rxerrors", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_radio_t, rxerrors) }, \
         { "fixed", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_radio_t, fixed) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_RADIO { \
    "RADIO", \
    7, \
    {  { "rssi", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_radio_t, rssi) }, \
         { "remrssi", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_radio_t, remrssi) }, \
         { "txbuf", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_radio_t, txbuf) }, \
         { "noise", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_radio_t, noise) }, \
         { "remnoise", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_radio_t, remnoise) }, \
         { "rxerrors", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_radio_t, rxerrors) }, \
         { "fixed", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_radio_t, fixed) }, \
         } \
}
#endif

/**
 * @brief Pack a radio message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param rssi  Local signal strength.
 * @param remrssi  Remote signal strength.
 * @param txbuf [%] How full the tx buffer is.
 * @param noise  Background noise level.
 * @param remnoise  Remote background noise level.
 * @param rxerrors  Receive errors.
 * @param fixed  Count of error corrected packets.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_radio_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t rssi, uint8_t remrssi, uint8_t txbuf, uint8_t noise, uint8_t remnoise, uint16_t rxerrors, uint16_t fixed)
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
    char buf[MAVLINK_MSG_ID_RADIO_LEN];
    _mav_put_uint16_t(buf, 0, rxerrors);
    _mav_put_uint16_t(buf, 2, fixed);
    _mav_put_uint8_t(buf, 4, rssi);
    _mav_put_uint8_t(buf, 5, remrssi);
    _mav_put_uint8_t(buf, 6, txbuf);
    _mav_put_uint8_t(buf, 7, noise);
    _mav_put_uint8_t(buf, 8, remnoise);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RADIO_LEN);
#else
    mavlink_radio_t packet;
    packet.rxerrors = rxerrors;
    packet.fixed = fixed;
    packet.rssi = rssi;
    packet.remrssi = remrssi;
    packet.txbuf = txbuf;
    packet.noise = noise;
    packet.remnoise = remnoise;

            
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_RADIO_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_RADIO_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_radio_t* radio_final = (mavlink_radio_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), radio_final, MAVLINK_MSG_ID_RADIO_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_RADIO;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RADIO_MIN_LEN, MAVLINK_MSG_ID_RADIO_LEN, MAVLINK_MSG_ID_RADIO_CRC);
}

/**
 * @brief Pack a radio message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rssi  Local signal strength.
 * @param remrssi  Remote signal strength.
 * @param txbuf [%] How full the tx buffer is.
 * @param noise  Background noise level.
 * @param remnoise  Remote background noise level.
 * @param rxerrors  Receive errors.
 * @param fixed  Count of error corrected packets.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_radio_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t rssi,uint8_t remrssi,uint8_t txbuf,uint8_t noise,uint8_t remnoise,uint16_t rxerrors,uint16_t fixed)
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
    char buf[MAVLINK_MSG_ID_RADIO_LEN];
    _mav_put_uint16_t(buf, 0, rxerrors);
    _mav_put_uint16_t(buf, 2, fixed);
    _mav_put_uint8_t(buf, 4, rssi);
    _mav_put_uint8_t(buf, 5, remrssi);
    _mav_put_uint8_t(buf, 6, txbuf);
    _mav_put_uint8_t(buf, 7, noise);
    _mav_put_uint8_t(buf, 8, remnoise);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RADIO_LEN);
#else
    mavlink_radio_t packet;
    packet.rxerrors = rxerrors;
    packet.fixed = fixed;
    packet.rssi = rssi;
    packet.remrssi = remrssi;
    packet.txbuf = txbuf;
    packet.noise = noise;
    packet.remnoise = remnoise;

        
    const char* packet_char = (const char*) &packet;
    
    uint8_t encrypt[MAVLINK_MSG_ID_RADIO_LEN];
    ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)packet_char, (uint8_t *)encrypt, MAVLINK_MSG_ID_RADIO_LEN);
    const char* encrypt_char = (const char*) &encrypt;
    
    mavlink_radio_t* radio_final = (mavlink_radio_t*)encrypt_char;
    memcpy(_MAV_PAYLOAD_NON_CONST(msg), radio_final, MAVLINK_MSG_ID_RADIO_LEN);
    
#endif

    msg->msgid = MAVLINK_MSG_ID_RADIO;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RADIO_MIN_LEN, MAVLINK_MSG_ID_RADIO_LEN, MAVLINK_MSG_ID_RADIO_CRC);
}

/**
 * @brief Encode a radio struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param radio C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_radio_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_radio_t* radio)
{
    return mavlink_msg_radio_pack(system_id, component_id, msg, radio->rssi, radio->remrssi, radio->txbuf, radio->noise, radio->remnoise, radio->rxerrors, radio->fixed);
}

/**
 * @brief Encode a radio struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param radio C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_radio_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_radio_t* radio)
{
    return mavlink_msg_radio_pack_chan(system_id, component_id, chan, msg, radio->rssi, radio->remrssi, radio->txbuf, radio->noise, radio->remnoise, radio->rxerrors, radio->fixed);
}

/**
 * @brief Send a radio message
 * @param chan MAVLink channel to send the message
 *
 * @param rssi  Local signal strength.
 * @param remrssi  Remote signal strength.
 * @param txbuf [%] How full the tx buffer is.
 * @param noise  Background noise level.
 * @param remnoise  Remote background noise level.
 * @param rxerrors  Receive errors.
 * @param fixed  Count of error corrected packets.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_radio_send(mavlink_channel_t chan, uint8_t rssi, uint8_t remrssi, uint8_t txbuf, uint8_t noise, uint8_t remnoise, uint16_t rxerrors, uint16_t fixed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RADIO_LEN];
    _mav_put_uint16_t(buf, 0, rxerrors);
    _mav_put_uint16_t(buf, 2, fixed);
    _mav_put_uint8_t(buf, 4, rssi);
    _mav_put_uint8_t(buf, 5, remrssi);
    _mav_put_uint8_t(buf, 6, txbuf);
    _mav_put_uint8_t(buf, 7, noise);
    _mav_put_uint8_t(buf, 8, remnoise);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RADIO, buf, MAVLINK_MSG_ID_RADIO_MIN_LEN, MAVLINK_MSG_ID_RADIO_LEN, MAVLINK_MSG_ID_RADIO_CRC);
#else
    mavlink_radio_t packet;
    packet.rxerrors = rxerrors;
    packet.fixed = fixed;
    packet.rssi = rssi;
    packet.remrssi = remrssi;
    packet.txbuf = txbuf;
    packet.noise = noise;
    packet.remnoise = remnoise;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RADIO, (const char *)&packet, MAVLINK_MSG_ID_RADIO_MIN_LEN, MAVLINK_MSG_ID_RADIO_LEN, MAVLINK_MSG_ID_RADIO_CRC);
#endif
}

/**
 * @brief Send a radio message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_radio_send_struct(mavlink_channel_t chan, const mavlink_radio_t* radio)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_radio_send(chan, radio->rssi, radio->remrssi, radio->txbuf, radio->noise, radio->remnoise, radio->rxerrors, radio->fixed);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RADIO, (const char *)radio, MAVLINK_MSG_ID_RADIO_MIN_LEN, MAVLINK_MSG_ID_RADIO_LEN, MAVLINK_MSG_ID_RADIO_CRC);
#endif
}

#if MAVLINK_MSG_ID_RADIO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_radio_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t rssi, uint8_t remrssi, uint8_t txbuf, uint8_t noise, uint8_t remnoise, uint16_t rxerrors, uint16_t fixed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, rxerrors);
    _mav_put_uint16_t(buf, 2, fixed);
    _mav_put_uint8_t(buf, 4, rssi);
    _mav_put_uint8_t(buf, 5, remrssi);
    _mav_put_uint8_t(buf, 6, txbuf);
    _mav_put_uint8_t(buf, 7, noise);
    _mav_put_uint8_t(buf, 8, remnoise);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RADIO, buf, MAVLINK_MSG_ID_RADIO_MIN_LEN, MAVLINK_MSG_ID_RADIO_LEN, MAVLINK_MSG_ID_RADIO_CRC);
#else
    mavlink_radio_t *packet = (mavlink_radio_t *)msgbuf;
    packet->rxerrors = rxerrors;
    packet->fixed = fixed;
    packet->rssi = rssi;
    packet->remrssi = remrssi;
    packet->txbuf = txbuf;
    packet->noise = noise;
    packet->remnoise = remnoise;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RADIO, (const char *)packet, MAVLINK_MSG_ID_RADIO_MIN_LEN, MAVLINK_MSG_ID_RADIO_LEN, MAVLINK_MSG_ID_RADIO_CRC);
#endif
}
#endif

#endif

// MESSAGE RADIO UNPACKING


/**
 * @brief Get field rssi from radio message
 *
 * @return  Local signal strength.
 */
static inline uint8_t mavlink_msg_radio_get_rssi(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field remrssi from radio message
 *
 * @return  Remote signal strength.
 */
static inline uint8_t mavlink_msg_radio_get_remrssi(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field txbuf from radio message
 *
 * @return [%] How full the tx buffer is.
 */
static inline uint8_t mavlink_msg_radio_get_txbuf(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field noise from radio message
 *
 * @return  Background noise level.
 */
static inline uint8_t mavlink_msg_radio_get_noise(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field remnoise from radio message
 *
 * @return  Remote background noise level.
 */
static inline uint8_t mavlink_msg_radio_get_remnoise(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field rxerrors from radio message
 *
 * @return  Receive errors.
 */
static inline uint16_t mavlink_msg_radio_get_rxerrors(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field fixed from radio message
 *
 * @return  Count of error corrected packets.
 */
static inline uint16_t mavlink_msg_radio_get_fixed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Decode a radio message into a struct
 *
 * @param msg The message to decode
 * @param radio C-struct to decode the message contents into
 */
static inline void mavlink_msg_radio_decode(const mavlink_message_t* msg, mavlink_radio_t* radio)
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
    radio->rxerrors = mavlink_msg_radio_get_rxerrors(msg);
    radio->fixed = mavlink_msg_radio_get_fixed(msg);
    radio->rssi = mavlink_msg_radio_get_rssi(msg);
    radio->remrssi = mavlink_msg_radio_get_remrssi(msg);
    radio->txbuf = mavlink_msg_radio_get_txbuf(msg);
    radio->noise = mavlink_msg_radio_get_noise(msg);
    radio->remnoise = mavlink_msg_radio_get_remnoise(msg);
#else
    uint8_t len = msg->len < MAVLINK_MSG_ID_RADIO_LEN? msg->len : MAVLINK_MSG_ID_RADIO_LEN;
    memset(radio, 0, MAVLINK_MSG_ID_RADIO_LEN);
    memcpy(radio, _MAV_PAYLOAD(msg), len); // this is the original way to decode the incomming payload

    //const char* payload = _MAV_PAYLOAD(msg);
            
    // printf("Encrypted data received from AP:\n");
    // hex_print((uint8_t *)payload, 0,len);
            
    //uint8_t decrypt[len];
    //ChaCha20XOR(chacha20_key, 1, nonce, (uint8_t *)payload, (uint8_t *)decrypt, len);
            
    //const char* decrypt_char = (const char*) &decrypt;
    //memcpy(radio, decrypt_char, len);

    // printf("Decrypted data received from AP:\n"); 
	// hex_print((uint8_t *)decrypt_char, 0,len);            
#endif
}
