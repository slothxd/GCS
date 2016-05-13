/* This file was autogenerated. All changes will be undone. */

/* Message: Payload_Bay_Command, ID: 3000*/

#ifndef _PAYLOAD_BAY_COMMAND_H_
#define _PAYLOAD_BAY_COMMAND_H_

#include <comnet_marshal.h>
#include <comnet_message.h>

typedef struct {
   float64_t timestamp;
   uint32_t payload_ID;
   uint8_t payload_command;
} payload_bay_command_t;

msg_offset pack_payload_bay_command(
   payload_bay_command_t* payload_bay_command,
   msg_offset offset);

msg_offset unpack_payload_bay_command(
   msg_offset offset,
   payload_bay_command_t* out_ptr);

void encode_payload_bay_command(
   uint8_t src_id,
   uint8_t dest_id,
   uint8_t msg_ttl,
   uint8_t seq_number,
   payload_bay_command_t* tx_msg,
   proto_msg_t* msg);

#endif
