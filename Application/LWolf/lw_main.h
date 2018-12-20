/*
 * lw_main.h
 *
 *  Created on: 01.11.2018
 *      Author: harald
 */

#ifndef LW_MAIN_H_
#define LW_MAIN_H_

extern "C" {
#include "uart.h"
#include "nrf24.h"
}

#include "stm32f1xx_hal.h"


// C interface
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif



EXTERNC void lw_main(void);
EXTERNC void nRF24_loop(void);



#undef EXTERNC
#ifdef __cplusplus

// put cpp includes here!!



#endif // C interface
#endif /* LW_MAIN_H_ */
