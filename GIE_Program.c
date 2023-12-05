/*
 * GIE_Program.c
 *
 *  Created on: Oct 31, 2023
 *      Author: Yasmin
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_Private.h"

//Enable Global Interrupt
void GIE_VidEnable(void)
{
	SET_BIT(SREG,7);
}
//Disable Global Interrupt
void GIE_VidDisable(void)
{
	CLR_BIT(SREG,7);
}
