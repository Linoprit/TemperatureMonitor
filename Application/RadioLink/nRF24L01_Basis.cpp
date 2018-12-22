/*
 * nRF24L01_Basis.cpp
 *
 *  Created on: 05.11.2018
 *      Author: harald
 */

#include "nRF24L01_Basis.h"
#include "../Framework/Instances/Common.h"
#include "Messages.h"

// Debugging
#include "../Framework/libraries/Arduino/WString.h"
#include "../Framework/libraries/HelpersLib.h"
#include "../Framework/System/uart_printf.h"
#include "../Framework/Instances/Common.h"





nRF24L01_Basis::nRF24L01_Basis(NRF24L01* nRF24)
{
	this->nRF24 = nRF24;
	lostPkgCount = 0;
	retransCount = 0;

	pipe1 = NULL;
	/*pipe2 = new simpleRingbuffer(PIPE2_RB_LEN) ;
	pipe3 = new simpleRingbuffer(PIPE3_RB_LEN) ;*/
}

void nRF24L01_Basis::init(const ID_Table::StationType station)
{
	// RX/TX disabled
    nRF24->CE_L();

    // Configure the nRF24L01+
    tx_printf("nRF24L01+ checking... ");
    while (!nRF24->Check())
    {
    	osDelay(10);
    }
    tx_printf(" OK\n");

    nRF24->Init(); // Initialize the nRF24L01 to its default state

	nRF24->SetRFChannel(nRF24_CHANNEL);
	nRF24->SetDataRate(nRF24_DR_250kbps); //  2Mbps);
	nRF24->SetCRCScheme(nRF24_CRC_2byte);
	nRF24->SetAddrWidth(5);

	if (station == ID_Table::SLAVE_01)
	{
		nRF24->SetAddr(nRF24_PIPETX, &nRF24_TX_ADDR1[0]); // program TX address
		nRF24->SetAddr(nRF24_PIPE0, &nRF24_TX_ADDR1[0]); // program address for pipe#0, must be same as TX (for Auto-ACK)
	}

	if (station == ID_Table::SLAVE_02)
	{
		nRF24->SetAddr(nRF24_PIPETX, &nRF24_TX_ADDR2[0]); // program TX address
		nRF24->SetAddr(nRF24_PIPE0, &nRF24_TX_ADDR2[0]); // program address for pipe#0, must be same as TX (for Auto-ACK)
	}

	if ( (station == ID_Table::SLAVE_02) ||  (station == ID_Table::SLAVE_01))
	{
		nRF24->SetAutoRetr(nRF24_ARD_2500us, nRF_AUTO_RETRY);
		nRF24->EnableAA(nRF24_PIPE0);
		nRF24->SetOperationalMode(nRF24_MODE_TX);
	}

	nRF24->SetTXPower(nRF24_TXPWR_0dBm);
	nRF24->ClearIRQFlags();
	nRF24->SetPowerMode(nRF24_PWR_UP); // Wake the transceiver

	if (station == ID_Table::MASTER)
	{
		pipe1 = new simpleRingbuffer(PIPE1_RB_LEN) ;

		nRF24->SetAddr(nRF24_PIPE1, &nRF24_RX_ADDR1[0]);
		nRF24->SetRXPipe(nRF24_PIPE1, nRF24_AA_ON, nRF_PAYLOAD_LEN);
		nRF24->SetAddr(nRF24_PIPE2, &nRF24_RX_ADDR2[0]);
		nRF24->SetRXPipe(nRF24_PIPE2, nRF24_AA_ON, nRF_PAYLOAD_LEN);

		nRF24->SetOperationalMode(nRF24_MODE_RX);
		nRF24->CE_H();
		gpio_callback_add((ISR_callback*) this);
	}

	tx_printf("Radio init done.\n");
}


NRF24L01::nRF24_TXResult nRF24L01_Basis::transmitPacket(
		uint8_t *pBuf, uint8_t length)
{
	volatile uint32_t wait = nRF24_WAIT_TIMEOUT;
	uint8_t otx;
	uint8_t otx_plos_cnt; // lost packet count
	uint8_t otx_arc_cnt;  // retransmit count
	uint8_t status;

	// Deassert the CE pin (in case if it still high)
	nRF24->CE_L();

	// Transfer a data from the specified buffer to the TX FIFO
	nRF24->WritePayload(pBuf, length);

	// Start a transmission by asserting CE pin (must be held at least 10us)
	nRF24->CE_H();

	// Poll the transceiver status register until one of the following flags will be set:
	//   TX_DS  - means the packet has been transmitted
	//   MAX_RT - means the maximum number of TX retransmits happened
	// note: this solution is far from perfect, better to use IRQ instead of polling the status
	do {
		status = nRF24->GetStatus();
		if (status & (nRF24_FLAG_TX_DS | nRF24_FLAG_MAX_RT)) {
			break;
		}
	} while (wait--);

	// Deassert the CE pin (Standby-II --> Standby-I)
	nRF24->CE_L();

	// Do statistics
	otx = nRF24->GetRetransmitCounters();
	otx_plos_cnt = (otx & nRF24_MASK_PLOS_CNT) >> 4; // packets lost counter
	otx_arc_cnt  = (otx & nRF24_MASK_ARC_CNT); // auto retransmissions counter
	add_stats(otx_plos_cnt, otx_arc_cnt);

	if (!wait) {
		return NRF24L01::nRF24_TX_TIMEOUT;
	}

	nRF24->ClearIRQFlags();

	if (status & nRF24_FLAG_MAX_RT) {
		// Auto retransmit counter exceeds the programmed maximum limit (FIFO is not removed)
		return NRF24L01::nRF24_TX_MAXRT;
	}

	if (status & nRF24_FLAG_TX_DS) {
		return NRF24L01::nRF24_TX_SUCCESS;
	}

	// Some banana happens, a payload remains in the TX FIFO, flush it
	nRF24->FlushTX();

	return NRF24L01::nRF24_TX_ERROR;
}


void nRF24L01_Basis::add_stats(uint8_t lostPkgCount, uint8_t retransCount)
{
	this->lostPkgCount += lostPkgCount;
	this->retransCount += retransCount;
}


void nRF24L01_Basis::ISR_callback_fcn (void)
{
	//nRF24_RXResult pipe;
	uint8_t payload_length;
	uint8_t nRF24_payload[nRF_PAYLOAD_LEN];

	// TODO if we want to receive statistics, we need the pipe-info

	if (nRF24->GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
	{
		// pipe =
		nRF24->ReadPayload(nRF24_payload, &payload_length);
		nRF24->ClearIRQFlags();

		/*char	buffer[21];
		for (uint8_t l=0; l < payload_length; l++)
		{
			sprintf(&buffer[l*2], "%02X", (unsigned) nRF24_payload[l]);
		}
		buffer[20]='\0';
		tx_printf("PAYLOAD:>%s< TX: %i\n", buffer, pipe);*/
	}

	if (pipe1 != NULL)
	{
		for(uint8_t i=0; i < payload_length; i++)
		{
			pipe1->Write(nRF24_payload[i]);
		}
	}

	// notify the controlling task, that data has arrived
	//osThreadId* task_to_notify = get_nRF24Task();
	//osSignalSet(*task_to_notify, 0x0);
	// for some reason, notification doesn't work.




	/*if (nRF24->GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
	{
		//pipe =
		nRF24->ReadPayload(nRF24_payload, &payload_length);
		nRF24->ClearIRQFlags();

		if (payload_length > nRF_MAXBUFF_LEN)
		{
			// TODO some error-action, LCD-Message or so...
			return;
		}


		char	buffer[21];
		for (uint8_t l=0; l < payload_length; l++)
		{
			sprintf(&buffer[l*2], "%02X", (unsigned) nRF24_payload[l]);
		}
		buffer[20]='\0';
		tx_printf("PAYLOAD:>%s< ... TX: ", buffer);

	}*/

}
