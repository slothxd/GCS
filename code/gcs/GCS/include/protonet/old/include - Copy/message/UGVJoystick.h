#ifndef _UGV_JOYSTICK_H
#define _UGV_JOYSTICK_H

#include <marshal.h>
#include <message.h>

typedef struct UGV_joystick_s
{
    uint8_t vehicle_id;
    float32_t steering;
	float32_t throttle;
}UGV_joystick_t;

msg_offset pack_UGV_joystick(
        UGV_joystick_t* UGV_joystick,
		msg_offset offset);

msg_offset unpack_UGV_joystick(
		msg_offset offset,
        UGV_joystick_t* out_ptr);

void encode_UGV_joystick(
		uint8_t src_id, 
		uint8_t dest_id, 
		uint8_t msg_ttl, 
		uint8_t seq_number,
		UGV_joystick_t* tx_msg, 
		proto_msg_t* msg);

#endif
