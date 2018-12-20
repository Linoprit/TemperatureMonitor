#include "nrf24_hal.h"


// Configure the GPIO lines of the nRF24L01 transceiver
// note: IRQ pin must be configured separately
/*void nRF24_GPIO_Init(void) {
    GPIO_InitTypeDef PORT;

    // Enable the nRF24L01 GPIO peripherals
	RCC->APB2ENR |= nRF24_GPIO_PERIPHERALS;

    // Configure CSN pin
	PORT.GPIO_Mode = GPIO_Mode_Out_PP;
	PORT.GPIO_Speed = GPIO_Speed_2MHz;
	PORT.GPIO_Pin = nRF24_CSN_PIN;
	GPIO_Init(nRF24_CSN_PORT, &PORT);
	nRF24_CSN_H();

	// Configure CE pin
	PORT.GPIO_Pin = nRF24_CE_PIN;
	GPIO_Init(nRF24_CE_PORT, &PORT);
	nRF24_CE_L();
}*/

// Low level SPI transmit/receive function (hardware depended)
// input:
//   data - value to transmit via SPI
// return: value received from SPI

uint8_t rx_buffer; // where received byte is put in

uint8_t nRF24_LL_RW(uint8_t data) {

	  while(HAL_SPI_GetState(get_nRF24_SPI()) != HAL_SPI_STATE_READY)
	    {
	    }

	  //HAL_SPI_Transmit(get_nRF24_SPI(), &data, 1, 500);
	  //HAL_SPI_Receive(get_nRF24_SPI(), &rx_buffer, 1, 500);
	  HAL_SPI_TransmitReceive(get_nRF24_SPI(), &data, &rx_buffer, 1, 500);

	 // Wait until TX buffer is empty
	/*while (SPI_I2S_GetFlagStatus(nRF24_SPI_PORT, SPI_I2S_FLAG_TXE) == RESET);
	// Send byte to SPI (TXE cleared)
	SPI_I2S_SendData(nRF24_SPI_PORT, data);
	// Wait while receive buffer is empty
	while (SPI_I2S_GetFlagStatus(nRF24_SPI_PORT, SPI_I2S_FLAG_RXNE) == RESET);*/

	// Return received byte
	return rx_buffer; //(uint8_t)SPI_I2S_ReceiveData(nRF24_SPI_PORT);
}
