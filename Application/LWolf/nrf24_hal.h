#ifndef __NRF24_HAL_H
#define __NRF24_HAL_H


// Hardware abstraction layer for NRF24L01+ transceiver (hardware depended functions)
// GPIO pins definition
// GPIO pins initialization and control functions
// SPI transmit functions


// Peripheral libraries
//#include <stm32f10x_gpio.h>
//#include <stm32f10x_spi.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal_uart.h"
#include <main.h>



extern SPI_HandleTypeDef* 		get_nRF24_SPI(void);
extern UART_HandleTypeDef* 	    get_huart1(void);

// SPI port peripheral
#define nRF24_SPI_PORT             SPI1

// nRF24 GPIO peripherals
//#define nRF24_GPIO_PERIPHERALS     (RCC_APB2ENR_IOPBEN)

// CE (chip enable) pin (PB11)
#define nRF24_CE_PORT              NRF_CE_GPIO_Port
#define nRF24_CE_PIN               NRF_CE_Pin
#define nRF24_CE_L()               HAL_GPIO_WritePin(nRF24_CE_PORT, nRF24_CE_PIN, GPIO_PIN_RESET)
#define nRF24_CE_H()               HAL_GPIO_WritePin(nRF24_CE_PORT, nRF24_CE_PIN, GPIO_PIN_SET)

// CSN (chip select negative) pin (PB12)
#define nRF24_CSN_PORT             NRF_CSN_GPIO_Port
#define nRF24_CSN_PIN              NRF_CSN_Pin
#define nRF24_CSN_L()              HAL_GPIO_WritePin(nRF24_CSN_PORT, nRF24_CSN_PIN, GPIO_PIN_RESET)
#define nRF24_CSN_H()              HAL_GPIO_WritePin(nRF24_CSN_PORT, nRF24_CSN_PIN, GPIO_PIN_SET)

// IRQ pin (PB10)
#define nRF24_IRQ_PORT             NRF_IRQ_GPIO_Port
#define nRF24_IRQ_PIN              NRF_IRQ_Pin


// Function prototypes
//void nRF24_GPIO_Init(void);
uint8_t nRF24_LL_RW(uint8_t data);

#endif // __NRF24_HAL_H
