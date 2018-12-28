/*
 * callbacks.c
 *
 *  Created on: 16.05.2016
 *      Author: harald
 */


#include "callbacks.h"
#include "stm32f1xx_hal.h"
#include "Common.h"

#include "../Framework/libraries/Arduino/WString.h"
#include "../Framework/libraries/HelpersLib.h"



ISR_callback *uart1_RxCplt_callback   = NULL;
ISR_callback *uart2_RxCplt_callback   = NULL;
ISR_callback *uart3_RxCplt_callback   = NULL;
ISR_callback *gpio_nRF24_callback	  = NULL;
ISR_callback *button_callback  	      = NULL;



/*void HAL_SYSTICK_Callback(void) {}*/

void nRF24_callback_add(ISR_callback* callback)
{
	gpio_nRF24_callback = callback;
}

void button_callback_add(ISR_callback* callback)
{
	button_callback = callback;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//UNUSED(GPIO_Pin);

	if ((gpio_nRF24_callback != NULL) && (GPIO_Pin == Common::nRF24_gpio->get_IRQ_Pin() ))
	{
		gpio_nRF24_callback->ISR_callback_fcn();
	}
	else if ((button_callback != NULL) && (GPIO_Pin == BUTTON_1_Pin))
	{
		button_callback->ISR_callback_fcn();
	}
}

void uart_callback_add(UART_HandleTypeDef *huart, ISR_callback* callback)
{
  if (huart->Instance == USART1)
	{
	  uart1_RxCplt_callback = callback;
	}

  else if (huart->Instance == USART2)
	{
	  uart2_RxCplt_callback = callback;
	}

  else if (huart->Instance == USART3)
	{
	  uart3_RxCplt_callback = callback;
	}
}

void call_uart_callbacks(UART_HandleTypeDef *huart)
{
  // TODO three times the same... better idea?
  if (huart->Instance == USART1)
	{
	  if (uart1_RxCplt_callback == NULL)
		return;

	  uart1_RxCplt_callback->ISR_callback_fcn();
	}

  else if (huart->Instance == USART2)
	{
	  if (uart2_RxCplt_callback == NULL)
		return;

	  uart2_RxCplt_callback->ISR_callback_fcn();
	}

  else if (huart->Instance == USART3)
	{
	  if (uart3_RxCplt_callback == NULL)
		return;

	  uart3_RxCplt_callback->ISR_callback_fcn();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  // TODO do we need some overflow handler?
  call_uart_callbacks(huart);
}

void HAL_UART_RxIdleCallback(UART_HandleTypeDef *huart)
{
  call_uart_callbacks(huart);
}









