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

#ifndef _LED_DRIVER_TLC5926_H_
#define _LED_DRIVER_TLC5926_H_

#include "../AVR_GPIO/AVR_GPIO.h"
#include <util/delay.h>

//END USER DEFINABLE LIBRARY PARAMETERS/////////////////
#define LED_DRIVER_TLC5926_GPIO_SDI		C, PC2
#define LED_DRIVER_TLC5926_GPIO_CLK		C, PC1
#define LED_DRIVER_TLC5926_GPIO_LE		C, PC0
#define LED_DRIVER_TLC5926_GPIO_OE		C, PC0

#define LED_DRIVER_TLC5926_NUM				(2)
#define LED_DRIVER_TLC5926_CLK_DELAY_MS		(10)
#define LED_DRIVER_TLC5926_HAS_OE_CONTROL	(0)

void LED_DRIVER_TLC5926_Init(void);
void LED_DRIVER_TLC5926_Turn_On(void);
void LED_DRIVER_TLC5926_Turn_Off(void);
void LED_DRIVER_TLC5926_Send_Value(uint16_t* val);


#endif
