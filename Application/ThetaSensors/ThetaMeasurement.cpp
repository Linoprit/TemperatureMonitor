/*
 * ThetaMeasurement.cpp
 *
 *  Created on: 20.12.2018
 *      Author: harald
 */

#include "ThetaMeasurement.h"
#include <stdlib.h>
#include "../../Framework/System/uart_printf.h"


ThetaMeasurement::ThetaMeasurement(uint8_t devices_count)
{
	sensorData = static_cast<SensorDataType*>(
			malloc (sizeof(SensorDataType) * devices_count));
	sensorCount = devices_count;
}

void ThetaMeasurement::put(
		uint8_t pos, uint8_t sensor_ID[SENSOR_ID_LEN], float temperature)
{
	sensorData[pos].temperature = temperature;
	for(uint8_t i=0; i < SENSOR_ID_LEN; i++)
	{
		sensorData[pos].sensor_ID[i] = sensor_ID[i];
	}
}

SensorDataType* ThetaMeasurement::get(uint8_t pos) const
{
	return &sensorData[pos];
}

uint8_t ThetaMeasurement::update(uint8_t sensor_ID[SENSOR_ID_LEN], float temperature)
{
	for (uint8_t i=0; i < sensorCount; i++)
	{
		SensorDataType* actData = get(i);

		if (ID_Table::ID_is_same(actData->sensor_ID, sensor_ID))
		{
			actData->temperature = temperature;
			return SUCCESS;
		}
	}
	return ERROR;
}

ID_Table::StationType ThetaMeasurement::get_stationType(void)
{
	// if we get different station types from ID_Table, we round the result
	uint32_t stations = 0;

	for (uint8_t i=0; i < sensorCount; i++)
	{
		stations += ID_Table::get_stationNo(get(i)->sensor_ID);
	}

	float result = static_cast<float>(stations) / sensorCount;
	result = result + 0.5f;

	return static_cast<ID_Table::StationType>(result);
}

/* to be deleted

	tx_printf("Size of sensorData: %i / %i\n", sizeof(msm), sizeof(SensorDataType));

	SensorDataType dummy = { {0x28, 0xFF, 0x89, 0x0E, 0x02, 0x17, 0x03, 0x4A},  32.04f};
	for (uint8_t i=0; i<10; i++)
	{
		msm->put(i, dummy.sensor_ID, dummy.temperature);
		dummy.sensor_ID[7]++;
	}


	for (uint8_t i=0; i<10; i++)
	{
		SensorDataType* get_dummy = msm->get(i);
		tx_printf("%i get_dummy: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X / %i\n",
				i,
				get_dummy->sensor_ID[0],
				get_dummy->sensor_ID[1],
				get_dummy->sensor_ID[2],
				get_dummy->sensor_ID[3],
				get_dummy->sensor_ID[4],
				get_dummy->sensor_ID[5],
				get_dummy->sensor_ID[6],
				get_dummy->sensor_ID[7],
				(int) (get_dummy->temperature * 100.0f) );
	}


	for (uint8_t i=0; i<sensorCount; i++)
		{
			SensorDataType* get_dummy = msmnt->get(i);
			tx_printf("%i get_dummy: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X / %d.%d\n",
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

	dummy.sensor_ID[7]--;
	uint8_t updResult = msm->update(dummy.sensor_ID, -33.05f);

	if (updResult == ERROR)
		tx_printf("updating went wrong.\n");


	for (uint8_t i=0; i<10; i++)
	{
		SensorDataType* get_dummy = msm->get(i);
		tx_printf("%i updated: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X / %i\n",
				i,
				get_dummy->sensor_ID[0],
				get_dummy->sensor_ID[1],
				get_dummy->sensor_ID[2],
				get_dummy->sensor_ID[3],
				get_dummy->sensor_ID[4],
				get_dummy->sensor_ID[5],
				get_dummy->sensor_ID[6],
				get_dummy->sensor_ID[7],
				(int) (get_dummy->temperature * 100.0f) );
	}




 */




