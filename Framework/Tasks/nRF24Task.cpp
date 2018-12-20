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
#include "../../Application/ThetaSensors/ID_Table.h"



// C interface
void StartnRF24Tsk(void const * argument)
{
  UNUSED(argument);


/*for (uint8_t i=0; i < ID_TABLE_LEN; i++)
{
  tx_printf("Sens ID: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X / StationNo %i / relayNo %i / shortname %s \n",
		  theta_sensors_id_list[i].sensor_ID[0],
		  theta_sensors_id_list[i].sensor_ID[1],
		  theta_sensors_id_list[i].sensor_ID[2],
		  theta_sensors_id_list[i].sensor_ID[3],
		  theta_sensors_id_list[i].sensor_ID[4],
		  theta_sensors_id_list[i].sensor_ID[5],
		  theta_sensors_id_list[i].sensor_ID[6],
		  theta_sensors_id_list[i].sensor_ID[7],
		  theta_sensors_id_list[i].stationNo,
		  theta_sensors_id_list[i].relayNo,
		  &theta_sensors_id_list[i].shortname[0] );
}*/

  //ID_Table idTbl; //= new ID_Table();
  uint8_t  ID[SENSOR_ID_LEN] = { 0x28, 0xFF, 0x10, 0xC4, 0xC0, 0x17, 0x01, 0x8C };

  tx_printf("SlaveNr %i / shortName %s \n",
		  ID_Table::get_stationNo(ID),
		  ID_Table::get_shortname(ID)
		  );



  Common::nRF24_basis->init();

  for(;;)
	{

	  //tx_printf("Radio Task\n");
	  //osSignalWait (0, osWaitForever);
	  //osDelay(1000);
	  //Error_messaging::write("StartnRF24Tsk\n");

	   HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	   //osThreadYield();
	   osDelay(10);

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

}


