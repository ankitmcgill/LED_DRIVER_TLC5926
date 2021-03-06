//////////////////////////////////////////////////////////////////
// LED DRIVER - TLC5926
//
// LIBRARY FOR 16 CHANNEL CONSTANT CURRENT SINK TLC5926 FROM
// TEXAS INSTRUMENTS
//
// NOTE : DEPENDS ON AVR_GPIO LIBRARY
//
// JANUARY 6, 2017
//
// ANKIT BHATNAGAR
// ANKIT.BHATNAGARINDIA@GMAIL.COM
//////////////////////////////////////////////////////////////////

#include "LED_DRIVER_TLC5926.h"

void LED_DRIVER_TLC5926_Init(void)
{
	//INITIALIZE TLC5926 AND TURN OFF THE 
	//DISPLAY
	//ALL PINS WILL BE BY DEFAULT LOW EXCEPT /OE WHICH WOULD
	//NEED TO BE SET TO HIGH (IF CONTROLLED BY THE LIBRARY)
	
	AVR_GPIO_PIN_SET_DIRECTION_OUT(LED_DRIVER_TLC5926_GPIO_SDI);
	AVR_GPIO_PIN_SET_DIRECTION_OUT(LED_DRIVER_TLC5926_GPIO_SDI);
	AVR_GPIO_PIN_SET_DIRECTION_OUT(LED_DRIVER_TLC5926_GPIO_LE);
	if(LED_DRIVER_TLC5926_HAS_OE_CONTROL)
	{
		//LIBRARY CONTROLS THE /OE LINE
		AVR_GPIO_PIN_SET_DIRECTION_OUT(LED_DRIVER_TLC5926_GPIO_OE);
		AVR_GPIO_PIN_HIGH(LED_DRIVER_TLC5926_GPIO_OE);
	}
}
void LED_DRIVER_TLC5926_Turn_On(void)
{
	//TURN ON DISPLAY (OE) OF TLC5926
	
	if(LED_DRIVER_TLC5926_HAS_OE_CONTROL)
	{
		//LIBRARY CONTROLS THE /OE LINE
		AVR_GPIO_PIN_LOW(LED_DRIVER_TLC5926_GPIO_OE);
	}
}

void LED_DRIVER_TLC5926_Turn_Off(void)
{
	//TURN OFF DISPLAY (OE) OF TLC5926
	
	if(LED_DRIVER_TLC5926_HAS_OE_CONTROL)
	{
		//LIBRARY CONTROLS THE /OE LINE
		AVR_GPIO_PIN_HIGH(LED_DRIVER_TLC5926_GPIO_OE);
	}
}

void LED_DRIVER_TLC5926_Send_Value(uint16_t* val)
{
	//SEND 16 BIT VALUE TO TLC5926 AND LATCH IT
	//TO IT'S OUTPUT
	//ARGUMENT IS ARRAY BECAUSE MULTIPLE TLC5926
	//CAN BE DAISY CHAINED BASED ON THE USER DEFINE
	//'LED_DRIVER_TLC5926_NUM'
	//DATA SHIFTED OUT MSB FIRST
	
	int8_t j = 0;
	uint8_t i = LED_DRIVER_TLC5926_NUM;
	
	while(i != 0)
	{
		AVR_GPIO_PIN_LOW(LED_DRIVER_TLC5926_GPIO_CLK);
		for(j = 15; j >= 0; j--)
		{
			if(val[i - 1] & (1 << j))
			{
				AVR_GPIO_PIN_HIGH(LED_DRIVER_TLC5926_GPIO_SDI);
			}
			else
			{
				AVR_GPIO_PIN_LOW(LED_DRIVER_TLC5926_GPIO_SDI);
			}
			AVR_GPIO_PIN_HIGH(LED_DRIVER_TLC5926_GPIO_CLK);
			_delay_ms(LED_DRIVER_TLC5926_CLK_DELAY_MS);
			AVR_GPIO_PIN_LOW(LED_DRIVER_TLC5926_GPIO_CLK);
			_delay_ms(LED_DRIVER_TLC5926_CLK_DELAY_MS);
		}
		i--;
	}

	//LATCH THE NEW VALUES
	AVR_GPIO_PIN_HIGH(LED_DRIVER_TLC5926_GPIO_LE);
	_delay_ms(LED_DRIVER_TLC5926_CLK_DELAY_MS);
	AVR_GPIO_PIN_LOW(LED_DRIVER_TLC5926_GPIO_LE);
}
