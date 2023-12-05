/*
 * TIMER_Interface.h
 *
 *  Created on: Nov 18, 2023
 *      Author: Yasmin
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define TIMER1_ICU_RAISING_EDGE   0
#define TIMER1_ICU_FALLING_EDGE   1

#define ICR1     *((volatile u16*)0x46)
#define OCR1A    *((volatile u16*)0x4A)

//Timer0 Initialization
void TIMER0_VidInit(void);
//Timer0 Set Preload
void TIMER0_VidSetPreload(u8 Copy_u8Preload);
//Timer0 Set CTC Value
void TIMER0_VidSetCTCValue(u8 Copy_u8CTCValue);

//Timer1 Initialization
void TIMER1_VidInit(void);
//Timer1 Set Preload
void TIMER1_VidSetPreload(u16 Copy_u16Preload);
//Timer1 Set CTC Value
void TIMER1_VidSetCTCValue(u16 Copy_u16CTCValue);
//Timer1 Set Top Value
void TIMER1_VidSetTopValue(u16 Copy_u16TopValue);
//Timer1 Select Sense Edge & Enable ICU Interrupt
void TIMER1_VidICUEnable(u8 Copy_u8Edge);

//Timer2 Initialization
void TIMER2_VidInit(void);
//Timer2 Set Preload
void TIMER2_VidSetPreload(u8 Copy_u8Preload);
//Timer2 Set CTC Value
void TIMER2_VidSetCTCValue(u8 Copy_u8CTCValue);

#endif /* TIMER_INTERFACE_H_ */
