/*
 * LCDFunctions.h
 *
 *  Created on: 26.12.2018
 *      Author: harald
 */

#ifndef NOKIA_LCD_LCDFUNCTIONS_H_
#define NOKIA_LCD_LCDFUNCTIONS_H_


#include "../Framework/Devices/PCD8544_LCD/PCD8544_graphics.h"
#include "../Application/ThetaSensors/ThetaMeasurement.h"
#include "../Framework/Instances/callbacks.h"


class LCDFunctions:
		ISR_callback
{

public:
	LCDFunctions();
	virtual ~LCDFunctions() { };

	PCD8544_graphics*  get_LCD_handle(void);
	void copyString(char* src, char* tgt, uint8_t len);
	void displayThetas(void);
	void update(void);
	void clrTmpLine(void);
	void incPage(void);
	void ISR_callback_fcn (void);

private:
	void init_PCD8574(void);
	void pushTheta(float theta);

	ThetaMeasurement* 	msmnt;
	PCD8544_graphics*	LCD_handle;

	uint32_t tickLEDoff;
	uint8_t  pages;
	char* 	 tmpLine;
	uint8_t	 tmpLineLen;
	uint8_t  act_line;
	uint8_t  act_page;
	uint8_t  sensorCount;

};

#endif /* NOKIA_LCD_LCDFUNCTIONS_H_ */
