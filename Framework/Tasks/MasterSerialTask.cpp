/*
 * MasterSerialTask.cpp
 *
 *  Created on: 02.02.2019
 *      Author: harald
 */

#include "MasterSerialTask.h"
#include "../Instances/Common.h"
#include "../Application/ThetaSensors/ID_Table.h"
#include "../Tasks/nRF24Task.h"


void StartMasterSerialTask(void const * argument)
{
	UNUSED(argument);

	ThetaMeasurement* msmnt = NULL;
	Messages::msg_nRF_theta_struct msg;
	uint8_t i;

	UART_TX_Socket* uart_tx_socket = new UART_TX_Socket(get_huart2());

	while (msmnt == NULL)
	{
		tx_printf("masterSerial: Waiting for sensors to initialize... ");
		msmnt       = get_remoteMsmt();

		osDelay(1000);
	}
	tx_printf("OK.\n");

	for(;;)
	{
		osDelay(MASTERSERAL_TASK_DELAY);
		//osDelay(3000);
		//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		for (i=0; i < ID_TABLE_LEN; i++)
		{
			const SensorDataType* const data = msmnt->get(i);

			if (!ThetaMeasurement::isValid(data->temperature))
				continue;

			Messages::prepare_uart_message(data, &msg);
			//bool result =
			uart_tx_socket->send_many_bytes(
					(uint8_t*) &msg, sizeof(Messages::msg_nRF_theta_struct));

			while(uart_tx_socket->is_TX_pending())
			{
				osDelay(1);
			}





			//tx_printf("%i ", (int)(msg.payload.theta * 100.0f));
			//tx_printf("%i: %i:%i:%i:%i:%i:%i:%i:%i / %i",        //%d.%d\n",
			/*tx_printf("%i: %i:%i:%i:%i / %i ",
					i,
					//msg.payload.sensor_id[0],
					//msg.payload.sensor_id[1],
					//msg.payload.sensor_id[2],
					//msg.payload.sensor_id[3],
					msg.payload.sensor_id[4],
					msg.payload.sensor_id[5],
					msg.payload.sensor_id[6],
					msg.payload.sensor_id[7],
					//(int) msg.payload.theta,
					//(int)((msg.payload.theta * 1000.0f) - (((int)msg.payload.theta) * 1000))
					(int)(msg.payload.theta * 100.0f)
			);*/



		}
		tx_printf("\n");
	}
}


UART_TX_Socket::UART_TX_Socket (UART_HandleTypeDef *huart)
{
	this->huart 	= huart;
}

bool UART_TX_Socket::send_byte(uint8_t byte)
{
	return send_many_bytes(&byte, 1);
}

bool UART_TX_Socket::send_many_bytes(uint8_t *ptr_to_data, uint8_t len, uint16_t timeout)
{
	uint16_t count = 0;
	HAL_UART_StateTypeDef uart_status = HAL_UART_GetState(huart);

	while ( ( (uart_status != HAL_UART_STATE_READY) &&
			(uart_status != HAL_UART_STATE_BUSY_RX) )  )
	{
		if(count >= timeout)
		{
			return ERROR;
		}

		osDelay(1);
		count++;
		uart_status = HAL_UART_GetState(huart);
	}

	HAL_UART_Transmit_DMA(huart, ptr_to_data, len);
	return SUCCESS;
}

bool UART_TX_Socket::is_TX_pending(void)
{
	HAL_UART_StateTypeDef usart_status = HAL_UART_GetState(huart);

	return
			( (usart_status == HAL_UART_STATE_BUSY_TX) ||
					(usart_status == HAL_UART_STATE_BUSY_TX_RX) );
}




