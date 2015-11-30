/*
 * Copyright (C) 2015 Valentin Py
 * Copyright (C) 2014 Serge Monnerat
 *
 * This file is part of Aeroval.
 *
 * Aeroval is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Aeroval is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mDelay.h"

//periods of pit interrupts [us]
#define kPit0Per 1000
#define kPit1Per 100
#define kPit2Per 1000
#define kPit3Per 1000

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
	iPit_InitDelay(kPit1);
	//iPit_InitDelay(kPit2);
	//iPit_InitDelay(kPit3);

	//Start PIT0
	iPit_StartPit(kPit0);
	iPit_StartPit(kPit1);
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
