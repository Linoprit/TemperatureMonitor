/*
 *
 *  Created on: 06.07.2018
 *      Author: harald
 */


#include "measureTask.h"

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "../Instances/Common.h"
#include "../Framework/Devices/ds18b20/ow.h"
#include "../Framework/Devices/ds18b20/ow_device_ds18x20.h"
#include "../Framework/Devices/ds18b20/scan_devices.h"
#include "../System/uart_printf.h"
#include "../../Framework/Tasks/nRF24Task.h"


ow_t ow;
ow_rom_t rom_ids[20];
size_t sensorCount;
ThetaMeasurement* msmnt = NULL;

void _scanSensors(void)
{
	size_t i;

	owr_t result = owERR;
	while (result != owOK)
	{
		result = ow_search_devices(
				&ow, &rom_ids[0], sizeof(rom_ids) / sizeof(rom_ids[0]), &sensorCount);

		tx_printf("Sensors found: %i\n", sensorCount);

		// scan oneWire-bus
		for (i = 0; i < sensorCount; i++)
		{
			if (ow_ds18x20_is_b(&ow, &rom_ids[i])) {
				float temp;
				ow_ds18x20_set_resolution(&ow, &rom_ids[i], 12);
				if (ow_ds18x20_read(&ow, &rom_ids[i], &temp))
				{
					tx_printf("Device ROM addr: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
							rom_ids[i].rom[0], rom_ids[i].rom[1], rom_ids[i].rom[2], rom_ids[i].rom[3],
							rom_ids[i].rom[4], rom_ids[i].rom[5], rom_ids[i].rom[6], rom_ids[i].rom[7]);
				}
				else
				{
					tx_printf("TempSensor scan error.\n");
					osDelay(1000);
				}
			}
		}
	}
}

void _initMeasurment(void)
{
	size_t i;

	if (Common::nRF24_basis->get_stationType() == ID_Table::MASTER)
	{
		msmnt = get_remoteMsmt();
	}
	else
	{
		msmnt = new ThetaMeasurement(sensorCount);
		for (i = 0; i < sensorCount; i++)
		{
			msmnt->put(i, rom_ids[i].rom, (float) INVLD_TEMPERATURE);
		}
	}
}

void _relayOnOff(uint8_t relayNo, bool on)
{
	GPIO_PinState state;
	if (on == true)
		state = GPIO_PIN_RESET;
	else
		state = GPIO_PIN_SET;

	if (relayNo == 1)
		HAL_GPIO_WritePin(RELAY_1__GPIO_Port, RELAY_1__Pin, state);

	if (relayNo == 2)
		HAL_GPIO_WritePin(RELAY_2__GPIO_Port, RELAY_2__Pin, state);
}

void _checkRelays(void)
{
	size_t i;
	for (i = 0; i < sensorCount; i++)
	{
		SensorDataType* const sensData   = msmnt->get(i);
		const theta_sens_type* idTblData = ID_Table::get_struct(sensData->sensor_ID);

		int32_t	tmpTheta      = (sensData->temperature + 0.05) * 10;
		int32_t ThetaThres_dn = idTblData->minTemp * 10;
		int32_t ThetaThres_up = (idTblData->minTemp + MIN_TEMP_HYSTERESIS) * 10;

		if(tmpTheta <= ThetaThres_dn)
		{
			_relayOnOff(idTblData->relayNo, true);
		}
		else if(tmpTheta > ThetaThres_up )
		{
			_relayOnOff(idTblData->relayNo, false);
		}
	}
}


void startMeasureTsk(void const * argument)
{
	UNUSED(argument);

	size_t i;

	tx_printf("Init Measure Task...\n");
	ow_init(&ow, NULL);    // Initialize 1-Wire library and set user argument to NULL

	osDelay(2000); // after power up, wait for sensors to wake
	_scanSensors();
	_initMeasurment();

	for(;;)
	{
		//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		//tx_printf("\nStart temperature conversion\n");

		ow_ds18x20_start(&ow, NULL);  // Start conversion on all devices, use protected API
		osDelay(1000);

		// Read temperature on all devices
		for (i = 0; i < sensorCount; i++)
		{
			if (ow_ds18x20_is_b(&ow, &rom_ids[i]))
			{
				float temperature;
				//uint8_t resolution = ow_ds18x20_get_resolution(&ow, &rom_ids[i]);
				if (ow_ds18x20_read(&ow, &rom_ids[i], &temperature))
				{
					msmnt->update(rom_ids[i].rom, temperature);
				}
			}
		}



		//tx_printf("relay on: GPIO_PIN_RESET\n" );
		//HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_PIN_RESET);
		//HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_RESET);
		//HAL_GPIO_WritePin(RELAY_2__GPIO_Port, RELAY_2__Pin, GPIO_PIN_RESET);
		//HAL_GPIO_WritePin(RELAY_1__GPIO_Port, RELAY_1__Pin, GPIO_PIN_RESET);

		/*tx_printf("relay off: GPIO_PIN_SET\n" );
		HAL_GPIO_WritePin(RELAY_11_GPIO_Port, RELAY_11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(RELAY_21_GPIO_Port, RELAY_21_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(RELAY_1__GPIO_Port, RELAY_1__Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(RELAY_2__GPIO_Port, RELAY_2__Pin, GPIO_PIN_SET);*/

		/*tx_printf("relay 1 off / 2 on \n" );
		HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1__Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2__Pin, GPIO_PIN_RESET);*/


		/*tx_printf("relay 1 on / 2 off \n" );
		HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1__Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2__Pin, GPIO_PIN_SET);*/

		_checkRelays();
		msmnt->incrementTimeouts();
		osDelay(TASK_DELAY);


		/*for (i=0; i < sensorCount; i++)
		{
			SensorDataType* get_dummy = msmnt->get(i);
			tx_printf("Sensor %i: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X / %d.%d\n",
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
		}*/

	}

}


ThetaMeasurement* get_thetaMeasurement(void)
{
	return msmnt;
}

