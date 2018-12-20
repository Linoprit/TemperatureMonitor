/*
 * Messages.cpp
 *
 *  Created on: 10.11.2018
 *      Author: harald
 */

#include "Messages.h"
#include "../../Framework/Instances/Common.h"
#include "cmsis_os.h"





Messages::Messages()
{
	for (uint8_t i=0; i < Messages::thetas; i++)
		new_messages[i] = false;
}



void Messages::put_payload_to_struct(uint8_t* msg_buf)
{
	uint8_t *pointer = 0;

	switch (msg_buf[0])
	{
	case nRF_CMD_SWITCH_CHANNEL:
		pointer = (uint8_t *) &cmd_switch_channel;
		set_msg_new(switch_channel);
		break;

	case nRF_CMD_USE_ADDRESS:
		pointer = (uint8_t *) &cmd_use_address;
		set_msg_new(use_address);
		break;

	case nRF_MSG_PING:
		pointer = (uint8_t *) &msg_ping;
		set_msg_new(ping);
		break;

	case nRF_MSG_STATISTICS:
		pointer = (uint8_t *) &msg_statistics;
		set_msg_new(statistics);
		break;

	case nRF_MSG_THETA:
		pointer = (uint8_t *) &msg_theta;
		set_msg_new(thetas);
		break;

	default:
		pointer = 0;
		break;
	}

	if (pointer != 0)
	{
		for (unsigned int i = 0; i < nRF_MAXBUFF_LEN; i++)
		{
			*pointer = msg_buf[i];
			pointer++;
		}
	}

	// notify the corresponding task, that data has arrived
	osSignalSet (get_nRF24Task(), 0);

}

Messages::cmd_switch_channel_struct* Messages::get_cmd_switch_channel(void)
{
	return &cmd_switch_channel;
}

Messages::cmd_use_address_struct* Messages::get_cmd_use_address(void)
{
	return &cmd_use_address;
}

Messages::msg_ping_struct* Messages::get_msg_ping(void)
{
	return &msg_ping;
}

Messages::msg_statistics_struct* Messages::get_msg_statistics(void)
{
	return &msg_statistics;
}

Messages::msg_theta_struct*	Messages::get_msg_theta(void)
{
	return &msg_theta;
}

void Messages::set_msg_new(msg_is_new_enum arrived_msg)
{
	new_messages[arrived_msg] = true;
}

void Messages::set_msg_done(msg_is_new_enum arrived_msg)
{
	new_messages[arrived_msg] = false;
}

bool Messages::is_msg_new(msg_is_new_enum msg)
{
	return (new_messages[msg]);
}
