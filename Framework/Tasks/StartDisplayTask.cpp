/*
 * StartDisplayTask.cpp
 *
 *  Created on: 22.12.2018
 *      Author: harald
 */


#include "StartDisplayTask.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "../Instances/Common.h"
#include "../System/uart_printf.h"
#include "../Tasks/nRF24Task.h"
#include "../Tasks/measureTask.h"
#include "../Application/Nokia_LCD/LCDFunctions.h"
#include "../libraries/HelpersLib.h"



LCDFunctions* lcd;


void clrTmpLine(char* tmpline, uint8_t len)
{
	for (uint8_t i=0; i < len; i++)
		tmpline[i] = ' ';
}

void StartDisplayTask(void const * argument)
{
	UNUSED(argument);

	lcd = new LCDFunctions();
	lcd->ISR_callback_fcn(); // Backlight on

	for(;;)
	{
		lcd->update();
		lcd->incPage();

		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		osDelay(3000);
	}



	/*for(;;)
	{
		uint8_t i;
		SensorDataType* get_dummy;
		ThetaMeasurement* lcl_msmnt = get_thetaMeasurement();
		ThetaMeasurement* rem_msmnt = get_remoteMsmt();


		osDelay(1000);
		//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		if (lcl_msmnt != NULL)
		{
			for (i=0; i < lcl_msmnt->get_sensorCount(); i++)
			{
				get_dummy = lcl_msmnt->get(i);

				tx_printf("Local %i: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X / %d.%d\n",
						i,
						get_dummy->sensor_ID[0],
						get_dummy->sensor_ID[1],
						get_dummy->sensor_ID[2],
						get_dummy->sensor_ID[3],
						get_dummy->sensor_ID[4],
						get_dummy->sensor_ID[5],
						get_dummy->sensor_ID[6],
						get_dummy->sensor_ID[7],
						(int) get_dummy->temperature,
						(int)((get_dummy->temperature * 1000.0f) - (((int)get_dummy->temperature) * 1000))	);
			}
		}

		if (rem_msmnt != NULL)
		{
			for (i=0; i < ID_TABLE_LEN; i++)
			{
				get_dummy = rem_msmnt->get(i);
				tx_printf("Remote %i: %d.%d\n",
						i,
						(int) get_dummy->temperature,
						(int)((get_dummy->temperature * 1000.0f) - (((int)get_dummy->temperature) * 1000))	);

				tx_printf("Remote %i: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X / %d.%d\n",
						i,
						get_dummy->sensor_ID[0],
						get_dummy->sensor_ID[1],
						get_dummy->sensor_ID[2],
						get_dummy->sensor_ID[3],
						get_dummy->sensor_ID[4],
						get_dummy->sensor_ID[5],
						get_dummy->sensor_ID[6],
						get_dummy->sensor_ID[7],
						(int) get_dummy->temperature,
						(int)((get_dummy->temperature * 1000.0f) - (((int)tmpSnsData->temperature) * 1000))	);
			}
			tx_printf("\n");
		}



	}*/


}


