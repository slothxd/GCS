/**@file This file was autogenerated. All changes will be undone. */

/** Message: Vehicle_Joystick_Command, ID: 1004*/

#ifndef _VEHICLE_JOYSTICK_COMMAND_H_
#define _VEHICLE_JOYSTICK_COMMAND_H_

#include <comnet_marshal.h>
#include <comnet_message.h>

#include"random_numbers.h"
#include "aes.h"
using CryptoPP::AES;
#include "ccm.h"
using CryptoPP::CFB_Mode;
typedef struct {
   float64_t timestamp;
   uint16_t vehicle_ID;
   float32_t steering;
   float32_t throttle;
} vehicle_joystick_command_t;

msg_offset pack_vehicle_joystick_command(
   vehicle_joystick_command_t* vehicle_joystick_command,
   msg_offset offset);

msg_offset unpack_vehicle_joystick_command(
   msg_offset offset,
   vehicle_joystick_command_t* out_ptr);

void encode_vehicle_joystick_command(
   uint8_t src_id,
   uint8_t dest_id,
   vehicle_joystick_command_t* tx_msg,
   com_msg_t* msg,
   uint8_t keyArr[]);//key for encryption CryptoPP

#endif