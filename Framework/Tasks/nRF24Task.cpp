/*
 * dspCallbackTask.cpp
 *
 *  Created on: 06.07.2018
 *      Author: harald
 */


#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "../Instances/Common.h"
#include "../System/uart_printf.h"
#include "../Tasks/nRF24Task.h"
#include "../Application/RadioLink/nRF24L01_Basis.h"
#include "../../Application/ThetaSensors/ID_Table.h"
#include "../../Application/ThetaSensors/ThetaMeasurement.h"
#include "../Tasks/measureTask.h"



// C interface
void StartnRF24Tsk(void const * argument)
{
	UNUSED(argument);

	tx_printf("Init Radio Task...\n");

	ThetaMeasurement* msmnt = get_thetaMeasurement();
	while (msmnt == NULL)
	{
		tx_printf("Determining station type...\n");
		msmnt = get_thetaMeasurement();
		osDelay(1000);
	}

	ID_Table::StationType stationType = msmnt->get_stationType();
	tx_printf("stationtype: %i\n", stationType);

	NRF24L01* nRF24 = Common::nRF24_basis->get_nRF24();
	Common::nRF24_basis->init(msmnt->get_stationType());

	if (stationType == ID_Table::MASTER)
	{
		for(;;)
		{
			//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			osDelay(1000);
		}
	}

	if ( (stationType == ID_Table::SLAVE_02) ||  (stationType == ID_Table::SLAVE_01))
	{
		uint8_t payload_length = 10;
		char	buffer[21];
		uint8_t j = 0, i;
		uint8_t k = 0;
		uint8_t nRF24_payload[32];
		uint32_t packets_lost = 0; // global counter of lost packets
		uint8_t otx;
		uint8_t otx_plos_cnt; // lost packet count
		uint8_t otx_arc_cnt; // retransmit count
		NRF24L01::nRF24_TXResult tx_res;


		for(;;)
		{
			//osSignalWait (0, osWaitForever);
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			osDelay(1000);


			// Prepare data packet
			for (i = 0; i < payload_length; i++) {
				nRF24_payload[i] = j++;
				if (j > 0x000000FF) j = 0;
			}

			if (k == 0)
			{
				k++;
				nRF24->SetAddr(nRF24_PIPETX, &nRF24_TX_ADDR1[0]);
				nRF24->SetAddr(nRF24_PIPE0,  &nRF24_TX_ADDR1[0]);
			}
			else
			{
				k=0;
				nRF24->SetAddr(nRF24_PIPETX, &nRF24_TX_ADDR2[0]);
				nRF24->SetAddr(nRF24_PIPE0,  &nRF24_TX_ADDR2[0]);
			}

			// Print payload
			for (uint8_t l=0; l < payload_length; l++)
			{
				sprintf(&buffer[l*2], "%02X", (unsigned) nRF24_payload[l]);
			}
			buffer[20]='\0';
			tx_printf("PAYLOAD:>%s< ... TX: ", buffer);

			// Transmit a packet
			tx_res = nRF24->TransmitPacket(nRF24_payload, payload_length);
			otx = nRF24->GetRetransmitCounters();
			otx_plos_cnt = (otx & nRF24_MASK_PLOS_CNT) >> 4; // packets lost counter
			otx_arc_cnt  = (otx & nRF24_MASK_ARC_CNT); // auto retransmissions counter

			switch (tx_res) {
			case NRF24L01::nRF24_TX_SUCCESS:
				tx_printf("OK");
				break;
			case NRF24L01::nRF24_TX_TIMEOUT:
				tx_printf("TIMEOUT");
				break;
			case NRF24L01::nRF24_TX_MAXRT:
				tx_printf("MAX RETRANSMIT");
				packets_lost += otx_plos_cnt;
				nRF24->ResetPLOS();
				break;
			default:
				tx_printf("ERROR");
				break;
			}
			tx_printf("   ARC=%i LOST=%i\n", otx_arc_cnt, packets_lost);
		}


	}




		/*
	  // SLAVE
	  if (Common::messages->is_msg_new(Messages::switch_channel))
	  {
		  Common::messages->set_msg_done(Messages::switch_channel);
		  Common::nRF24_device->SetRFChannel(
				  Common::messages->get_cmd_switch_channel()->channel);
	  }

	  if (Common::messages->is_msg_new(Messages::use_address))
	  {
		  Common::messages->set_msg_done(Messages::use_address);
		  // program new TX address
		  Common::nRF24_device->SetAddr(
				  nRF24_PIPETX, Common::messages->get_cmd_use_address()->address);
	  }

	  // MASTER
	  if (Common::messages->is_msg_new(Messages::ping))
	  {
		  Common::messages->set_msg_done(Messages::ping);

		  uint8_t slaveNo =
				  ID_Table::get_slaveNo(Common::messages->get_msg_ping()->sens_id);

		  if (slaveNo == 1)
		  {
			  // TODO
			  // send cmd_use_address
		  }
		  else if (slaveNo == 2)
		  {
			  // TODO
			  // send cmd_use_address
		  }

	  }

	  if (Common::messages->is_msg_new(Messages::statistics))
	  {
		  Common::messages->set_msg_done(Messages::statistics);

	  }

	  if (Common::messages->is_msg_new(Messages::thetas))
	  {
		  Common::messages->set_msg_done(Messages::thetas);

	  }


	  // TODO wenn Theta-msg empfangen wurde, Temperatur anhand der ID in die
	  // entsprechende Klasse kopieren.

		 */


}


