/*
 * gMotors.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#include "gMotors.h"
#include "../misc/filters.h"

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
			gMotors.aMotorsValuesIn_0[i] = 0;
			gMotors.aMotorsValuesIn_1[i] = 0;
			gMotors.aMotorsValuesIn_2[i] = 0;
			gMotors.aMotorsValuesOut[i]=0;
		}
	}
	else if (gFlightCompute.aState == kArmed)
	{

		//Filter values
		int i=0;
		for(i=0; i<8; i++)
		{
			gMotors.aMotorsValuesIn_0[i] = gFlightCompute.aMotorsOutput[i];
			gMotors.aMotorsValuesOut[i] = misc_MedianFilter(gMotors.aMotorsValuesIn_0[i], gMotors.aMotorsValuesIn_1[i], gMotors.aMotorsValuesIn_2[i]);
		}


		//Store for next iteration
		for(i=0; i<8; i++)
		{
			gMotors.aMotorsValuesIn_2[i]=gMotors.aMotorsValuesIn_1[i];
			gMotors.aMotorsValuesIn_1[i]=gMotors.aMotorsValuesIn_0[i];
		}

		//Send values to motors
		if(mSwitches_Get(kMaskSwitch0))
		{
			mMotors_SetMotor(kMotor0, gMotors.aMotorsValuesOut[M0]);
			mMotors_SetMotor(kMotor1, gMotors.aMotorsValuesOut[M1]);
			mMotors_SetMotor(kMotor2, gMotors.aMotorsValuesOut[M2]);
			mMotors_SetMotor(kMotor3, gMotors.aMotorsValuesOut[M3]);

			mMotors_SetMotor(kMotor4, gMotors.aMotorsValuesOut[M4]);
			mMotors_SetMotor(kMotor5, gMotors.aMotorsValuesOut[M5]);
			mMotors_SetMotor(kMotor6, gMotors.aMotorsValuesOut[M6]);
			mMotors_SetMotor(kMotor7, gMotors.aMotorsValuesOut[M7]);
		}
		else
		{
			mMotors_StopAll();
		}
	}
}
