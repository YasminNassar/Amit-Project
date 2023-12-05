/*
 * GCD_Program.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Yasmin
 */

#define F_CPU   2000000UL
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "GLCD_Private.h"
#include "GLCD_Config.h"
#include "Font_Header.h"
#include <math.h>
#include <util/delay.h>

u8 Y = 0;   //Global Variable to Track Column Address
u8 X = 0;   //Global Variable to Track Page

//Send Command
void GLCD_VidSendCommand(u8 Copy_u8Command)
{
	//Choose Write Mode (RW)
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN1,PIN_LOW);
	//Select Command Register (RS)
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN0,PIN_LOW);
	//Send Command
	DIO_VidSetPortValue(GLCD_DATA_PORT,Copy_u8Command);
	//Enable
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN2,PIN_HIGH);
	_delay_us(5);
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN2,PIN_LOW);
	_delay_us(5);
}
//GLCD Initialization
void GLCD_VidInit(void)
{
	//Select CS1, CS2 & Set Reset Pin to High
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN5,PIN_HIGH);
	_delay_ms(20);
	GLCD_VidSendCommand(GLCD_DISPLAY_OFF);   //Display Off
	GLCD_VidSendCommand(GLCD_START_COLUMN);  //Set Column to address 0x40
	GLCD_VidSendCommand(GLCD_START_PAGE);    //Set Page to 0xB8
	GLCD_VidSendCommand(GLCD_START_LINE);    //Set Line to 0xC0
	GLCD_VidSendCommand(GLCD_DISPLAY_ON);    //Display On
}
//Send Data
void GLCD_VidSendData(u8 Copy_u8Data)
{
	//Choose Write Mode (RW)
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN1,PIN_LOW);
	//Select Data Register (RS)
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN0,PIN_HIGH);
	//Send Command
	DIO_VidSetPortValue(GLCD_DATA_PORT,Copy_u8Data);
	//Enable
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN2,PIN_HIGH);
	_delay_us(5);
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN2,PIN_LOW);
	_delay_us(5);
}
//Clear Screen
void GLCD_VidClear(void)
{
	// Select CS1 & CS2 (Both Left & Right Sides)
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
	//GLCD_VidSendCommand(0xB8);   //Set Page to 0xB8
	//GLCD_VidSendCommand(0x40);   //Set Column to address 0x40
	u8 i;
	u8 ii;

	for(i=0;i<8;i++)
	{
		GLCD_VidSendCommand(0xB8 + i);   //Increment Page
		for(ii=0;ii<64;ii++)
		{
			GLCD_VidSendData(0x00);   //Write Zeros to All 64 Column
		}
	}
	GLCD_VidSendCommand(0xB8);   //Set Page to 0xB8
	GLCD_VidSendCommand(0x40);   //Set Column to address 0x40
}
//Set Position in GLCD
void GLCD_VidSetPosition(u8 Copy_u8Page, u8 Copy_u8Column)
{
	Y = Copy_u8Column;
	X = Copy_u8Page;

	if(Copy_u8Column < 64)
	{
		//Select CS1 (Left Side)
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_LOW);
		GLCD_VidSendCommand(0xB8 + Copy_u8Page);     //Set Page
		GLCD_VidSendCommand(0x40 + Copy_u8Column);   //Set Column
	}
	else if(Copy_u8Column >= 64)
	{
		//Select CS2 (Right Side)
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
		GLCD_VidSendCommand(0xB8 + Copy_u8Page);   //Set Page
		GLCD_VidSendCommand(Copy_u8Column);        //Set Column
	}
}
//Send String
void GLCD_VidSendString(u8 *Copy_u8String)
{
	u8 i = 0;
	u8 ii;

	if(Y < 64)
	{
		//Select CS1 (Left Side)
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_LOW);
	}
	else if(Y >= 64)
	{
		//Select CS2 (Right Side)
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
	}

	while (Copy_u8String[i] != '\0')   //Print char in string till null
	{
		if((Y+6) > 128)   //Check if Column address reaches 128 (End of Right Side of GLCD) & There is Enough Columns For The Last Character
		{
			//Select CS1 (Left Side)
			DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
			DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_LOW);
			GLCD_VidSendCommand(0xB8+X+1);   //Set Page & Increment to the next Page
			GLCD_VidSendCommand(0x40);       //Set Column to address 0x40
			X++;                             //Increment The Page Tracker Variable
			Y = 0;                           //Reset The Column Tracker Variable
		}
		for(ii = 0; ii < 5; ii++ )   //For Every Column in Font Array
		{
			if(Y == 64)   //Check if Column address reaches 64 (Start of Right Side of GLCD)
			{
				//Select CS2 (Right Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
				GLCD_VidSendCommand(0xB8+X);   //Set Page
				GLCD_VidSendCommand(0x40);     //Set Column to address 0x40
			}
			if(Y == 128)   //Check if Column address reaches 128 (End of Right Side of GLCD)
			{
				//Select CS1 (Left Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_LOW);
				GLCD_VidSendCommand(0xB8+X+1);   //Set Page & Increment to the next Page
				GLCD_VidSendCommand(0x40);       //Set Column to address 0x40
				X++;                             //Increment The Page Tracker Variable
				Y = 0;                           //Reset The Column Tracker Variable
			}
			GLCD_VidSendData(font[Copy_u8String[i] - 32][ii]);   //Send First Column of the Char in Font Array
			Y++;                                                 //Increment The Column Tracker Variable
		}
		if(Y == 64)   //Check if Column address reaches 64 (Start of Right Side of GLCD)
		{
			//Select CS2 (Right Side)
			DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
			DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
			GLCD_VidSendCommand(0xB8+X);   //Set Page
			GLCD_VidSendCommand(0x40);     //Set Column to address 0x40
		}
		if((Copy_u8String[i+1] != 32) && (Copy_u8String[i] != 32) && (Y != 0))   //If The Char is Space or The Next Char is Space or The Character is at Column 0
		{
			GLCD_VidSendData(0x00);   //Send Zeroes to Display Space between Characters
			Y++;                      //Increment The Column Tracker Variable
		}
		i++;   //Increment to the next Char in The String
	}
}
//Send Number to GLCD
void GLCD_VidSendingNumber(u8 Copy_u8Number)
{
	u8 ii;

	for(ii = 0; ii < 5; ii++ )   //For Every Column in Font Array
	{
		if(Y == 64)   //Check if Column address reaches 64 (Start of Right Side of GLCD)
		{
			//Select CS2 (Right Side)
			DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
			DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
			GLCD_VidSendCommand(0xB8+X);   //Set Page
			GLCD_VidSendCommand(0x40);     //Set Column to address 0x40
		}
		if(Y == 128)   //Check if Column address reaches 128 (End of Right Side of GLCD)
		{
			//Select CS1 (Left Side)
			DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
			DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_LOW);
			GLCD_VidSendCommand(0xB8+X+1);   //Set Page & Increment to the next Page
			GLCD_VidSendCommand(0x40);       //Set Column to address 0x40
			X++;                             //Increment The Page Tracker Variable
			Y = 0;                           //Reset The Column Tracker Variable
		}
		GLCD_VidSendData(font[Copy_u8Number][ii]);   //Send Number
		Y++;                                         //Increment The Column Tracker Variable
	}
}
//Convert Number to Character
void GLCD_VidSendNumber(f32 Copy_u32Number)
{
	u8 Arr[10];   //Array to Store Number
	u8 i = 0;
	u8 j = 0;
	u8 Number_Float_Exist = 0;   //Variable to Check For Float Number
	u8 Dot = 0;
	u32 Number_int = Copy_u32Number;   //Store Integral Part of The Number
	u32 Number_int_Copy = Copy_u32Number;
	f32 Number_float = (Copy_u32Number - Number_int);   //Store Float Part of The Number
	f32 Number_float_remain = 0;

	while(Number_int_Copy != 0)   //While The Integral Part is Not Zero
	{
		Number_int_Copy/=10;           //Divide By 10
		j++;                      //Count Integral Numbers
	}

	if(Number_int == 0)  //Save Place For zero if Integral Number is Zero
	{
		j = 1;
	}

	if(Number_float !=0)   //Check If There is Float Numbers to Add Their Places
	{
		Number_Float_Exist = 3;
		Dot = 5;
	}

	if((Y+(((j+Number_Float_Exist)*6)+Dot)) > 128)   //Calculate Places Needed to Represent The Number
	{
		//Select CS1 (Left Side)
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
		DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_LOW);
		GLCD_VidSendCommand(0xB8+X+1);   //Set Page & Increment to the next Page
		GLCD_VidSendCommand(0x40);       //Set Column to address 0x40
		X++;                             //Increment The Page Tracker Variable
		Y = 0;                           //Reset The Column Tracker Variable
	}
	if(Copy_u32Number != 0)   //If The Number is Not Zero (Both Integral & Float Part)
	{
		if(Number_int != 0)   //If The Integral Part is Not Zero
		{
			j = 0;
			while(Number_int != 0)   //While The Integral Part is Not Zero
			{
				Arr[j] = Number_int%10;   //Store The Reminder in The Array
				Number_int/=10;           //Divide By 10
				j++;                      //Increment to The Next Position in The Array
			}

			//Print The Integral Part on The GLCD
			if(Y < 64)   //If Start Column is in the Left Side of The GLCD
			{
				//Select CS1 (Left Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_LOW);
			}
			else if(Y >= 64)   //If Start Column is in the Right Side of The GLCD
			{
				//Select CS2 (Right Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
			}

			for(s8 jj=j-1;jj>=0;jj--)  //For All Integral Numbers
			{
				GLCD_VidSendingNumber((Arr[jj]+16));   //Send First Column of the Char in Font Array

				if(Y == 64)   //Check if Column address reaches 64 (Start of Right Side of GLCD)
				{
					//Select CS2 (Right Side)
					DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
					DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
					GLCD_VidSendCommand(0xB8+X);   //Set Page
					GLCD_VidSendCommand(0x40);     //Set Column to address 0x40
					Y++;                           //Increment The Column Tracker Variable
				}
				if((Arr[jj+1] != 32) && (Arr[jj] != 32))   //If The Char is Space or The Next Char is Space
				{
					GLCD_VidSendData(0x00);   //Send Zeroes to Display Space between Characters
					Y++;                      //Increment The Column Tracker Variable
				}
			}
		}
		else
		{
			GLCD_VidSendingNumber(16);   //Send '0'
		}

		if(Number_float != 0)   //If The Float Part is Not Zero
		{
			GLCD_VidSendingNumber(14);  //Send '.'
			j = 0;
			while(i<3)   //For 3 Decimal Point Precision
			{
				Arr[j] = (Number_float*10);                      //Store The Number in The Array
				Number_float = (Number_float*10);                //Multiply By 10
				Number_float_remain = (Number_float - Arr[j]);   //Store The Remain Numbers to Be Saved in The Array
				Number_float = Number_float_remain;              //Update The Float Number
				j++;                                             //Increment to The Next Position in The Array
				i++;
			}
			if(Y < 64)   //If Start Column is in the Left Side of The GLCD
			{
				//Select CS1 (Left Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_LOW);
			}
			else if(Y >= 64)   //If Start Column is in the Right Side of The GLCD
			{
				//Select CS2 (Right Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
			}

			for(u8 jj=0;jj<j;jj++)   //For All Float Numbers
			{
				GLCD_VidSendingNumber((Arr[jj]+16));
				if(Y == 64)   //Check if Column address reaches 64 (Start of Right Side of GLCD)
				{
					//Select CS2 (Right Side)
					DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
					DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
					GLCD_VidSendCommand(0xB8+X);   //Set Page
					GLCD_VidSendCommand(0x40);     //Set Column to address 0x40
					Y++;                           //Increment The Column Tracker Variable
				}
				if((Arr[jj+1] != 32) && (Arr[jj] != 32))   //If The Char is Space or The Next Char is Space
				{
					GLCD_VidSendData(0x00);   //Send Zeroes to Display Space between Characters
					Y++;                      //Increment The Column Tracker Variable
				}
			}
		}
	}
	else   //If The Number is Zero (Both Integral & Float Part)
	{
		GLCD_VidSendingNumber(16);   //Send '0'
		GLCD_VidSendData(0x00);      //Send Zeroes to Display Space between Characters
		Y++;                         //Increment The Column Tracker Variable
	}
}
//Draw PWM Waveform
void GLCD_VidDrawPWM(u8 Copy_u8Page, f32 Frequency, f32 DutyCycle)
{
	u8 i;
	u8 Y = 0;   //Reset Column Tracker Variable
	u32 PWMNumber = round(((Frequency*1000)*16.0)/244);   //Calculate Max Number of Waves to be Displayed in 128 Column
	u32 PWMLength = (128/PWMNumber);   //Calculate Wave Length
	f32 Level = (PWMLength - 2);   //Subtract 2 From The WaveLength to be Represented as Edges
	f32 Ton = round((Level*DutyCycle)/100);   //Calculate Ton
	u32 Toff = (Level - Ton);   //Calculate Toff

	/*GLCD_VidSetPosition(4,64);
	GLCD_VidSendNumber(PWMLength);
	GLCD_VidSetPosition(5,64);
	GLCD_VidSendNumber(Level);
	GLCD_VidSetPosition(6,64);
	GLCD_VidSendNumber(Ton);
	GLCD_VidSetPosition(7,64);
	GLCD_VidSendNumber(Toff);*/

	//Select CS1 (Left Side)
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_HIGH);
	DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_LOW);
	GLCD_VidSendCommand(0xB8 + Copy_u8Page);   //Set Page
	GLCD_VidSendCommand(0x40);                 //Set Column to address 0x40

	while(1)   //While Not Reaching The End of The GLCD
	{
		for(i=0;i<Ton;i++)   //For High Level Period (Ton)
		{
			if(Y == 64)   //Check if Column address reaches 64 (Start of Right Side of GLCD)
			{
				//Select CS2 (Right Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
				GLCD_VidSendCommand(0xB8 + Copy_u8Page);   //Set Page
				GLCD_VidSendCommand(0x40);                 //Set Column to address 0x40
			}
			if(Y == 128)   //Check if Column address reaches 128 (End of Right Side of GLCD)
			{
				return;   //Break From Function
			}
			GLCD_VidSendData(0x01);   //Send 0x01 to Display High Level
			Y++;                      //Increment The Column Tracker Variable
		}

		if((Toff != 0) && (Ton != 0))   //If the Wave is not fully High/Low Level
		{
			if(Y == 64)   //Check if Column address reaches 64 (Start of Right Side of GLCD)
			{
				//Select CS2 (Right Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
				GLCD_VidSendCommand(0xB8 + Copy_u8Page);   //Set Page
				GLCD_VidSendCommand(0x40);                 //Set Column to address 0x40
			}
			if(Y == 128)   //Check if Column address reaches 128 (End of Right Side of GLCD)
			{
				return;   //Break From Function
			}
			GLCD_VidSendData(0xFF);   //Send 0xFF to Display Vertical Line (Represents Edge)
			Y++;                      //Increment The Column Tracker Variable
		}

		for(i=0;i<Toff;i++)   //For Low Level Period (Toff)
		{
			if(Y == 64)   //Check if Column address reaches 64 (Start of Right Side of GLCD)
			{
				//Select CS2 (Right Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
				GLCD_VidSendCommand(0xB8 + Copy_u8Page);   //Set Page
				GLCD_VidSendCommand(0x40);                 //Set Column to address 0x40
			}
			if(Y == 128)   //Check if Column address reaches 128 (End of Right Side of GLCD)
			{
				return;   //Break From Function
			}
			GLCD_VidSendData(0x80);   //Send 0x80 to Display Low Level
			Y++;                      //Increment The Column Tracker Variable
		}

		if((Toff != 0) && (Ton != 0))   //If the Wave is not fully High/Low Level
		{
			if(Y == 64)   //Check if Column address reaches 64 (Start of Right Side of GLCD)
			{
				//Select CS2 (Right Side)
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN3,PIN_LOW);
				DIO_VidSetPinValue(GLCD_CONTROL_PORT,PIN4,PIN_HIGH);
				GLCD_VidSendCommand(0xB8 + Copy_u8Page);   //Set Page
				GLCD_VidSendCommand(0x40);                 //Set Column to address 0x40
			}
			if(Y == 128)   //Check if Column address reaches 128 (End of Right Side of GLCD)
			{
				return;   //Break From Function
			}
			GLCD_VidSendData(0xFF);   //Send 0xFF to Display Vertical Line (Represents Edge)
			Y++;                      //Increment The Column Tracker Variable
		}
	}
}
