/*
 * nRF24L01_Basis.cpp
 *
 *  Created on: 05.11.2018
 *      Author: harald
 */

#include "nRF24L01_Basis.h"
#include "../Inc/main.h"
#include "../Framework/Instances/Common.h"
#include "Messages.h"
#include "../Framework/Tasks/nRF24Task.h"

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
}

void nRF24L01_Basis::init()
{
	// RX/TX disabled
	nRF24->CE_L();
	ID_Table::StationType station = get_stationType();

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
	}

	if (station == ID_Table::SLAVE_02)
	{
		nRF24->SetAddr(nRF24_PIPETX, &nRF24_TX_ADDR2[0]); // program TX address
	}

	if (station == ID_Table::SLAVE_03)
	{
		nRF24->SetAddr(nRF24_PIPETX, &nRF24_TX_ADDR3[0]); // program TX address
	}

	if (station != ID_Table::MASTER)
	{
		nRF24->SetOperationalMode(nRF24_MODE_TX);
	}

	nRF24->DisableAA(0xFF); // Disable ShockBurst for all RX pipes
	nRF24->SetTXPower(nRF24_TXPWR_0dBm);
	nRF24->ClearIRQFlags();
	nRF24->SetPowerMode(nRF24_PWR_UP); // Wake the transceiver

	if (station == ID_Table::MASTER)
	{
		nRF24->SetOperationalMode(nRF24_MODE_RX);

		nRF24->SetAddr(nRF24_PIPE1, &nRF24_RX_ADDR1[0]);
		nRF24->SetRXPipe(nRF24_PIPE1, nRF24_AA_OFF, nRF_PAYLOAD_LEN);
		nRF24->SetAddr(nRF24_PIPE2, &nRF24_RX_ADDR2[0]);
		nRF24->SetRXPipe(nRF24_PIPE2, nRF24_AA_OFF, nRF_PAYLOAD_LEN);
		nRF24->SetAddr(nRF24_PIPE3, &nRF24_RX_ADDR3[0]);
		nRF24->SetRXPipe(nRF24_PIPE3, nRF24_AA_OFF, nRF_PAYLOAD_LEN);

		nRF24->CE_H();

		nRF24_callback_add((ISR_callback*) this);
	}

	tx_printf("Radio init done.\n");
}


NRF24L01::nRF24_TXResult nRF24L01_Basis::transmitPacket(
		uint8_t *pBuf, uint8_t length)
{
	volatile int32_t wait = nRF24_WAIT_TIMEOUT;
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

	if (wait <= 0) {
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


ID_Table::StationType nRF24L01_Basis::get_stationType(void)
{
	uint8_t station =
			(HAL_GPIO_ReadPin(StationCode1_GPIO_Port, StationCode1_Pin) << 1) |
			(HAL_GPIO_ReadPin(StationCode0_GPIO_Port, StationCode0_Pin) );

	return static_cast<ID_Table::StationType>(station);
}


void nRF24L01_Basis::ISR_callback_fcn (void)
{
	// TODO if we want to receive statistics, we need the pipe-info
	//nRF24_RXResult pipe;
	uint8_t payload_length;
	uint8_t nRF24_payload[nRF_PAYLOAD_LEN];

	// TODO remove ledblink
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);



	if (nRF24->GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
	{
		// pipe =
		nRF24->ReadPayload(nRF24_payload, &payload_length);
		nRF24->ClearIRQFlags();

		if (Common::nRF24_basis->get_stationType() == ID_Table::MASTER)
		{
			osPoolId* msg_pool 	= get_msg_pool();
			osMessageQId* queue = get_quue();

			if(payload_length != nRF_PAYLOAD_LEN)
				return;

			Messages::msg_dummy_struct* msg =
					(Messages::msg_dummy_struct*) osPoolAlloc(*msg_pool);

			for (uint8_t i=0; i < sizeof(Messages::msg_dummy_struct); i++)
			{
				msg->byte[i] = nRF24_payload[i];
			}

			osMessagePut(*queue, (uint32_t)msg, 0);
		}


	}
}
