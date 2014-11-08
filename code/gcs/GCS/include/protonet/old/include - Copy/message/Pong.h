#ifndef _PONG_H
#define _PONG_H

#include <marshal.h>
#include <message.h>

typedef struct pong_s
{
	float64_t timestamp;
}pong_t;

msg_offset pack_pong(
		pong_t* Pong,
		msg_offset offset);

msg_offset unpack_pong(
		msg_offset offset,
		pong_t* out_ptr);

void encode_pong(
		uint8_t src_id, 
		uint8_t dest_id, 
		uint8_t msg_ttl, 
		uint8_t seq_number,
		pong_t* tx_msg, 
		proto_msg_t* msg);


#endif