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


ow_t ow;
ow_rom_t rom_ids[20];
size_t sensorCount;
ThetaMeasurement* msmnt = NULL;


// C interface
void startMeasureTsk(void const * argument)
{
	UNUSED(argument);


	//tx_printf("Measurement Task is disabled\n");
	//osSignalWait (1, osWaitForever);


	size_t i;

	tx_printf("Init Measure Task...\n");
	ow_init(&ow, NULL);    // Initialize 1-Wire library and set user argument to NULL

	owr_t result = owERR;
	while (result != owOK)
	{
		result = ow_search_devices(
				&ow, &rom_ids[0], sizeof(rom_ids) / sizeof(rom_ids[0]), &sensorCount);

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

	msmnt = new ThetaMeasurement(sensorCount);
	for (i = 0; i < sensorCount; i++)
	{
		msmnt->put(i, rom_ids[i].rom, -255.0f);
	}

	for(;;)
	{
		//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		//tx_printf("\nStart temperature conversion\n");
		ow_ds18x20_start(&ow, NULL);  // Start conversion on all devices, use protected API
		osDelay(1000);                // Release thread for 1 second

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

		//osThreadYield();
	}

}


ThetaMeasurement* get_thetaMeasurement(void)
{
	return msmnt;
}

