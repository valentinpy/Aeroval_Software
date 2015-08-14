/*
 * gMotors.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#include "gMotors.h"

//-----------------------------------
// Motors initialisation
//-----------------------------------
void gMotors_Setup()
{
	mMotors_Setup();
	mMotors_StopAll();
}

//-----------------------------------
// Send commands to motors
//-----------------------------------
void gMotors_Run()
{
	mMotors_SetAllMotors(150);
}
