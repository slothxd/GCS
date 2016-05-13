/**@file This file was autogenerated. All changes will be undone. */

/** Message: Vehicle_Waypoint_Command, ID: 2006*/

#ifndef _VEHICLE_WAYPOINT_COMMAND_H_
#define _VEHICLE_WAYPOINT_COMMAND_H_

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
   float32_t latitude;
   float32_t longitude;
   float32_t altitude;
} vehicle_waypoint_command_t;

msg_offset pack_vehicle_waypoint_command(
   vehicle_waypoint_command_t* vehicle_waypoint_command,
   msg_offset offset);

msg_offset unpack_vehicle_waypoint_command(
   msg_offset offset,
   vehicle_waypoint_command_t* out_ptr);

void encode_vehicle_waypoint_command(
   uint8_t src_id,
   uint8_t dest_id,
   vehicle_waypoint_command_t* tx_msg,
   com_msg_t* msg,
   uint8_t keyArr[]);//key for encryption CryptoPP

#endif