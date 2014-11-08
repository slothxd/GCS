#ifndef _PING_H
#define _PING_H

#include <marshal.h>
#include <message.h>
typedef struct ping_s
{
	float64_t timestamp;
}ping_t;

msg_offset pack_ping(
		ping_t* ping,
		msg_offset offset);

msg_offset unpack_ping(
		msg_offset offset,
		ping_t* out_ptr);

void encode_ping(
		uint8_t src_id, 
		uint8_t dest_id, 
		uint8_t msg_ttl, 
		uint8_t seq_number,
		ping_t* tx_msg, 
		proto_msg_t* msg);

#endif