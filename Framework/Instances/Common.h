/*
 * Initclasses.h
 *
 *  Created on: 06.05.2016
 *      Author: harald
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"


#define TASK_DELAY 60000


// C interface
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void common_init(void);
//EXTERNC UART_HandleTypeDef* get_huart1(void); //only for tx_printf
EXTERNC SPI_HandleTypeDef*  get_nRF24_SPI(void);
EXTERNC SPI_HandleTypeDef*  get_LCD_SPI(void);
EXTERNC osThreadId* 		get_errorMsgTask(void);
EXTERNC osThreadId* 		get_nRF24Task(void);

#undef EXTERNC

#ifdef __cplusplus

// put cpp includes here!!
#include "../System/uart_printf.h"
#include "../Sockets/spi_socket.h"
#include "../Framework/Devices/nRF24L01/nRF24L01_GPIO.h"
#include "../Framework/Devices/nRF24L01/nRF24L01.h"
#include "../Application/RadioLink/nRF24L01_Basis.h"
#include "../Application/RadioLink/Messages.h"



class Common
{
public:

  Common() {};
  virtual ~Common() {};

  static void init(void);
  static uint32_t get_tick(void);

  static inline void delay(uint32_t delay)  { osDelay(delay); }//HAL_Delay(delay); }

  // TODO cleanup - use get-functions!!

  // sockets
  static Spi_socket*		nRF24_spi_socket;

  // system Classes
  // NOP

  // device Classes
  static NRF24L01_GPIO* 	nRF24_gpio;
  static NRF24L01* 	 		nRF24_device;

  // Application Classes
  static nRF24L01_Basis*	nRF24_basis;

private:



};

#endif // C interface
#endif /* COMMON_H_ */
