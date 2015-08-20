/*
------------------------------------------------------------
Copyright 2003-2015 Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name : 		mDelay.c	
Authors and date :	Serge Monnerat 	26.09.2014
					Valentin Py		15.06.2015

Goal :
This file provides all the necessary functions to interract with delays.


*/

#include "mDelay.h"

//periods of pit interrupts [ms]
#define kPit0Per 1
#define kPit1Per 100
#define kPit2Per 100
#define kPit3Per 100

//-----------------------------------------------------------------------------
// Delay module setup
//-----------------------------------------------------------------------------
void mDelay_Setup(void)
{
	//Configure PIT0-3
	iPit_Config(kPit0,kPit0Per);
	iPit_Config(kPit1,kPit1Per);
	iPit_Config(kPit2,kPit2Per);
	iPit_Config(kPit3,kPit3Per);


	// PIT delays structure setup
	iPit_InitDelay(kPit0);
	//iPit_InitDelay(kPit1);
	//iPit_InitDelay(kPit2);
	//iPit_InitDelay(kPit3);

	//Start PIT0
	iPit_StartPit(kPit0);
	//iPit_StartPit(kPit1);
	//iPit_StartPit(kPit2);
	//iPit_StartPit(kPit3);
}
//------------------------------------------------------------
// Get one delay
// aDelay	: delay time in ms
// Retour	: delay number or -1 if no more free delay
// 
//------------------------------------------------------------
Int16 mDelay_GetDelay(PitEnum aPit, UInt32 aDelay)
{
	return iPit_GetDelay(aPit, aDelay);
}

//------------------------------------------------------------
// Delay release
// aDelayNb	: delay number
//------------------------------------------------------------
void mDelay_DelayRelease(PitEnum aPit, UInt16 aDelayNb)
{
	iPit_DelayRelease(aPit, aDelayNb);
}

//------------------------------------------------------------
// Delay restart
// aDelay		: delay time
// aDelayNb	: delay number
//------------------------------------------------------------
void mDelay_ReStart(PitEnum aPit, UInt16 aDelayNb,UInt32 aDelay)
{
	iPit_ReStart(aPit, aDelayNb,aDelay);
}


//------------------------------------------------------------
// Check if the delay is done
// aDelayNb	: delay number
// Retour		: flag state
//------------------------------------------------------------
bool mDelay_IsDelayDone(PitEnum aPit, UInt16 aDelayNb)
{
	return iPit_IsDelayDone(aPit, aDelayNb);
}
