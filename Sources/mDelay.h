/*
------------------------------------------------------------
Copyright 2003-2015 Haute école ARC Ingéniérie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name : 		mDelay.h	
Authors and date :	Serge Monnerat 	26.09.2014
					Valentin Py		15.06.2015

Goal :
This file provides all the necessary functions to interract with delays.

*/
#ifndef __mDelay__
#define __mDelay__

#include "def.h"
#include "iPit.h"


//-----------------------------------------------------------------------------
// Delay module setup
//-----------------------------------------------------------------------------
void mDelay_Setup(void);

//------------------------------------------------------------
// Get one delay
// aDelay	: delay time in ms
// Retour	: delay number or -1 if no more free delay
// 
//------------------------------------------------------------
Int16 mDelay_GetDelay(PitEnum aPit, UInt32 aDelay);

//------------------------------------------------------------
// Delay release
// aPit		: which PIT
// aDelayNb	: delay number
//------------------------------------------------------------
void mDelay_DelayRelease(PitEnum aPit, UInt16 aDelayNb);

//------------------------------------------------------------
// Delay restart
// aDelay		: delay time
// aDelayNb	: delay number
//------------------------------------------------------------
void mDelay_ReStart(PitEnum aPit, UInt16 aDelayNb,UInt32 aDelay);

//------------------------------------------------------------
// Check if the delay is done
// aDelayNb	: delay number
// Retour		: flag state
//------------------------------------------------------------
bool mDelay_IsDelayDone(PitEnum aPit, UInt16 aDelayNb);

#endif
