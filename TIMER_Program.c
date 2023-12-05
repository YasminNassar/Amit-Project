/*
 * TIMER_Program.c
 *
 *  Created on: Nov 18, 2023
 *      Author: Yasmin
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_Private.h"
#include "TIMER_Interface.h"
#include "TIMER_Config.h"

//Timer0 Initialization
void TIMER0_VidInit(void)
{
	/*Set Prescaler*/
	TCCR0&=0xF8;
	TCCR0|=TIMER0_SET_PRESCALER;
	/*Set Mode*/
#if TIMER0_SET_MODE == TIMER0_NORMAL_MODE   //Select Normal Mode
	CLR_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	/*Enable Overflow Interrupt*/
	SET_BIT(TIMSK,0);
#elif TIMER0_SET_MODE == TIMER0_CTC_MODE   //Select CTC Mode
	CLR_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	//OC0 Pin Option
#if TIMER0_OC0_MODE == TIMER0_OC0_DISCONNECTED  //OC0 Disconnected
	CLR_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif TIMER0_OC0_MODE == TIMER0_OC0_TOGGLE   //Toggle OC0
	SET_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif TIMER0_OC0_MODE == TIMER0_OC0_CLEAR   //Clear OC0
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif TIMER0_OC0_MODE == TIMER0_OC0_SET   //Set OC0
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#else
#error "Timer0 OC0 Pin Option is not Valid"
#endif
	/*Enable CTC Interrupt*/
	SET_BIT(TIMSK,1);
#elif TIMER0_SET_MODE == TIMER0_FAST_PWM_MODE   //Select Fast PWM Mode
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,3);
	//OC0 Pin Option
#if TIMER0_FAST_PWM_OC0_MODE == TIMER0_OC0_NON_INVERTING   //OC0 in Non Inverting Mode
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif TIMER0_FAST_PWM_OC0_MODE == TIMER0_OC0_INVERTING   //OC0 in Inverting Mode
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#else
#error "Timer0 OC0 Pin Option is not Valid"
#endif
#elif TIMER0_SET_MODE == TIMER0_PHASE_CORRECT_PWM_MODE   //Select Phase Correct Mode
	SET_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	//OC0 Pin Option
#if TIMER0_PHASE_CORRECT_PWM_OC0_MODE  == TIMER0_OC0_NON_INVERTING   //OC0 in Non Inverting Mode
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#elif TIMER0_PHASE_CORRECT_PWM_OC0_MODE  == TIMER0_OC0_INVERTING   //OC0 in Inverting Mode
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#else
#error "Timer0 OC0 Pin Option is not Valid"
#endif
#else
#error "Timer0 Mode Option is not Valid"
#endif
}
//Timer0 Set Preload
void TIMER0_VidSetPreload(u8 Copy_u8Preload)
{
	TCNT0 = Copy_u8Preload;
}
//Timer0 Set CTC Value
void TIMER0_VidSetCTCValue(u8 Copy_u8CTCValue)
{
	OCR0 = Copy_u8CTCValue;
}

//Timer1 Initialization
void TIMER1_VidInit(void)
{
	/*Set Prescaler*/
	TCCR1B&=0xF8;
	TCCR1B|=TIMER1_SET_PRESCALER;
	/*Set Mode*/
#if TIMER1_SET_MODE == TIMER1_NORMAL_MODE   //Select Normal Mode
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	/*Enable Overflow Interrupt*/
	SET_BIT(TIMSK,2);
#elif TIMER1_SET_MODE == TIMER1_PHASE_CORRECT_PWM_8_BIT_MODE   //Select Phase Correct PWM 8 Bit Mode
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_INVERTING    //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_PHASE_CORRECT_PWM_9_BIT_MODE   //Select Phase Correct PWM 9 Bit Mode
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_DISCONNECTED    //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_NON_INVERTING    //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_INVERTING    //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_PHASE_CORRECT_PWM_10_BIT_MODE   //Select Phase Correct PWM 10 Bit Mode
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_NON_INVERTING    //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_INVERTING    //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_CTC_MODE   //Select CTC Mode
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_CTC_OC1A_AND_OC1B_MODE == TIMER1_CTC_OC1A_AND_OC1B_DISCONNECRED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
	/*Enable CTC Interrupt for Channel A*/
	SET_BIT(TIMSK,4);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
	/*Enable CTC Interrupt for Channel B*/
	SET_BIT(TIMSK,3);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_CTC_OC1A_AND_OC1B_MODE == TIMER1_CTC_OC1A_AND_OC1B_TOGGLE   ///Toggle OC1A & OC1B
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
	/*Enable CTC Interrupt for Channel A*/
	SET_BIT(TIMSK,4);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
	/*Enable CTC Interrupt for Channel B*/
	SET_BIT(TIMSK,3);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_CTC_OC1A_AND_OC1B_MODE == TIMER1_CTC_OC1A_AND_OC1B_CLEAR   //Clear OC1A & OC1B
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
	/*Enable CTC Interrupt for Channel A*/
	SET_BIT(TIMSK,4);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	/*Enable CTC Interrupt for Channel B*/
	SET_BIT(TIMSK,3);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_CTC_OC1A_AND_OC1B_MODE == TIMER1_CTC_OC1A_AND_OC1B_SET   //Set OC1A & OC1B
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
	/*Enable CTC Interrupt for Channel A*/
	SET_BIT(TIMSK,4);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	/*Enable CTC Interrupt for Channel B*/
	SET_BIT(TIMSK,3);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_FAST_PWM_8_BIT_MODE   //Select Fast PWM 8 Bit Mode
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_INVERTING   //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_FAST_PWM_9_BIT_MODE   //Select Fast PWM 9 Bit Mode
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_INVERTING   //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_FAST_PWM_10_BIT_MODE   //Select Fast PWM 10 Bit Mode
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_INVERTING   //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_PHASE_AND_FREQUENCY_CORRECT_ICR1_AS_TOP_MODE   //Select Phase & Frequency Correct Mode ICR1 as Top
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_INVERTING   //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_PHASE_AND_FREQUENCY_CORRECT_OCR1A_AS_TOP_MODE   //Select Phase & Frequency Correct Mode OCR1A as Top
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_INVERTING   //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_PHASE_CORRECT_ICR1_AS_TOP_MODE   //Select Phase & Frequency Correct Mode ICR1 as Top
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_INVERTING   //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_PHASE_CORRECT_OCR1A_AS_TOP_MODE   //Select Phase & Frequency Correct Mode OCR1A as Top
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_MODE == TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_INVERTING   //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_CTC_ICR1_AS_TOP_MODE   //Select CTC Mode ICR1 as Top
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_CTC_OC1A_AND_OC1B_MODE == TIMER1_CTC_OC1A_AND_OC1B_DISCONNECRED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
	/*Enable CTC Interrupt for Channel A*/
	SET_BIT(TIMSK,4);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
	/*Enable CTC Interrupt for Channel B*/
	SET_BIT(TIMSK,3);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_CTC_OC1A_AND_OC1B_MODE == TIMER1_CTC_OC1A_AND_OC1B_TOGGLE   //Toggle OC1A & OC1B
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
	/*Enable CTC Interrupt for Channel A*/
	SET_BIT(TIMSK,4);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
	/*Enable CTC Interrupt for Channel B*/
	SET_BIT(TIMSK,3);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_CTC_OC1A_AND_OC1B_MODE == TIMER1_CTC_OC1A_AND_OC1B_CLEAR   //Clear OC1A & OC1B
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
	/*Enable CTC Interrupt for Channel A*/
	SET_BIT(TIMSK,4);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	/*Enable CTC Interrupt for Channel B*/
	SET_BIT(TIMSK,3);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_CTC_OC1A_AND_OC1B_MODE == TIMER1_CTC_OC1A_AND_OC1B_SET   //Set OC1A & OC1B
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
	/*Enable CTC Interrupt for Channel A*/
	SET_BIT(TIMSK,4);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	/*Enable CTC Interrupt for Channel B*/
	SET_BIT(TIMSK,3);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_FAST_PWM_ICR1_AS_TOP_MODE   //Select Fast PWM Mode ICR1 as Top
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_INVERTING   //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#elif TIMER1_SET_MODE == TIMER1_FAST_PWM_OCR1A_AS_TOP_MODE   //Select Fast PWM Mode OCR1A as Top
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	//OC1A & OC1B Pins Options
#if TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_DISCONNECTED   //OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED   //Toggle OC1A & OC1B Disconnected
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_NON_INVERTING   //OC1A & OC1B in Non Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#elif TIMER1_FAST_PWM_OC1A_AND_OC1B_MODE == TIMER1_FAST_PWM_OC1A_AND_OC1B_INVERTING   //OC1A & OC1B in Inverting Mode
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A   //Select Channel A
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B   //Select Channel B
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
#else
#error "Timer1 Channel Option is not Valid"
#endif
#else
#error "Timer1 OC1A/OC1B Pins Option is not Valid"
#endif
#else
#error "Timer1 Mode Option is not Valid"
#endif


}
//Timer1 Set Preload
void TIMER1_VidSetPreload(u16 Copy_u16Preload)
{
	TCNT1  = Copy_u16Preload;
}
//Timer1 Set CTC Value
void TIMER1_VidSetCTCValue(u16 Copy_u16CTCValue)
{
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A
	OCR1A = Copy_u16CTCValue;
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B
	OCR1B = Copy_u16CTCValue;
#else
#error "Timer1 Channel Option is not Valid"
#endif
}
//Timer1 Set Top Value
void TIMER1_VidSetTopValue(u16 Copy_u16TopValue)
{
	ICR1 = Copy_u16TopValue;
}
//Timer1 Select Sense Edge & Enable ICU Interrupt
void TIMER1_VidICUEnable(u8 Copy_u8Edge)
{
	/*Select Sense Control*/
	if(Copy_u8Edge == TIMER1_ICU_RAISING_EDGE)
	{
		SET_BIT(TCCR1B,6);
	}
	else if(Copy_u8Edge == TIMER1_ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,6);
	}
	/*ICU Interrupt Enable*/
	SET_BIT(TIMSK,5);
}

//Timer2 Initialization
void TIMER2_VidInit(void)
{
	/*Set Prescaler*/
	TCCR2&=0xF8;
	TCCR2|=TIMER2_SET_PRESCALER;
	/*Set Mode*/
#if TIMER2_SET_MODE == TIMER2_NORMAL_MODE   //Select Normal Mode
	CLR_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);
	/*Enable Overflow Interrupt*/
	SET_BIT(TIMSK,6);
#elif TIMER2_SET_MODE == TIMER2_CTC_MODE   //Select CTC Mode
	CLR_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);
	//OC2 Pin Option
#if TIMER2_OC2_MODE == TIMER2_OC2_DISCONNECTED  //OC2 Disconnected
	CLR_BIT(TCCR2,4);
	CLR_BIT(TCCR2,5);
#elif TIMER2_OC2_MODE == TIMER2_OC2_TOGGLE   //Toggle OC2
	SET_BIT(TCCR2,4);
	CLR_BIT(TCCR2,5);
#elif TIMER2_OC2_MODE == TIMER2_OC2_CLEAR   //Clear OC2
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
#elif TIMER2_OC2_MODE == TIMER2_OC2_SET   //Set OC2
	SET_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
#else
#error "Timer2 OC2 Pin Option is not Valid"
#endif
	/*Enable CTC Interrupt*/
	SET_BIT(TIMSK,7);
#elif TIMER2_SET_MODE == TIMER2_FAST_PWM_MODE   //Select Fast PWM Mode
	SET_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);
	//OC2 Pin Option
#if TIMER2_FAST_PWM_OC2_MODE == TIMER2_OC2_NON_INVERTING   //OC2 in Non Inverting Mode
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
#elif TIMER2_FAST_PWM_OC2_MODE == TIMER0_OC2_INVERTING   //OC2 in Inverting Mode
	SET_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
#else
#error "Timer2 OC2 Pin Option is not Valid"
#endif
#elif TIMER2_SET_MODE == TIMER2_PHASE_CORRECT_PWM_MODE   //Select Phase Correct Mode
	SET_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);
	//OC2 Pin Option
#if TIMER2_PHASE_CORRECT_PWM_OC2_MODE  == TIMER2_OC2_NON_INVERTING   //OC2 in Non Inverting Mode
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
#elif TIMER2_PHASE_CORRECT_PWM_OC2_MODE  == TIMER2_OC2_INVERTING   //OC2 in Inverting Mode
	SET_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
#else
#error "Timer2 OC2 Pin Option is not Valid"
#endif
#else
#error "Timer2 Mode Option is not Valid"
#endif
}
//Timer2 Set Preload
void TIMER2_VidSetPreload(u8 Copy_u8Preload)
{
	TCNT2 = Copy_u8Preload;
}
//Timer2 Set CTC Value
void TIMER2_VidSetCTCValue(u8 Copy_u8CTCValue)
{
	OCR2 = Copy_u8CTCValue;
}

