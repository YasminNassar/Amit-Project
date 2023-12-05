/*
 * GLCD_Interface.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Yasmin
 */

#ifndef GLCD_INTERFACE_H_
#define GLCD_INTERFACE_H_

//GLCD Initialization
void GLCD_VidInit(void);
//Clear Screen
void GLCD_VidClear(void);
//Send Command
void GLCD_VidSendCommand(u8 Copy_u8Command);
//Send Data
void GLCD_VidSendData(u8 Copy_u8Data);
//Set Position in GLCD
void GLCD_VidSetPosition(u8 Copy_u8Page, u8 Copy_u8Column);
//Send String
void GLCD_VidSendString(u8 *Copy_u8String);
//Send Number to GLCD
void GLCD_VidSendingNumber(u8 Copy_u8Number);
//Convert Number to Character
void GLCD_VidSendNumber(f32 Copy_u32Number);
//Draw PWM Waveform
void GLCD_VidDrawPWM(u8 Copy_u8Page, f32 Frequency, f32 DutyCycle);

#endif /* GLCD_INTERFACE_H_ */
