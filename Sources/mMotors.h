/*
 * mMotors.h
 *
 *  Created on: 4 ao�t 2015
 *      Author: valentin.py
 */

#ifndef SOURCES_MMOTORS_H_
#define SOURCES_MMOTORS_H_

#include "iFtm.h"
#include "def.h"

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
