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
#include "../modules/mSwitches.h"
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

	//Setup IMU algorithms
	FusionAhrsInitialise(&gAttitudeSensors.aEM7180FusionAhrs, 0.5f, 20.0f, 70.0f);

	//Initialize variables

	//floats
	gAttitudeSensors.aHeading_rad = 0.0;
	gAttitudeSensors.aPitch_rad   =	0.0;
	gAttitudeSensors.aRoll_rad 	  = 0.0;

	gAttitudeSensors.aGyro_X_rads	= 0.0;
	gAttitudeSensors.aGyro_Y_rads	= 0.0;
	gAttitudeSensors.aGyro_Z_rads 	= 0.0;

	//UInt16
	gAttitudeSensors.aDeltaTimeEuler_us = 0;
	gAttitudeSensors.aDeltaTimeGyro_us 	= 0;
}

//-----------------------------------
// Attitude measurement initialization
//-----------------------------------
void gAttitudeSensors_Open()
{
//	while(FusionAhrsIsInitialising(&gAttitudeSensors.aFusionAhrs))
//	{
//		//TODO implement AHRS update 200hz + delay 5ms
//	}
}

//-----------------------------------
// Attitude measurement
//-----------------------------------
void gAttitudeSensors_Run()
{

	mEm7180_GetValues(&(gAttitudeSensors.aSensorValuesEM7180));
	mMPU6000_GetValues(&(gAttitudeSensors.aSensorValuesMPU6000));

#ifdef USE_EM7180
	//Copy gyro

	#ifndef GYRO_LP_FILTER
		gAttitudeSensors.aGyro_X_rads = kEM7180_GyroToRadS * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawGyroX));
		gAttitudeSensors.aGyro_Y_rads   = kEM7180_GyroToRadS * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawGyroY));
		gAttitudeSensors.aGyro_Z_rads    = kEM7180_GyroToRadS * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawGyroZ));

	#else
		gAttitudeSensors.aGyro_X_rads = filter_lowPassFilter(kEM7180_GyroToRadS * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawGyroX)), gAttitudeSensors.aGyro_X_rads, 0.6);
		gAttitudeSensors.aGyro_Y_rads = filter_lowPassFilter(kEM7180_GyroToRadS * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawGyroY)), gAttitudeSensors.aGyro_Y_rads, 0.6);
		gAttitudeSensors.aGyro_Z_rads = filter_lowPassFilter(kEM7180_GyroToRadS * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawGyroZ)), gAttitudeSensors.aGyro_Z_rads, 0.6);
	#endif

	//Copy accel
	gAttitudeSensors.aAccel_X = kEM7180_AccelToG * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawAccelX));
	gAttitudeSensors.aAccel_Y = kEM7180_AccelToG * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawAccelY));
	gAttitudeSensors.aAccel_Z = kEM7180_AccelToG * ((float)((Int16)gAttitudeSensors.aSensorValuesEM7180.RawAccelZ));
#else
	#error "Not implemented"
#endif

//#ifdef DEBUG_MODE
//	//Compute accel norm
//	float accelNorm =  sqrt((gAttitudeSensors.aAccel_X * gAttitudeSensors.aAccel_X)+
//							(gAttitudeSensors.aAccel_Y * gAttitudeSensors.aAccel_Y)+
//							(gAttitudeSensors.aAccel_Z * gAttitudeSensors.aAccel_Z));
//#endif

//UInt16
//TODO Warn: implement time difference: read old value and scale
//gAttitudeSensors.aDeltaTimeEuler_us = gAttitudeSensors.aSensorValuesEM7180.EulerDeltaTime_us;
//gAttitudeSensors.aDeltaTimeGyro_us = gAttitudeSensors.aSensorValuesEM7180.RawGyroDeltaTime;


//Choose sentral/orientation algorithm
if(mSwitches_Get(kMaskSwitch1))
{
	FusionVector3 gyroscope = {
		.axis.x = gAttitudeSensors.aGyro_X_rads,
		.axis.y = gAttitudeSensors.aGyro_Y_rads,
		.axis.z = gAttitudeSensors.aGyro_Z_rads,
	};
	FusionVector3 accelerometer = {
		.axis.x = gAttitudeSensors.aAccel_X,
		.axis.y = gAttitudeSensors.aAccel_Y,
		.axis.z = gAttitudeSensors.aAccel_Z,
	};

	//Extract HPR from madgwick's quaternion
	//TODO warn: dynamic sample rate for madgwick
	FusionAhrsUpdate(&gAttitudeSensors.aEM7180FusionAhrs, gyroscope, accelerometer, FUSION_VECTOR3_ZERO, 0.005); //Assume 200Hz sample rate, no magnetometers measurments
	FusionEulerAngles angles_rad = FusionQuaternionToEulerAngles_rad(gAttitudeSensors.aEM7180FusionAhrs.quaternion);

	gAttitudeSensors.aHeading_rad = angles_rad.angle.yaw;
	gAttitudeSensors.aPitch_rad   = angles_rad.angle.pitch;
	gAttitudeSensors.aRoll_rad 	  = -angles_rad.angle.roll;

}
else
{
	//Copy Sentral HPR
	gAttitudeSensors.aHeading_rad = (float)(gAttitudeSensors.aSensorValuesEM7180.EulerHeading_urad)/1000000;
	gAttitudeSensors.aPitch_rad   =	(float)(gAttitudeSensors.aSensorValuesEM7180.EulerPitch_urad)/1000000;
	gAttitudeSensors.aRoll_rad 	  = (float)(gAttitudeSensors.aSensorValuesEM7180.EulerRoll_urad)/1000000;
}


	//Add offset
	gAttitudeSensors.aPitch_rad   += gFlightCompute.aPitch_rad_offset;
	gAttitudeSensors.aRoll_rad    += gFlightCompute.aRoll_rad_offset;

	//Add offset
	gAttitudeSensors.aGyro_X_rads   += gFlightCompute.aGyro_X_rads_offset;
	gAttitudeSensors.aGyro_Y_rads    += gFlightCompute.aGyro_Y_rads_offset;
	gAttitudeSensors.aGyro_Z_rads    += gFlightCompute.aGyro_Z_rads_offset;

}
