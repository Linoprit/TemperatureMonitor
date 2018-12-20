/*
 * nRF24L01_Basis.h
 *
 *  Created on: 05.11.2018
 *      Author: harald
 */

#ifndef RADIOLINK_NRF24L01_BASIS_H_
#define RADIOLINK_NRF24L01_BASIS_H_


#include "../Framework/Instances/callbacks.h"
#include "../Framework/Devices/nRF24L01/nRF24L01.h"
#include "../Framework/libraries/simpleRingbuffer.h"



/*#define PIPE1_RB_LEN	nRF_MAXBUFF_LEN
#define PIPE2_RB_LEN	(3 * nRF_MAXBUFF_LEN)
#define PIPE3_RB_LEN	(3 * nRF_MAXBUFF_LEN)*/


static constexpr uint8_t nRF24_CHANNEL = 115;
static constexpr uint8_t nRF24_ADDR1[5] = { 'E', 'S', 'B', 'X', 'Z' }; // Pingchannel
static constexpr uint8_t nRF24_ADDR2[1] = { 'Y' }; // Datachannel
static constexpr uint8_t nRF24_ADDR3[1] = { 'A' }; // Datachannel


class nRF24L01_Basis:
		ISR_callback
{
public:
	nRF24L01_Basis(NRF24L01* nrf24);
	virtual ~nRF24L01_Basis() {};

	void init(void);
	void SlaveRequestReg(void);



	void ISR_callback_fcn (void);

private:
	NRF24L01* nRF24;


	/*simpleRingbuffer* pipe1;
	simpleRingbuffer* pipe2;
	simpleRingbuffer* pipe3;*/
};

#endif /* RADIOLINK_NRF24L01_BASIS_H_ */
