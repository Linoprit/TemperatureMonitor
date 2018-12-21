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
	/*pipe1 = new simpleRingbuffer(PIPE1_RB_LEN) ;
	pipe2 = new simpleRingbuffer(PIPE2_RB_LEN) ;
	pipe3 = new simpleRingbuffer(PIPE3_RB_LEN) ;*/
}


void nRF24L01_Basis::init(const ID_Table::StationType station)
{
	// RX/TX disabled
    nRF24->CE_L();

    // Configure the nRF24L01+
    tx_printf("nRF24L01+ check:");
    while (!nRF24->Check())
    {
    	tx_printf(" FAIL...");
    	osDelay(10);
    }
    tx_printf(" OK\n");

    nRF24->Init(); // Initialize the nRF24L01 to its default state

	nRF24->SetRFChannel(nRF24_CHANNEL);
	nRF24->SetDataRate(nRF24_DR_250kbps); //  2Mbps);
	nRF24->SetCRCScheme(nRF24_CRC_2byte);
	nRF24->SetAddrWidth(5);




	/*nRF24->SetAddr(nRF24_PIPE1, &nRF24_RX_ADDR1[0]);
	nRF24->SetRXPipe(nRF24_PIPE1, nRF24_AA_ON, 10); // TODO payload length = 10 here!
	nRF24->SetAddr(nRF24_PIPE2, &nRF24_RX_ADDR2[0]);
	nRF24->SetRXPipe(nRF24_PIPE2, nRF24_AA_ON, 10); // TODO Auto-ACK: enabled, payload length: 10 bytes

	nRF24->SetTXPower(nRF24_TXPWR_0dBm);
	nRF24->SetOperationalMode(nRF24_MODE_RX);
	nRF24->ClearIRQFlags();
	nRF24->SetPowerMode(nRF24_PWR_UP);
	nRF24->CE_H();


	gpio_callback_add((ISR_callback*) this);
	return;*/




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

		nRF24->SetAutoRetr(nRF24_ARD_2500us, 10);
		nRF24->EnableAA(nRF24_PIPE0);
		nRF24->SetOperationalMode(nRF24_MODE_TX);
	}

	nRF24->SetTXPower(nRF24_TXPWR_0dBm);
	nRF24->ClearIRQFlags();
	nRF24->SetPowerMode(nRF24_PWR_UP); // Wake the transceiver

	if (station == ID_Table::MASTER)
	{
		nRF24->SetAddr(nRF24_PIPE1, &nRF24_RX_ADDR1[0]);
		nRF24->SetRXPipe(nRF24_PIPE1, nRF24_AA_ON, 10); // TODO payload length = 10 here!
		nRF24->SetAddr(nRF24_PIPE2, &nRF24_RX_ADDR2[0]);
		nRF24->SetRXPipe(nRF24_PIPE2, nRF24_AA_ON, 10); // TODO Auto-ACK: enabled, payload length: 10 bytes

		nRF24->SetOperationalMode(nRF24_MODE_RX);
		nRF24->CE_H();
		gpio_callback_add((ISR_callback*) this);
	}









	// begin MASTER
	// Configure RX PIPES
	/*nRF24->SetAddr(nRF24_PIPE1, &nRF24_ADDR1[0]);
	nRF24->SetRXPipe(nRF24_PIPE1, nRF24_AA_ON, nRF_MAXBUFF_LEN);

	nRF24->SetAddr(nRF24_PIPE2, nRF24_ADDR2);
	nRF24->SetRXPipe(nRF24_PIPE2, nRF24_AA_ON, nRF_MAXBUFF_LEN);

	nRF24->SetAddr(nRF24_PIPE3, nRF24_ADDR3);
	nRF24->SetRXPipe(nRF24_PIPE3, nRF24_AA_ON, nRF_MAXBUFF_LEN);

	nRF24->SetTXPower(nRF24_TXPWR_0dBm);
	nRF24->SetOperationalMode(nRF24_MODE_RX);
	nRF24->ClearIRQFlags();
	nRF24->SetPowerMode(nRF24_PWR_UP); // Wake the transceiver

	nRF24->CE_H();

	*/
	// end MASTER


	tx_printf("Radio init done\n");


}


void nRF24L01_Basis::SlaveRequestReg(void)
{
	// Tx-addres = addr1
	// send Ping with 48Bit address of Theta Sensor 1
	// get 1-Byte address to use, store it
	// set Tx-address
	// done
}



void nRF24L01_Basis::ISR_callback_fcn (void)
{
	// Buffer to store a payload of maximum width
	uint8_t nRF24_payload[nRF_MAXBUFF_LEN];
	nRF24_RXResult pipe;
	uint8_t payload_length;

	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

	if (nRF24->GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
	{
		//pipe =
		pipe = nRF24->ReadPayload(nRF24_payload, &payload_length);
		nRF24->ClearIRQFlags();

		char	buffer[21];
		for (uint8_t l=0; l < payload_length; l++)
		{
			sprintf(&buffer[l*2], "%02X", (unsigned) nRF24_payload[l]);
		}
		buffer[20]='\0';
		tx_printf("PAYLOAD:>%s< TX: %i\n", buffer, pipe);
	}


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