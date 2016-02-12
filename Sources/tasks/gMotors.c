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

#include "gMotors.h"
#include "../userDefined.h"

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
#ifdef MOTORS_NOMEDIANFILTER
			gMotors.aMotorsValuesOut[i] = gFlightCompute.aMotorsOutput[i];
#else
			gMotors.aMotorsValuesIn_0[i] = gFlightCompute.aMotorsOutput[i];
			gMotors.aMotorsValuesOut[i] = filter_MedianFilter(gMotors.aMotorsValuesIn_0[i], gMotors.aMotorsValuesIn_1[i], gMotors.aMotorsValuesIn_2[i]);
#endif
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
