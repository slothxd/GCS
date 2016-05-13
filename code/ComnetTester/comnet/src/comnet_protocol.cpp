/* This file was autogenerated. All changes will be undone. */

#include <comnet_protocol.h>

const uint8_t msg_data_offset = 28;

void unpack_com_msg_t(
   com_msg_t* msg,
   com_msg_buf_t* buf)
{
   uint8_t* unpack_offset = msg->data+msg_data_offset;
   switch(msg->header.message_type)
   {
   case Com_Enter:
      unpack_enter(unpack_offset, &buf->enter);
      break;
   case Com_Ping:
      unpack_ping(unpack_offset, &buf->ping);
      break;
   case Com_Pong:
      unpack_pong(unpack_offset, &buf->pong);
      break;
   case Com_Exit:
      unpack_exit(unpack_offset, &buf->exit);
      break;
   case Com_Raw_Data:
      unpack_raw_data(unpack_offset, &buf->raw_data);
      break;
   case Com_Connection_Request:
      unpack_connection_request(unpack_offset, &buf->connection_request);
      break;
   case Com_Connection_Reply:
      unpack_connection_reply(unpack_offset, &buf->connection_reply);
      break;
   case Com_Vehicle_Identification:
      unpack_vehicle_identification(unpack_offset, &buf->vehicle_identification);
      break;
   case Com_Vehicle_Authorization_Request:
      unpack_vehicle_authorization_request(unpack_offset, &buf->vehicle_authorization_request);
      break;
   case Com_Vehicle_Authorization_Reply:
      unpack_vehicle_authorization_reply(unpack_offset, &buf->vehicle_authorization_reply);
      break;
   case Com_Vehicle_Mode_Command:
      unpack_vehicle_mode_command(unpack_offset, &buf->vehicle_mode_command);
      break;
   case Com_Vehicle_Joystick_Command:
      unpack_vehicle_joystick_command(unpack_offset, &buf->vehicle_joystick_command);
      break;
   case Com_Vehicle_Termination_Command:
      unpack_vehicle_termination_command(unpack_offset, &buf->vehicle_termination_command);
      break;
   case Com_Vehicle_Telemetry_Command:
      unpack_vehicle_telemetry_command(unpack_offset, &buf->vehicle_telemetry_command);
      break;
   case Com_Vehicle_System_Status:
      unpack_vehicle_system_status(unpack_offset, &buf->vehicle_system_status);
      break;
   case Com_Vehicle_Inertial_State:
      unpack_vehicle_inertial_state(unpack_offset, &buf->vehicle_inertial_state);
      break;
   case Com_Vehicle_Global_Position:
      unpack_vehicle_global_position(unpack_offset, &buf->vehicle_global_position);
      break;
   case Com_Vehicle_Body_Sensed_State:
      unpack_vehicle_body_sensed_state(unpack_offset, &buf->vehicle_body_sensed_state);
      break;
   case Com_Vehicle_Attitude:
      unpack_vehicle_attitude(unpack_offset, &buf->vehicle_attitude);
      break;
   case Com_Air_Vehicle_Ground_Relative_State:
      unpack_air_vehicle_ground_relative_state(unpack_offset, &buf->air_vehicle_ground_relative_state);
      break;
   case Com_Vehicle_Waypoint_Command:
      unpack_vehicle_waypoint_command(unpack_offset, &buf->vehicle_waypoint_command);
      break;
   case Com_Payload_Bay_Command:
      unpack_payload_bay_command(unpack_offset, &buf->payload_bay_command);
      break;
   case Com_Payload_Data_Recorder_Command:
      unpack_payload_data_recorder_command(unpack_offset, &buf->payload_data_recorder_command);
      break;
   case Com_Payload_Operation_Command:
      unpack_payload_operation_command(unpack_offset, &buf->payload_operation_command);
      break;
   case Com_Communications_Payload_Command:
      unpack_communications_payload_command(unpack_offset, &buf->communications_payload_command);
      break;
   case Com_Communications_Payload_Configuration_Command:
      unpack_communications_payload_configuration_command(unpack_offset, &buf->communications_payload_configuration_command);
      break;
   case Com_Payload_Bay_Mode_Command:
      unpack_payload_bay_mode_command(unpack_offset, &buf->payload_bay_mode_command);
      break;
   case Com_Payload_Bay_Status:
      unpack_payload_bay_status(unpack_offset, &buf->payload_bay_status);
      break;
   case Com_Payload_Data_Recorder_Status:
      unpack_payload_data_recorder_status(unpack_offset, &buf->payload_data_recorder_status);
      break;
   case Com_Payload_Operating_Status:
      unpack_payload_operating_status(unpack_offset, &buf->payload_operating_status);
      break;
   case Com_Communications_Payload_Status:
      unpack_communications_payload_status(unpack_offset, &buf->communications_payload_status);
      break;
   case Com_Target_Status:
      unpack_target_status(unpack_offset, &buf->target_status);
      break;
   case Com_Target_Acknowledgement:
      unpack_target_acknowledgement(unpack_offset, &buf->target_acknowledgement);
      break;
   case Com_Target_Designation_Command:
      unpack_target_designation_command(unpack_offset, &buf->target_designation_command);
      break;
   case Com_UAV_Location:
      unpack_UAV_location(unpack_offset, &buf->UAV_location);
      break;
   case Com_UAV_Speed:
      unpack_UAV_speed(unpack_offset, &buf->UAV_speed);
      break;
   case Com_UAV_Heading:
      unpack_UAV_heading(unpack_offset, &buf->UAV_heading);
      break;
   case Com_UAV_Battery:
      unpack_UAV_battery(unpack_offset, &buf->UAV_battery);
      break;
   case Com_UAV_Collision_Avodiance_Status:
      unpack_UAV_collision_avodiance_status(unpack_offset, &buf->UAV_collision_avodiance_status);
      break;
   case Com_UAV_Mission_Status:
      unpack_UAV_mission_status(unpack_offset, &buf->UAV_mission_status);
      break;
   case Com_UAV_Collision_Avodiance_Message:
      unpack_UAV_collision_avodiance_message(unpack_offset, &buf->UAV_collision_avodiance_message);
      break;
   case Com_UUV_Status:
      unpack_UUV_status(unpack_offset, &buf->UUV_status);
      break;
   case Com_ROV_Status_Message:
      unpack_ROV_status_message(unpack_offset, &buf->ROV_status_message);
      break;
   default:
      break;
   }
}

const char* com_typestr(com_msg_type_t msg_type)
{
   if(msg_type == Com_Enter)
   {
      return "Enter";
   }
   if(msg_type == Com_Ping)
   {
      return "Ping";
   }
   if(msg_type == Com_Pong)
   {
      return "Pong";
   }
   if(msg_type == Com_Exit)
   {
      return "Exit";
   }
   if(msg_type == Com_Raw_Data)
   {
      return "Raw Data";
   }
   if(msg_type == Com_Connection_Request)
   {
      return "Connection Request";
   }
   if(msg_type == Com_Connection_Reply)
   {
      return "Connection Reply";
   }
   if(msg_type == Com_Vehicle_Identification)
   {
      return "Vehicle Identification";
   }
   if(msg_type == Com_Vehicle_Authorization_Request)
   {
      return "Vehicle Authorization Request";
   }
   if(msg_type == Com_Vehicle_Authorization_Reply)
   {
      return "Vehicle Authorization Reply";
   }
   if(msg_type == Com_Vehicle_Mode_Command)
   {
      return "Vehicle Mode Command";
   }
   if(msg_type == Com_Vehicle_Joystick_Command)
   {
      return "Vehicle Joystick Command";
   }
   if(msg_type == Com_Vehicle_Termination_Command)
   {
      return "Vehicle Termination Command";
   }
   if(msg_type == Com_Vehicle_Telemetry_Command)
   {
      return "Vehicle Telemetry Command";
   }
   if(msg_type == Com_Vehicle_System_Status)
   {
      return "Vehicle System Status";
   }
   if(msg_type == Com_Vehicle_Inertial_State)
   {
      return "Vehicle Inertial State";
   }
   if(msg_type == Com_Vehicle_Global_Position)
   {
      return "Vehicle Global Position";
   }
   if(msg_type == Com_Vehicle_Body_Sensed_State)
   {
      return "Vehicle Body Sensed State";
   }
   if(msg_type == Com_Vehicle_Attitude)
   {
      return "Vehicle Attitude";
   }
   if(msg_type == Com_Air_Vehicle_Ground_Relative_State)
   {
      return "Air Vehicle Ground Relative State";
   }
   if(msg_type == Com_Vehicle_Waypoint_Command)
   {
      return "Vehicle Waypoint Command";
   }
   if(msg_type == Com_Payload_Bay_Command)
   {
      return "Payload Bay Command";
   }
   if(msg_type == Com_Payload_Data_Recorder_Command)
   {
      return "Payload Data Recorder Command";
   }
   if(msg_type == Com_Payload_Operation_Command)
   {
      return "Payload Operation Command";
   }
   if(msg_type == Com_Communications_Payload_Command)
   {
      return "Communications Payload Command";
   }
   if(msg_type == Com_Communications_Payload_Configuration_Command)
   {
      return "Communications Payload Configuration Command";
   }
   if(msg_type == Com_Payload_Bay_Mode_Command)
   {
      return "Payload Bay Mode Command";
   }
   if(msg_type == Com_Payload_Bay_Status)
   {
      return "Payload Bay Status";
   }
   if(msg_type == Com_Payload_Data_Recorder_Status)
   {
      return "Payload Data Recorder Status";
   }
   if(msg_type == Com_Payload_Operating_Status)
   {
      return "Payload Operating Status";
   }
   if(msg_type == Com_Communications_Payload_Status)
   {
      return "Communications Payload Status";
   }
   if(msg_type == Com_Target_Status)
   {
      return "Target Status";
   }
   if(msg_type == Com_Target_Acknowledgement)
   {
      return "Target Acknowledgement";
   }
   if(msg_type == Com_Target_Designation_Command)
   {
      return "Target Designation Command";
   }
   if(msg_type == Com_UAV_Location)
   {
      return "UAV Location";
   }
   if(msg_type == Com_UAV_Speed)
   {
      return "UAV Speed";
   }
   if(msg_type == Com_UAV_Heading)
   {
      return "UAV Heading";
   }
   if(msg_type == Com_UAV_Battery)
   {
      return "UAV Battery";
   }
   if(msg_type == Com_UAV_Collision_Avodiance_Status)
   {
      return "UAV Collision Avodiance Status";
   }
   if(msg_type == Com_UAV_Mission_Status)
   {
      return "UAV Mission Status";
   }
   if(msg_type == Com_UAV_Collision_Avodiance_Message)
   {
      return "UAV Collision Avodiance Message";
   }
   if(msg_type == Com_UUV_Status)
   {
      return "UUV Status";
   }
   if(msg_type == Com_ROV_Status_Message)
   {
      return "ROV Status Message";
   }
   return 0;
}