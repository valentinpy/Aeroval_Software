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

#ifndef SOURCES_MMOTORS_H_
#define SOURCES_MMOTORS_H_

#include "../interfaces/iFtm.h"
#include "../misc/def.h"

// Motors Enum
typedef enum
{
	kMotor0,
	kMotor1,
	kMotor2,
	kMotor3,
	kMotor4,
	kMotor5,
	kMotor6,
	kMotor7
}MotorsEnum;

//------------------------------------------------------------
// Setup motors
//------------------------------------------------------------
void mMotors_Setup();

//------------------------------------------------------------
// Stop all motors
//------------------------------------------------------------
void mMotors_StopAll();

//------------------------------------------------------------
// Idle all motors
//------------------------------------------------------------
void mMotors_IdleAll();

//------------------------------------------------------------
// Set speed (same) for all motors
// aSpeed: UInt16 0-1000. 0=off, 1000=full power
//------------------------------------------------------------
void mMotors_SetAllMotors(UInt16 aSpeed);

//------------------------------------------------------------
// Set speed for 1 motor
// aMotor: MotorsEnum. Select motor to set speed
// aSpeed: UInt16 0-1000. 0=off, 1000=full power
//------------------------------------------------------------
void mMotors_SetMotor(MotorsEnum aMotor, UInt16 aSpeed);

#endif /* SOURCES_MMOTORS_H_ */
