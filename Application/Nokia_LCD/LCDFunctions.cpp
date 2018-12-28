/*
 * LCDFunctions.cpp
 *
 *  Created on: 26.12.2018
 *      Author: harald
 */

#include "LCDFunctions.h"
#include "../../Framework/Instances/Common.h"
#include "../../Framework/Tasks/nRF24Task.h"
#include "../../Framework/Tasks/measureTask.h"
#include "../../Framework/libraries/HelpersLib.h"
#include <math.h>


#define TICKS_BCKLT_ON 60000



LCDFunctions::LCDFunctions()
{
	init_PCD8574();

	msmnt = NULL;
	while (msmnt == NULL)
	{
		tx_printf("LCD: Waiting for sensors to initialize... ");
		if (Common::nRF24_basis->get_stationType() == ID_Table::MASTER)
		{
			msmnt       = get_remoteMsmt();
		}
		else
		{
			msmnt       = get_thetaMeasurement();
		}
		osDelay(1000);
	}
	tx_printf("OK.\n");

	if (Common::nRF24_basis->get_stationType() == ID_Table::MASTER)
	{
		sensorCount = ID_TABLE_LEN;
	}
	else
	{
		sensorCount = msmnt->get_sensorCount();
	}

	pages = static_cast<uint8_t>(
			ceil( ((float) sensorCount) / LCD_handle->get_dispLines() ) );
	tmpLineLen = LCD_handle->get_chars_per_line() + 1;
	tmpLine    = static_cast<char*>(malloc(tmpLineLen));
	clrTmpLine();

	act_line   = 0;
	act_page   = 0;
	tickLEDoff = 0;

	button_callback_add((ISR_callback*) this);
}

void LCDFunctions::init_PCD8574(void)
{
	SPI_HandleTypeDef *spi 		= get_LCD_SPI();

	PCD8544_socket::spi_pinspack_type*
	lcd_pinspack = new PCD8544_socket::spi_pinspack_type
	{
		LCD_CE_GPIO_Port,
		LCD_CE_Pin,
		LCD_Reset_GPIO_Port,
		LCD_Reset_Pin,
		LCD_DC_GPIO_Port,
		LCD_DC_Pin,
		LCD_BCKLT_GPIO_Port,
		LCD_BCKLT_Pin
	};

	PCD8544_socket* LCD_socket = new PCD8544_socket(spi, lcd_pinspack);
	//LCD_basis = new PCD8544_basis(LCD_socket);
	LCD_handle  = new PCD8544_graphics(LCD_socket);
	LCD_handle->switch_font(FONT_5x8);
	LCD_handle->clear();
}


void LCDFunctions::update(void)
{
	uint8_t dispLines = LCD_handle->get_dispLines();
	uint8_t start     = act_page * dispLines;
	uint8_t end		  = start + dispLines;
	uint8_t act_line = 0;

	if (HAL_GetTick() > tickLEDoff)
		LCD_handle->backlight_off();

	LCD_handle->clear(); // clear internal buffer

	for (uint8_t i=start; i < end; i++)
	{
		if(i >= sensorCount)
			break;

		clrTmpLine();

		SensorDataType* const data = msmnt->get(i);
		char* tmpShrtnm  = const_cast<char*>(ID_Table::get_shortname( data->sensor_ID ));
		copyString(&tmpLine[0], &tmpShrtnm[0], SHORTNAME_LEN-1);

		pushTheta(data->temperature);

		if( (pages > 1) && (act_line == 0)) // display page-nr
		{
			uint8_t pos = LCD_handle->get_chars_per_line() - 2 ;
			HelpersLib::value2char(&tmpLine[pos], 2, 0, act_page);
		}

		LCD_handle->write_string(
				0, (LCD_handle->line_2_y_pix(act_line)), static_cast<char*>(&tmpLine[0]));

		//tx_printf("lcd: %i, %i, %i, %i\n", start, end, i, LCD_handle->line_2_y_pix(act_line));
		//tx_printf("lcd: %s %i \n", ID_Table::get_shortname( data->sensor_ID ), (int) (data->temperature * 100));

		act_line++;
		displayThetas();
	}
}


void LCDFunctions::pushTheta(float theta)
{
	int32_t	tmpTheta = (theta + 0.05) * 10;

	if (tmpTheta < (INVLD_TEMPERATURE * 10))
	{
		HelpersLib::value2char(&tmpLine[SHORTNAME_LEN], 5, 1, tmpTheta);
		if (tmpTheta >= 0)
			tmpLine[SHORTNAME_LEN] = ' ';
	}
	else
	{
		char txt[] = " --.-";
		copyString(&tmpLine[SHORTNAME_LEN], &txt[0], 5);
	}

}

void LCDFunctions::displayThetas(void)
{
	LCD_handle->display(); // push internal buffer to LCD
	act_line   = 0;
}

void LCDFunctions::incPage(void)
{
	act_page++;
	if(act_page >= pages)
	{
		act_page = 0;
	}
}

void LCDFunctions::clrTmpLine(void)
{
	for (uint8_t i=0; i < tmpLineLen-1; i++)
	{
		tmpLine[i] = ' ';
	}
	tmpLine[tmpLineLen-1] = '\0';
}

void LCDFunctions::copyString(char* tgt, char* src, uint8_t len)
{
	for (uint8_t i=0; i < len; i++)
	{
		tgt[i] = src[i];
	}
}

PCD8544_graphics* LCDFunctions::get_LCD_handle(void)
{
	return LCD_handle;
}

void LCDFunctions::ISR_callback_fcn (void)
{
	tickLEDoff = HAL_GetTick() + TICKS_BCKLT_ON;
	LCD_handle->backlight_on();
}



