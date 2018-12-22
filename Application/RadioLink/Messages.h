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


#define nRF_PAYLOAD_LEN				13 // nRF24 payload length for RX and TX

#define MSG_ID_STATISTICS			 5
#define MSG_ID_THETA 				15


class Messages {
public:

	enum msg_is_new_enum { statistics, thetas };

	typedef struct PACKED
	{
		uint8_t   msg_id = MSG_ID_STATISTICS;
		uint16_t  lostPkgCount;
		uint16_t  retransCount;
		uint8_t   relay_1;
		uint8_t	  relay_2;
		uint8_t   padding[ (nRF_PAYLOAD_LEN - 7) ];
	} msg_statistics_struct;

	// longest message
	typedef struct PACKED
	{
		uint8_t   msg_id = MSG_ID_THETA;
		uint8_t   sensor_id[8];
		float     theta;
	} msg_theta_struct;

	Messages();
	virtual ~Messages() {};

	static void prepare_payload(uint8_t* payload, uint8_t* data, uint8_t msg_type);
	void put_payload_to_struct(uint8_t *msg_buf);
	void set_msg_new(msg_is_new_enum arrived_msg);
	void set_msg_done(msg_is_new_enum arrived_msg);
	bool is_msg_new(msg_is_new_enum msg);

	msg_statistics_struct*		get_msg_statistics(void)    ;
	msg_theta_struct*			get_msg_theta(void)         ;


private:

	msg_statistics_struct		msg_statistics;
	msg_theta_struct			msg_theta;

	// set by put_payload_to_struct, reset by computing function
	bool new_messages[thetas];






};

#endif /* RADIOLINK_MESSAGES_H_ */
