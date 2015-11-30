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

#ifndef __mDelay__
#define __mDelay__

#include "../interfaces/iPit.h"
#include "../misc/def.h"

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
