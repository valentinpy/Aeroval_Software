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

#include "mServos.h"

//------------------------------------------------------------
// Setup servos
//------------------------------------------------------------
void mServos_Setup()
{
	iFtm_Config();
}

//------------------------------------------------------------
// Set min and max for the servos
// TODO implement
//------------------------------------------------------------
void mServos_SetMinMax()
{
	//TODO implement
}

//------------------------------------------------------------
// Freewheel
// aServo: which servo
//------------------------------------------------------------
void mServos_Freewheel(ServosEnum aServo)
{
	switch (aServo)
	{
	case kServo0:
		iFtm_SetPwm(kPwmOut8, 0);
		break;

	case kServo1:
		iFtm_SetPwm(kPwmOut9, 0);
		break;

	case kServo2:
		iFtm_SetPwm(kPwmOut10, 0);
		break;

	case kServo3:
		iFtm_SetPwm(kPwmOut11, 0);
		break;

	default:
		break;
	}
}

//------------------------------------------------------------
// Set position of a servo
// aPosition: 0-1000
// aServo: which servo
//------------------------------------------------------------
void mServos_SetPosition(ServosEnum aServo, UInt16 aPosition)
{
	switch (aServo)
	{
	case kServo0:
		iFtm_SetPwm(kPwmOut8, (aPosition+1000));
		break;

	case kServo1:
		iFtm_SetPwm(kPwmOut9, (aPosition+1000));
		break;

	case kServo2:
		iFtm_SetPwm(kPwmOut10, (aPosition+1000));
		break;

	case kServo3:
		iFtm_SetPwm(kPwmOut11, (aPosition+1000));
		break;

	default:
		break;
	}
}
