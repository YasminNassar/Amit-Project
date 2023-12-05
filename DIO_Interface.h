/*
 * DIO_Interface.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Yasmin
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_PORTA  0
#define DIO_PORTB  1
#define DIO_PORTC  2
#define DIO_PORTD  3

#define PIN_OUTPUT 1
#define PIN_INPUT  0

#define PIN_HIGH   1
#define PIN_LOW    0

#define PORT_OUTPUT 255
#define PORT_INPUT  0

#define PORT_HIGH 255
#define PORT_LOW   0

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,

}Pin_t;

/*Set Pin Direction*/
void DIO_VidSetPinDirection(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinDirection);
/*Set Pin Value*/
void DIO_VidSetPinValue(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinValue);
/*Get Pin Value*/
u8 DIO_u8GetPinValue(u8 Copy_u8PortName, u8 Copy_u8PinNumber);
/*Set Port Direction*/
void DIO_VidSetPortDirection(u8 Copy_u8PortName,u8 Copy_u8PortDirection);
/*Set Port Value*/
void DIO_VidSetPortValue(u8 Copy_u8PortName,u8 Copy_u8PortValue);
/*Set 4MSB Direction*/
void DIO_VidSet4MSBDirection(u8 Copy_u8PortName,u8 Copy_u8PinsDirection);
/*Set 4LSB Direction*/
void DIO_VidSet4LSBDirection(u8 Copy_u8PortName,u8 Copy_u8PinsDirection);
/*Set 4MSB Value*/
void DIO_VidSet4MSBValue(u8 Copy_u8PortName,u8 Copy_u8PinsValue);
/*Set 4LSB Value*/
void DIO_VidSetLSBValue(u8 Copy_u8PortName,u8 Copy_u8PinsValue);


#endif /* DIO_INTERFACE_H_ */
