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

#include "gAttitudeSensors.h"
#include "../misc/filters.h"
#include <math.h>

//-----------------------------------
// Attitude measurement initialization
//-----------------------------------
void gAttitudeSensors_Setup()
{
	//Setup and open EM7180
	mEM7180_Setup(&(gAttitudeSensors.aSensorValuesEM7180));
	mEM7180_Open();

	//Setup and open MPU6000
	mMPU6000_Setup(&(gAttitudeSensors.aSensorValuesEM7180));
	mMPU6000_Open();

	//Initialize variables

	//floats
	gAttitudeSensors.aHeading_rad = 0.0;
	gAttitudeSensors.aPitch_rad   =	0.0;
	gAttitudeSensors.aRoll_rad 	  = 0.0;

	gAttitudeSensors.aHeadingRate_rads	= 0.0;
	gAttitudeSensors.aPitchRate_rads	= 0.0;
	gAttitudeSensors.aRollRate_rads 	= 0.0;

	//UInt16
	gAttitudeSensors.aDeltaTimeEuler_us = 0;
	gAttitudeSensors.aDeltaTimeGyro_us 	= 0;
}

//-----------------------------------
// Attitude measurement
//-----------------------------------
void gAttitudeSensors_Run()
{

	mEm7180_GetValues(&(gAttitudeSensors.aSensorValuesEM7180));
	mMPU6000_GetValues(&(gAttitudeSensors.aSensorValuesMPU6000));

#ifdef USE_EM7180

	//Read Sentral quaternions
	gAttitudeSensors.aHeading_rad = (float)(gAttitudeSensors.aSensorValuesEM7180.EulerHeading_urad)/1000000;
	gAttitudeSensors.aPitch_rad   =	(float)(gAttitudeSensors.aSensorValuesEM7180.EulerPitch_urad)/1000000;
	gAttitudeSensors.aRoll_rad 	  = (float)(gAttitudeSensors.aSensorValuesEM7180.EulerRoll_urad)/1000000;

	//Read gyro
	gAttitudeSensors.aHeadingRate_rads = kEM7180_GyroToRadS * ((float)(gAttitudeSensors.aSensorValuesEM7180.RawGyroX));
	gAttitudeSensors.aPitchRate_rads   = kEM7180_GyroToRadS * ((float)(gAttitudeSensors.aSensorValuesEM7180.RawGyroY));
	gAttitudeSensors.aRollRate_rads    = kEM7180_GyroToRadS * ((float)(gAttitudeSensors.aSensorValuesEM7180.RawGyroZ));

	//Read accel
	gAttitudeSensors.aAccel_X = kEM7180_AccelToG * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawAccelX));
	gAttitudeSensors.aAccel_Y = kEM7180_AccelToG * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawAccelY));
	gAttitudeSensors.aAccel_Z = kEM7180_AccelToG * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawAccelZ));

#ifdef DEBUG_MODE
	//Compute accel norm
	float accelNorm =  sqrt((gAttitudeSensors.aAccel_X * gAttitudeSensors.aAccel_X)+
							(gAttitudeSensors.aAccel_Y * gAttitudeSensors.aAccel_Y)+
							(gAttitudeSensors.aAccel_Z * gAttitudeSensors.aAccel_Z));
#endif

	MadgwickAHRSupdateIMU()

	//UInt16
	//TODO Warn: implement time difference: read old value and scale
	//gAttitudeSensors.aDeltaTimeEuler_us = gAttitudeSensors.aSensorValuesEM7180.EulerDeltaTime_us;
	//gAttitudeSensors.aDeltaTimeGyro_us = gAttitudeSensors.aSensorValuesEM7180.RawGyroDeltaTime;



#else
	#error "Not implemented"
#endif


#ifdef GYRO_LP_FILTER
	#error "Not implemented"
	//Filter
	//TODO Implement Gyro LP filter
	//This won't work, because we need previous value, which is not stored at this time
	//gAttitudeSensors.aHeadingRate_rads =  filter_lowPassFilter(kEM7180_GyroToRadS * ((float)(gAttitudeSensors.aSensorValuesEM7180.RawGyroX)), gAttitudeSensors.aHeadingRate_rads, 0.6);
	//gAttitudeSensors.aPitchRate_rads =  filter_lowPassFilter(kEM7180_GyroToRadS * ((float)(gAttitudeSensors.aSensorValuesEM7180.RawGyroYX)), gAttitudeSensors.aPitchRate_rads, 0.6);
	//gAttitudeSensors.aRollRate_rads =  filter_lowPassFilter(kEM7180_GyroToRadS * ((float)(gAttitudeSensors.aSensorValuesEM7180.RawGyroZ)), gAttitudeSensors.aRollRate_rads, 0.6);
#endif

	//Add offset
	gAttitudeSensors.aPitch_rad   += gFlightCompute.aPitch_rad_offset;
	gAttitudeSensors.aRoll_rad    += gFlightCompute.aRoll_rad_offset;
}
