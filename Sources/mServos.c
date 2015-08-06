/*
 * mServos.c
 *
 *  Created on: 4 ao�t 2015
 *      Author: valentin.py
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
