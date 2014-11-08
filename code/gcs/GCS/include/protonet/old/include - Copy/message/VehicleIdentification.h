#ifndef _VEHICLE_IDENIFICATION_H
#define _VEHICLE_IDENIFICATION_H

#include <marshal.h>
#include <message.h>

typedef struct vehicle_identification_s
{
	float64_t timestamp;
    uint8_t vehicle_ID;
    uint8_t vehicle_type;
    uint8_t owner_ID;
}vehicle_identification_t;

msg_offset pack_vehicle_identification(
        vehicle_identification_t* vehicle_identification,
		msg_offset offset);

msg_offset unpack_vehicle_identification(
		msg_offset offset,
        vehicle_identification_t* out_ptr);

void encode_vehicle_identification(
        uint8_t src_id,
        uint8_t dest_id,
        uint8_t msg_ttl,
        uint8_t seq_number,
        vehicle_identification_t* tx_msg,
        proto_msg_t* msg
        );

#endif
