/*
 * gAttitudeSensors.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */


#include "gAttitudeSensors.h"

//-----------------------------------
// Attitude measurement initialization
//-----------------------------------
void gAttitudeSensors_Setup()
{
	//Setup and open mEm7180
	mEm7180_Setup();
	mEm7180_Open();

	//Initialize variables

	//floats
	gAttitudeSensors.aHeading_rad = 0.0;
	gAttitudeSensors.aPitch_rad   =	0.0;
	gAttitudeSensors.aRoll_rad 	  = 0.0;

	//int
	gAttitudeSensors.aTimeStamp = 0;
}

//-----------------------------------
// Attitude measurement
//-----------------------------------
void gAttitudeSensors_Run()
{
	//Struct to stock data into
	EM7180_DataStruct aDataResult;

	//Get values from sensor
	mEm7180_GetEuler(&aDataResult);

	//Copy into mailbox

	gAttitudeSensors.aHeading_rad = aDataResult.QX.f;
	gAttitudeSensors.aPitch_rad = 	aDataResult.QY.f; //Z
	gAttitudeSensors.aRoll_rad = 	aDataResult.QZ.f; //Y

	gAttitudeSensors.aHeadingRate_rads = kGyroToRadS * ((float)aDataResult.GZ);
	gAttitudeSensors.aPitchRate_rads = kGyroToRadS * (float)(aDataResult.GY);
	gAttitudeSensors.aRollRate_rads = kGyroToRadS * ((float)aDataResult.GX);
/*
	gAttitudeSensors.aHeading_rad = 0;
	gAttitudeSensors.aPitch_rad = 	0;
	gAttitudeSensors.aRoll_rad = 	0;

	gAttitudeSensors.aHeadingRate_rads = 0;
	gAttitudeSensors.aPitchRate_rads = 0;
	gAttitudeSensors.aRollRate_rads = 0;*/

	//Add offset
	gAttitudeSensors.aPitch_rad   += gFlightCompute.aPitch_rad_offset;
	gAttitudeSensors.aRoll_rad    += gFlightCompute.aRoll_rad_offset;

	//Store time
	gAttitudeSensors.aTimeStamp = aDataResult.QTime;
}
