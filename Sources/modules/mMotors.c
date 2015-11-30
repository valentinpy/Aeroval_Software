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

#include "mMotors.h"

//------------------------------------------------------------
// Setup motors
//------------------------------------------------------------
void mMotors_Setup()
{
	iFtm_Config();
	mMotors_SetAllMotors(0);
}

//------------------------------------------------------------
// Stop all motors
//------------------------------------------------------------
void mMotors_StopAll()
{
	mMotors_SetAllMotors(0);
}

//------------------------------------------------------------
// Idle all motors
//------------------------------------------------------------
void mMotors_IdleAll()
{
	//TODO check value
	mMotors_SetAllMotors(50);
}

//------------------------------------------------------------
// Set speed (same) for all motors
// aSpeed: UInt16 0-1000. 0=off, 1000=full power
//------------------------------------------------------------
void mMotors_SetAllMotors(UInt16 aSpeed)
{
	iFtm_SetPwm(kPwmOut0, (aSpeed+1000));
	iFtm_SetPwm(kPwmOut1, (aSpeed+1000));
	iFtm_SetPwm(kPwmOut2, (aSpeed+1000));
	iFtm_SetPwm(kPwmOut3, (aSpeed+1000));

	iFtm_SetPwm(kPwmOut4, (aSpeed+1000));
	iFtm_SetPwm(kPwmOut5, (aSpeed+1000));
	iFtm_SetPwm(kPwmOut6, (aSpeed+1000));
	iFtm_SetPwm(kPwmOut7, (aSpeed+1000));
}

//------------------------------------------------------------
// Set speed for 1 motor
// aMotor: MotorsEnum. Select motor to set speed
// aSpeed: UInt16 0-1000. 0=off, 1000=full power
//------------------------------------------------------------
void mMotors_SetMotor(MotorsEnum aMotor, UInt16 aSpeed)
{
	switch(aMotor)
	{
	case kMotor0:
		iFtm_SetPwm(kPwmOut0, (aSpeed+1000));
		break;

	case kMotor1:
		iFtm_SetPwm(kPwmOut1, (aSpeed+1000));
		break;

	case kMotor2:
		iFtm_SetPwm(kPwmOut2, (aSpeed+1000));
		break;

	case kMotor3:
		iFtm_SetPwm(kPwmOut3, (aSpeed+1000));
		break;

	case kMotor4:
		iFtm_SetPwm(kPwmOut4, (aSpeed+1000));
		break;

	case kMotor5:
		iFtm_SetPwm(kPwmOut5, (aSpeed+1000));
		break;

	case kMotor6:
		iFtm_SetPwm(kPwmOut6, (aSpeed+1000));
		break;

	case kMotor7:
		iFtm_SetPwm(kPwmOut7, (aSpeed+1000));
		break;

	default:
		break;
	}
}
