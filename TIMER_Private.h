/*
 * TIMER_Private.h
 *
 *  Created on: Nov 18, 2023
 *      Author: Yasmin
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TIMSK    *((volatile u8*)0x59)
#define TCCR0    *((volatile u8*)0x53)
#define TCNT0    *((volatile u8*)0x52)
#define OCR0     *((volatile u8*)0x5C)
#define TCCR1A   *((volatile u8*)0x4F)
#define TCCR1B   *((volatile u8*)0x4E)
#define TCNT1    *((volatile u16*)0x4C)
#define OCR1A    *((volatile u16*)0x4A)
#define OCR1B    *((volatile u16*)0x48)
#define ICR1     *((volatile u16*)0x46)
#define TCCR2    *((volatile u16*)0x45)
#define TCNT2    *((volatile u16*)0x44)
#define OCR2     *((volatile u16*)0x43)


#define TIMER0_NO_PRESCALER     1
#define TIMER0_8_PRESCALER      2
#define TIMER0_64_PRESCALER     3
#define TIMER0_256_PRESCALER    4
#define TIMER0_1024_PRESCALER   5
#define TIMER0_EXTERNAL_CLOCK_FALLING_EDGE    6
#define TIMER0_EXTERNAL_CLOCK_RAISING_EDGE    7

#define TIMER0_NORMAL_MODE              0
#define TIMER0_CTC_MODE                 1
#define TIMER0_FAST_PWM_MODE            2
#define TIMER0_PHASE_CORRECT_PWM_MODE   3

#define TIMER0_OC0_DISCONNECTED   0
#define TIMER0_OC0_TOGGLE         1
#define TIMER0_OC0_CLEAR          2
#define TIMER0_OC0_SET            3

#define TIMER0_OC0_NON_INVERTING   0
#define TIMER0_OC0_INVERTING       1

#define TIMER1_CHANNEL_A   0
#define TIMER1_CHANNEL_B   1

#define TIMER1_NO_PRESCALER                   1
#define TIMER1_8_PRESCALER                    2
#define TIMER1_64_PRESCALER                   3
#define TIMER1_256_PRESCALER                  4
#define TIMER1_1024_PRESCALER                 5
#define TIMER1_EXTERNAL_CLOCK_FALLING_EDGE    6
#define TIMER1_EXTERNAL_CLOCK_RAISING_EDGE    7

#define TIMER1_NORMAL_MODE                                   0
#define TIMER1_PHASE_CORRECT_PWM_8_BIT_MODE                  1
#define TIMER1_PHASE_CORRECT_PWM_9_BIT_MODE                  2
#define TIMER1_PHASE_CORRECT_PWM_10_BIT_MODE                 3
#define TIMER1_CTC_MODE                                      4
#define TIMER1_FAST_PWM_8_BIT_MODE                           5
#define TIMER1_FAST_PWM_9_BIT_MODE                           6
#define TIMER1_FAST_PWM_10_BIT_MODE                          7
#define TIMER1_PHASE_AND_FREQUENCY_CORRECT_ICR1_AS_TOP_MODE    8
#define TIMER1_PHASE_AND_FREQUENCY_CORRECT_OCR1A_AS_TOP_MODE   9
#define TIMER1_PHASE_CORRECT_ICR1_AS_TOP_MODE                10
#define TIMER1_PHASE_CORRECT_OCR1A_AS_TOP_MODE               11
#define TIMER1_CTC_ICR1_AS_TOP_MODE                          12
#define TIMER1_FAST_PWM_ICR1_AS_TOP_MODE                     13
#define TIMER1_FAST_PWM_OCR1A_AS_TOP_MODE                    14

#define TIMER1_CTC_OC1A_AND_OC1B_DISCONNECRED   0
#define TIMER1_CTC_OC1A_AND_OC1B_TOGGLE         1
#define TIMER1_CTC_OC1A_AND_OC1B_CLEAR          2
#define TIMER1_CTC_OC1A_AND_OC1B_SET            3

#define TIMER1_FAST_PWM_OC1A_AND_OC1B_DISCONNECTED          0
#define TIMER1_FAST_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED       1
#define TIMER1_FAST_PWM_OC1A_AND_OC1B_NON_INVERTING         2
#define TIMER1_FAST_PWM_OC1A_AND_OC1B_INVERTING             3

#define TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_DISCONNECTED          0
#define TIMER1_PHASE_CORRECT_PWM_OC1A_TOGGLE_OC1B_DISCONNECTED       1
#define TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_NON_INVERTING         2
#define TIMER1_PHASE_CORRECT_PWM_OC1A_AND_OC1B_INVERTING             3

#define TIMER2_NO_PRESCALER     1
#define TIMER2_8_PRESCALER      2
#define TIMER2_32_PRESCALER     3
#define TIMER2_64_PRESCALER     4
#define TIMER2_128_PRESCALER    5
#define TIMER2_256_PRESCALER    6
#define TIMER2_1024_PRESCALER   7

#define TIMER2_NORMAL_MODE              0
#define TIMER2_CTC_MODE                 1
#define TIMER2_FAST_PWM_MODE            2
#define TIMER2_PHASE_CORRECT_PWM_MODE   3

#define TIMER2_OC2_DISCONNECTED   0
#define TIMER2_OC2_TOGGLE         1
#define TIMER2_OC2_CLEAR          2
#define TIMER2_OC2_SET            3

#define TIMER2_OC2_NON_INVERTING   0
#define TIMER2_OC2_INVERTING       1

#endif /* TIMER_PRIVATE_H_ */
