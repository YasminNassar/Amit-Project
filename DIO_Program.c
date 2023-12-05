/*
 * DIO_Program.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Yasmin
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"

/*Set Pin Direction*/
void DIO_VidSetPinDirection(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinDirection)
{
	switch(Copy_u8PortName)
	{
	case DIO_PORTA:
		if(Copy_u8PinDirection == PIN_OUTPUT)
		{
			SET_BIT(DDRA,Copy_u8PinNumber);
		}
		else if(Copy_u8PinDirection == PIN_INPUT)
		{
			CLR_BIT(DDRA,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTB:
		if(Copy_u8PinDirection == PIN_OUTPUT)
		{
			SET_BIT(DDRB,Copy_u8PinNumber);
		}
		else if(Copy_u8PinDirection == PIN_INPUT)
		{
			CLR_BIT(DDRB,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTC:
		if(Copy_u8PinDirection == PIN_OUTPUT)
		{
			SET_BIT(DDRC,Copy_u8PinNumber);
		}
		else if(Copy_u8PinDirection == PIN_INPUT)
		{
			CLR_BIT(DDRC,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTD:
		if(Copy_u8PinDirection == PIN_OUTPUT)
		{
			SET_BIT(DDRD,Copy_u8PinNumber);
		}
		else if(Copy_u8PinDirection == PIN_INPUT)
		{
			CLR_BIT(DDRD,Copy_u8PinNumber);
		}
		break;
	}

}
/*Set Pin Value*/
void DIO_VidSetPinValue(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinValue)
{
	switch(Copy_u8PortName)
	{
	case DIO_PORTA:
		if(Copy_u8PinValue == PIN_HIGH)
		{
			SET_BIT(PORTA,Copy_u8PinNumber);
		}
		else if(Copy_u8PinValue == PIN_LOW)
		{
			CLR_BIT(PORTA,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTB:
		if(Copy_u8PinValue == PIN_HIGH)
		{
			SET_BIT(PORTB,Copy_u8PinNumber);
		}
		else if(Copy_u8PinValue == PIN_LOW)
		{
			CLR_BIT(PORTB,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTC:
		if(Copy_u8PinValue == PIN_HIGH)
		{
			SET_BIT(PORTC,Copy_u8PinNumber);
		}
		else if(Copy_u8PinValue == PIN_LOW)
		{
			CLR_BIT(PORTC,Copy_u8PinNumber);
		}
		break;
	case DIO_PORTD:
		if(Copy_u8PinValue == PIN_HIGH)
		{
			SET_BIT(PORTD,Copy_u8PinNumber);
		}
		else if(Copy_u8PinValue == PIN_LOW)
		{
			CLR_BIT(PORTD,Copy_u8PinNumber);
		}
		break;
	}
}
/*Get Pin Value*/
u8 DIO_u8GetPinValue(u8 Copy_u8PortName, u8 Copy_u8PinNumber)
{
	u8 LOC_u8PinState = 0;
	switch(Copy_u8PortName)
	{
	case DIO_PORTA:
		LOC_u8PinState = GET_BIT(PINA, Copy_u8PinNumber);
		break;
	case DIO_PORTB:
		LOC_u8PinState = GET_BIT(PINB, Copy_u8PinNumber);
		break;
	case DIO_PORTC:
		LOC_u8PinState = GET_BIT(PINC, Copy_u8PinNumber);
		break;
	case DIO_PORTD:
		LOC_u8PinState = GET_BIT(PIND, Copy_u8PinNumber);
		break;
	}
	return LOC_u8PinState;
}
/*Set Port Direction*/
void DIO_VidSetPortDirection(u8 Copy_u8PortName,u8 Copy_u8PortDirection)
{
	switch(Copy_u8PortName)
	{
	case DIO_PORTA:
		DDRA = Copy_u8PortDirection;
		break;
	case DIO_PORTB:
		DDRB = Copy_u8PortDirection;
		break;
	case DIO_PORTC:
		DDRC = Copy_u8PortDirection;
		break;
	case DIO_PORTD:
		DDRD = Copy_u8PortDirection;
		break;
	}
}
/*Set Port Value*/
void DIO_VidSetPortValue(u8 Copy_u8PortName,u8 Copy_u8PortValue)
{
	switch(Copy_u8PortName)
	{
	case DIO_PORTA:
		PORTA = Copy_u8PortValue;
		break;
	case DIO_PORTB:
		PORTB = Copy_u8PortValue;
		break;
	case DIO_PORTC:
		PORTC = Copy_u8PortValue;
		break;
	case DIO_PORTD:
		PORTD = Copy_u8PortValue;
		break;
	}
}
/*Set 4MSB Direction*/
void DIO_VidSet4MSBDirection(u8 Copy_u8PortName,u8 Copy_u8PinsDirection)
{
	switch(Copy_u8PortName)
	{
	case DIO_PORTA:
		DDRA&=0x0F;
		DDRA|=(Copy_u8PinsDirection<<4);
		break;
	case DIO_PORTB:
		DDRB&=0x0F;
		DDRB|=(Copy_u8PinsDirection<<4);
		break;
	case DIO_PORTC:
		DDRC&=0x0F;
		DDRC|=(Copy_u8PinsDirection<<4);
		break;
	case DIO_PORTD:
		DDRD&=0x0F;
		DDRD|=(Copy_u8PinsDirection<<4);
		break;
	}
}
/*Set 4LSB Direction*/
void DIO_VidSet4LSBDirection(u8 Copy_u8PortName,u8 Copy_u8PinsDirection)
{
	switch(Copy_u8PortName)
	{
	case DIO_PORTA:
		DDRA&=0xF0;
		DDRA|=Copy_u8PinsDirection;
		break;
	case DIO_PORTB:
		DDRB&=0xF0;
		DDRB|=Copy_u8PinsDirection;
		break;
	case DIO_PORTC:
		DDRC&=0xF0;
		DDRC|=Copy_u8PinsDirection;
		break;
	case DIO_PORTD:
		DDRD&=0xF0;
		DDRD|=Copy_u8PinsDirection;
		break;
	}
}
/*Set 4MSB Value*/
void DIO_VidSet4MSBValue(u8 Copy_u8PortName,u8 Copy_u8PinsValue)
{
	switch(Copy_u8PortName)
	{
	case DIO_PORTA:
		PORTA&=0x0F;
		PORTA|=(Copy_u8PinsValue<<4);
		break;
	case DIO_PORTB:
		PORTB&=0x0F;
		PORTB|=(Copy_u8PinsValue<<4);
		break;
	case DIO_PORTC:
		PORTC&=0x0F;
		PORTC|=(Copy_u8PinsValue<<4);
		break;
	case DIO_PORTD:
		PORTD&=0x0F;
		PORTD|=(Copy_u8PinsValue<<4);
		break;
	}
}
/*Set 4LSB Value*/
void DIO_VidSetLSBValue(u8 Copy_u8PortName,u8 Copy_u8PinsValue)
{
	switch(Copy_u8PortName)
	{
	case DIO_PORTA:
		PORTA&=0xF0;
		PORTA|=Copy_u8PinsValue;
		break;
	case DIO_PORTB:
		PORTB&=0xF0;
		PORTB|=Copy_u8PinsValue;
		break;
	case DIO_PORTC:
		PORTC&=0xF0;
		PORTC|=Copy_u8PinsValue;
		break;
	case DIO_PORTD:
		PORTD&=0xF0;
		PORTD|=Copy_u8PinsValue;
		break;
	}
}
