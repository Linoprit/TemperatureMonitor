/*
 * Messages.h
 *
 *  Created on: 10.11.2018
 *      Author: harald
 */

#ifndef RADIOLINK_MESSAGES_H_
#define RADIOLINK_MESSAGES_H_

#include <stdint.h>

#define	 PACKED	__attribute__ ((packed))


#define nRF_MAXBUFF_LEN				 9
#define nRF_HEADER_LEN				 1

#define nRF_CMD_SWITCH_CHANNEL 		 1
#define nRF_CMD_USE_ADDRESS			 2

#define nRF_MSG_PING				10
#define nRF_MSG_STATISTICS			11
#define nRF_MSG_THETA 				12

#if ((THETA_MASTER + THETA_SLAVE) != 1)
#error "Define only THETA_MASTER or THETA_SLAVE!"
#endif


class Messages {
public:

	enum msg_is_new_enum { switch_channel, use_address, ping, statistics, thetas  };

	typedef struct PACKED
	{
		uint8_t  msg_id;
		uint8_t  channel;
		uint8_t  padding[ (nRF_MAXBUFF_LEN - 2) ];
	} cmd_switch_channel_struct;

	typedef struct PACKED
	{
		uint8_t  msg_id;
		uint8_t  address[5];
		uint8_t  padding[ (nRF_MAXBUFF_LEN - 6) ];
	} cmd_use_address_struct;

	typedef struct PACKED
	{
		uint8_t  msg_id;
		uint8_t  sens_id[6];
		uint8_t  padding[ (nRF_MAXBUFF_LEN - 7) ];
	} msg_ping_struct;

	typedef struct PACKED
	{
		uint8_t  msg_id;
		uint8_t  lost_packages;
		uint8_t  retries;		// mean over the last minute
		uint8_t  padding[ (nRF_MAXBUFF_LEN - 3) ];
	} msg_statistics_struct;

	// longest message 9 bytes
	typedef struct PACKED
	{
		uint8_t   msg_id;
		uint8_t   sensor_id[6];
		uint16_t  theta;
		//uint8_t  padding[ (nRF_MAXBUFF_LEN - 9) ];
	} msg_theta_struct;

	Messages();
	virtual ~Messages() {};

	void put_payload_to_struct(uint8_t *msg_buf);
	void set_msg_new(msg_is_new_enum arrived_msg);
	void set_msg_done(msg_is_new_enum arrived_msg);
	bool is_msg_new(msg_is_new_enum msg);

	cmd_switch_channel_struct* 	get_cmd_switch_channel(void);
	cmd_use_address_struct*		get_cmd_use_address(void)   ;
	msg_ping_struct*			get_msg_ping(void)          ;
	msg_statistics_struct*		get_msg_statistics(void)    ;
	msg_theta_struct*			get_msg_theta(void)         ;


private:
	cmd_switch_channel_struct 	cmd_switch_channel;
	cmd_use_address_struct		cmd_use_address;
	msg_ping_struct				msg_ping;
	msg_statistics_struct		msg_statistics;
	msg_theta_struct			msg_theta;

	// set by put_payload_to_struct, reset by computing function
	bool new_messages[thetas];


	/*
#if THETA_MASTER
	msg_theta_struct			msg_theta[5];
#endif
#if THETA_SLAVE
	msg_theta_struct			msg_theta[5];
#endif
	 */



};

#endif /* RADIOLINK_MESSAGES_H_ */
