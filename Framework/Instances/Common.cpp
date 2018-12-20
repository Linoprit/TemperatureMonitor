/*
 * Initclasses.cpp
 *
 *  Created on: 06.05.2016
 *      Author: harald
 */


#include "Common.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "callbacks.h"


NRF24L01* 				Common::nRF24_device	= NULL;
Spi_socket*				Common::spi_socket		= NULL;
NRF24L01_GPIO* 			Common::nRF24_gpio		= NULL;
nRF24L01_Basis*			Common::nRF24_basis		= NULL;


// C interface
void common_init(void)	{ Common::init(); }


void Common::init()
{
	// switch off LED
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

#ifdef TRACE
	//errorMsg_comm 	= new uart_socket(get_huart1(), get_errorMsgTask());
	//error_msg		= new Error_messaging(errorMsg_comm);
#endif /* TRACE */


	spi_socket 		= new Spi_socket(get_nRF24_SPI());
	nRF24_gpio		= new NRF24L01_GPIO(
			NRF_CE_GPIO_Port,  NRF_CE_Pin,
			NRF_CSN_GPIO_Port, NRF_CSN_Pin,
			NRF_IRQ_GPIO_Port, NRF_IRQ_Pin	);
	nRF24_device 	= new NRF24L01(spi_socket, nRF24_gpio);
	nRF24_basis		= new nRF24L01_Basis(nRF24_device);



	// Workaround...
	//osSignalSet (*get_displayTask(), 0);

}


uint32_t Common::get_tick(void)
{
	return HAL_GetTick();
}





