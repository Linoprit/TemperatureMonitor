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
#include "../Application/RadioLink/Messages.h"
#include "../Application/ThetaSensors/ID_Table.h"
#include "../Tasks/measureTask.h"


ThetaMeasurement* remoteMsmt = NULL;
ThetaMeasurement* get_remoteMsmt(void) { return remoteMsmt; };


osPoolId  msg_pool;
osPoolId* get_msg_pool(void) { return &msg_pool; }

osMessageQId  queue;
osMessageQId* get_quue(void) {return &queue; }



void process_rx_data(Messages::msg_dummy_struct* msg)
{
	if(msg->byte[0] == MSG_ID_THETA)
	{
		if (remoteMsmt != NULL)
		{
			/*tx_printf("got ROM: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
					msg->byte[1], msg->byte[2], msg->byte[3], msg->byte[4],
					msg->byte[5], msg->byte[6], msg->byte[7], msg->byte[8]);*/

			float* theta = (float*) &msg->byte[9];
			remoteMsmt->update(&msg->byte[1], *theta);
		}
	}
}



// C interface
void StartnRF24Tsk(void const * argument)
{
	UNUSED(argument);

	ID_Table::StationType stationType = Common::nRF24_basis->get_stationType();

	tx_printf("Init Radio Task, stationtype is: , %i\n", stationType);

	Common::nRF24_basis->init();

	if (stationType == ID_Table::MASTER)
	{
		remoteMsmt = new ThetaMeasurement(); // no argument = Master mode

		osPoolDef(msg_pool, ID_TABLE_LEN, Messages::msg_dummy_struct);
		osMessageQDef(queue, ID_TABLE_LEN, Messages::msg_dummy_struct);

		msg_pool = osPoolCreate(osPool(msg_pool));
		queue    = osMessageCreate(osMessageQ(queue), NULL);

		for(;;)
		{
			//osDelay(1000);
			//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

			osEvent evt = osMessageGet(queue, 3000);// osWaitForever);
			if(evt.status == osEventTimeout)
				tx_printf("timeout ");

			if (evt.status == osEventMessage)
			{
				Messages::msg_dummy_struct* msg =
						(Messages::msg_dummy_struct*) evt.value.p;

				process_rx_data(msg);

				osPoolFree(msg_pool, msg);
			}
		}
	}

	if (stationType != ID_Table::MASTER)
	{
		uint8_t i;

		ThetaMeasurement* msmnt = get_thetaMeasurement();
		while (msmnt == NULL)
		{
			tx_printf("NRF: Waiting for sensors to initialize... ");
			msmnt = get_thetaMeasurement();
			osDelay(1000);
		}
		tx_printf("OK.\n");

		for(;;)
		{
			//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			//NRF24L01::nRF24_TXResult tx_res;

			for (i=0; i < msmnt->get_sensorCount(); i++)
			{
				Messages::msg_theta_struct msg;
				const SensorDataType* data = msmnt->get(i);

				for(uint8_t i=0; i < 8; i++)
				{
					msg.sensor_id[i] = data->sensor_ID[i];
				}
				msg.theta	  = data->temperature;

				//tx_res =
				Common::nRF24_basis->transmitPacket((uint8_t*) &msg);
			}

			// TODO will we send statistics?
			// TODO reset stats every hour, or so...
			osDelay(1000);
		}


		/*
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

		} */


	}

}


