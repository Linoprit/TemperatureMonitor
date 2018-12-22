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
#include "Messages.h"


static constexpr uint8_t nRF24_CHANNEL 		= 115;
static constexpr uint32_t nRF24_WAIT_TIMEOUT = (uint32_t)0x000FFFFF;
static constexpr uint8_t nRF_AUTO_RETRY     = 10;

// TX addresses
static constexpr uint8_t nRF24_TX_ADDR1[] = { 'E', 'S', 'B', 'X', 'Z' }; // Slave 1
static constexpr uint8_t nRF24_TX_ADDR2[] = { 'E', 'S', 'B', 'X', 'Y' }; // Slave 2
// RX addresses
static constexpr uint8_t nRF24_RX_ADDR1[] = { 'E', 'S', 'B', 'X', 'Z' }; // Slave 1
static constexpr uint8_t nRF24_RX_ADDR2[1] = { 'Y' };                    // Slave 2

// Maximum of messages, stored by the ISR receiver
static constexpr uint8_t PIPE1_RB_LEN = nRF_PAYLOAD_LEN * 3;


class nRF24L01_Basis:
		ISR_callback
{
public:
	nRF24L01_Basis(NRF24L01* nrf24);
	virtual ~nRF24L01_Basis() {};

	void init(const ID_Table::StationType station);
	NRF24L01::nRF24_TXResult transmitPacket(uint8_t *pBuf, uint8_t length = nRF_PAYLOAD_LEN);

	NRF24L01* get_nRF24(void) 			{ return nRF24; 		};
	uint16_t  get_lostPkgCount(void) 	{ return lostPkgCount; 	};
	uint16_t  get_retransCount(void)    { return retransCount;	};
	void	  reset_stats(void)  		{ lostPkgCount = 0; retransCount = 0;		};
	void	  add_stats(uint8_t lostPkgCount, uint8_t retransCount);
	simpleRingbuffer* get_rx_ringbuffer(void) { return pipe1;	};

	void ISR_callback_fcn (void);

private:
	NRF24L01* nRF24;
	uint16_t  lostPkgCount;
	uint16_t  retransCount;
	simpleRingbuffer* pipe1; // only initialized in Master-mode

};

#endif /* RADIOLINK_NRF24L01_BASIS_H_ */
