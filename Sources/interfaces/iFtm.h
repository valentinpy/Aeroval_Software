/*
 * Copyright (C) 2015 Valentin Py
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

#ifndef SOURCES_IFTM_H_
#define SOURCES_IFTM_H_

#include "../misc/def.h"
#include "../misc/derivative.h"
#include "iDio.h"

// PWM Out Enum
typedef enum
{
	kPwmOut0,
	kPwmOut1,
	kPwmOut2,
	kPwmOut3,
	kPwmOut4,
	kPwmOut5,
	kPwmOut6,
	kPwmOut7,
	kPwmOut8,
	kPwmOut9,
	kPwmOut10,
	kPwmOut11
}PwmOutEnum;

// PWM In Enum
typedef enum
{
	kPwmIn0,
	kPwmIn1,
	kPwmIn2,
	kPwmIn3,
	kPwmIn4,
	kPwmIn5,
	kPwmIn6,
	kPwmIn7
}PwmInEnum;


//------------------------------------------------------------
// Configure the FlexTimers
//------------------------------------------------------------
void iFtm_Config();

//------------------------------------------------------------
// Set a PWM output
//------------------------------------------------------------
void iFtm_SetPwm(PwmOutEnum aOut, UInt32 aTimeUs);


//------------------------------------------------------------
// Get a PWM input
//------------------------------------------------------------
UInt16 iFtm_ReadPwm(PwmInEnum aIn);

#endif /* SOURCES_IFTM_H_ */
