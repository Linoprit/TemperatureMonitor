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
#include "../Application/ThetaSensors/ID_Table.h"


static constexpr uint8_t nRF24_CHANNEL = 115;
// TX addresses
static constexpr uint8_t nRF24_TX_ADDR1[] = { 'E', 'S', 'B', 'X', 'Z' }; // Slave 1
static constexpr uint8_t nRF24_TX_ADDR2[] = { 'E', 'S', 'B', 'X', 'Y' }; // Slave 2
// RX addresses
static constexpr uint8_t nRF24_RX_ADDR1[] = { 'E', 'S', 'B', 'X', 'Z' }; // Slave 1
static constexpr uint8_t nRF24_RX_ADDR2[1] = { 'Y' }; // Slave 2


/*#define PIPE1_RB_LEN	nRF_MAXBUFF_LEN
#define PIPE2_RB_LEN	(3 * nRF_MAXBUFF_LEN)
#define PIPE3_RB_LEN	(3 * nRF_MAXBUFF_LEN)*/



class nRF24L01_Basis:
		ISR_callback
{
public:
	nRF24L01_Basis(NRF24L01* nrf24);
	virtual ~nRF24L01_Basis() {};

	void init(const ID_Table::StationType station);
	void SlaveRequestReg(void);
	NRF24L01* get_nRF24(void) { return nRF24; };


	void ISR_callback_fcn (void);

private:
	NRF24L01* nRF24;


	/*simpleRingbuffer* pipe1;
	simpleRingbuffer* pipe2;
	simpleRingbuffer* pipe3;*/
};

#endif /* RADIOLINK_NRF24L01_BASIS_H_ */
