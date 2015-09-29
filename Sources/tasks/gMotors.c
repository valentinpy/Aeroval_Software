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
	//Kill the motors if state is disarmed (for safety)
	if(gFlightCompute.aState==kDisarmed)
	{
		//Stop motors!
		mMotors_StopAll();

		//Show motors are stopped
		//Store values
		UInt8 i;
		for(i=0; i<8; i++)
		{
			gMotors.aMotorsValues[i] = 0;
		}
	}
	else if (gFlightCompute.aState == kArmed)
	{
		//Send values to motors
		mMotors_SetMotor(kMotor0, gMotors.aMotorsValues[0]);
		mMotors_SetMotor(kMotor1, gMotors.aMotorsValues[1]);
		mMotors_SetMotor(kMotor2, gMotors.aMotorsValues[2]);
		mMotors_SetMotor(kMotor3, gMotors.aMotorsValues[3]);

		mMotors_SetMotor(kMotor4, gMotors.aMotorsValues[4]);
		mMotors_SetMotor(kMotor5, gMotors.aMotorsValues[5]);
		mMotors_SetMotor(kMotor6, gMotors.aMotorsValues[6]);
		mMotors_SetMotor(kMotor7, gMotors.aMotorsValues[7]);

		//Store values
		gMotors.aMotorsValues[0] = gFlightCompute.aMotorsOutput[0];
		gMotors.aMotorsValues[1] = gFlightCompute.aMotorsOutput[1];
		gMotors.aMotorsValues[2] = gFlightCompute.aMotorsOutput[2];
		gMotors.aMotorsValues[3] = gFlightCompute.aMotorsOutput[3];

		gMotors.aMotorsValues[4] = gFlightCompute.aMotorsOutput[4];
		gMotors.aMotorsValues[5] = gFlightCompute.aMotorsOutput[5];
		gMotors.aMotorsValues[6] = gFlightCompute.aMotorsOutput[6];
		gMotors.aMotorsValues[7] = gFlightCompute.aMotorsOutput[7];
	}
}
