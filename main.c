/*
 * main.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Yasmin
 */

#define F_CPU   2000000UL
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "GLCD_Interface.h"
#include "GLCD_Config.h"
#include "TIMER_Interface.h"
#include "GIE_Interface.h"
#include <math.h>
#include <util/delay.h>

u8 count = 0;
u8 flag = 0;
u32 T1;
u32 T2;
u32 T3;

int main(void)
{
	u8 Frequency_ARR[] ="Frequency = ";
	u8 KHZ[] ="KHZ";
	u8 DutyCycle_ARR[] = "Duty Cycle = ";
	u8 Percent[] ="%";
	u8 TimePerid_ARR[] = "Time Period = ";
	u8 ms[] ="ms";
	u8 Welcome[] = "Welcome...";

	/*Set OC2 as Output*/
	DIO_VidSetPinDirection(DIO_PORTD,7,PIN_OUTPUT);
	/*Set ICP1 as Input*/
	DIO_VidSetPinDirection(DIO_PORTD,6,PIN_INPUT);

	/*Set Data Pins Direction*/
	DIO_VidSetPortDirection(GLCD_DATA_PORT,PORT_OUTPUT);
	/*Set Control Pins Direction*/
	DIO_VidSetPortDirection(GLCD_CONTROL_PORT,PORT_OUTPUT);
	/*DIO_VidSetPinDirection(GLCD_CONTROL_PORT,PIN0,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,PIN1,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,PIN2,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,PIN3,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,PIN4,PIN_OUTPUT);
	DIO_VidSetPinDirection(GLCD_CONTROL_PORT,PIN5,PIN_OUTPUT);*/

	//GLCD Initialization
	GLCD_VidInit();
	//Clear GLCD
	GLCD_VidClear();

	/*ICU Select Raising Edge & Enable Interrupt*/
	TIMER1_VidICUEnable(TIMER1_ICU_RAISING_EDGE);

	/*Timer1 Initialization - Prescaler 8*/
	TIMER1_VidInit();

	/*Timer2 CTC Value*/
	TIMER2_VidSetCTCValue(100);
	/*Timer2 Initialization - Prescaler 256*/
	TIMER2_VidInit();

	/*GLobal Interrupt Enable*/
	GIE_VidEnable();

	f32 Frequency;
	f32 DutyCycle;
	f32 TimePeriod;

	//Select Position
	GLCD_VidSetPosition(0,0);
	GLCD_VidSendString(Welcome);
	_delay_ms(1000);
	//Clear GLCD
	GLCD_VidClear();

	while(1)
	{
		if(flag == 3)
		{
			Frequency = (1000/(((T3*8.0)/2)-((T1*8.0)/2))); //Calculate Frequency in KHz
			DutyCycle = (((T2-T1)*100.0)/(T3-T1));          //Calculate Duty Cycle
			TimePeriod = (1/Frequency);
			GLCD_VidSetPosition(0,0);                       //Select Page 0 Column 0
			GLCD_VidSendString(Frequency_ARR);
			GLCD_VidSendNumber(Frequency);                  //Display Frequency
			GLCD_VidSendString(KHZ);
			GLCD_VidSetPosition(2,0);                       //Select Page 1 Column 0//Select Position
			GLCD_VidSendString(DutyCycle_ARR);
			GLCD_VidSendNumber(DutyCycle);                  //Display Duty Cycle
			GLCD_VidSendString(Percent);
			GLCD_VidSetPosition(4,0);                       //Select Page 2 Column 0
			GLCD_VidSendString(TimePerid_ARR);
			GLCD_VidSendNumber(TimePeriod);                 //Display Tp in ms
			GLCD_VidSendString(ms);

			/*GLCD_VidSetPosition(5,0);
			GLCD_VidSendNumber(T1);
			GLCD_VidSetPosition(6,0);
			GLCD_VidSendNumber(T2);
			GLCD_VidSetPosition(7,0);
			GLCD_VidSendNumber(T3);*/

			//GLCD_VidSetPosition(0,0);
			//GLCD_VidSendString("Hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
			//GLCD_VidSendString("LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");

			//GLCD_VidSendNumber(4294967295);

			//GLCD_VidSetPosition(2,123);
			//GLCD_VidSendNumber(0);
			//GLCD_VidSetPosition(2,93);
			//GLCD_VidSendString("H");

			//Draw PWM
			GLCD_VidDrawPWM(6,Frequency,DutyCycle);

			flag = 4;
		}
	}
	return 0;
}

//ISR For Timer1 OverFlow
void __vector_9(void)       __attribute__((signal));
void __vector_9(void)
{
	count++;   //Increment Counter When OverFlow Occurs
}

//ISR For Timer1 ICU
void __vector_6(void)       __attribute__((signal));
void __vector_6(void)
{
	if(flag == 0)
	{
		T1 = ICR1 + (count*65536);                      //Store Counts For The Raising Edge
		TIMER1_VidICUEnable(TIMER1_ICU_FALLING_EDGE);   //Wait For Falling Edge
		flag = 1;
	}
	else if(flag == 1)
	{
		T2 = ICR1 + (count*65536);                      //Store Counts For The Falling Edge
		TIMER1_VidICUEnable(TIMER1_ICU_RAISING_EDGE);   //Wait For Raising Edge
		flag = 2;
	}
	else if(flag == 2)
	{
		T3 = ICR1 + (count*65536);   //Store Counts For The Raising Edge
		flag = 3;
	}
}
