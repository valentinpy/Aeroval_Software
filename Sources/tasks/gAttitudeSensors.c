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

	//milli-int
	gAttitudeSensors.aHeading_urad = 0;
	gAttitudeSensors.aPitch_urad   = 0;
	gAttitudeSensors.aRoll_urad    = 0;

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
	gAttitudeSensors.aPitch_rad = 	aDataResult.QZ.f;
	gAttitudeSensors.aRoll_rad = 	aDataResult.QY.f;

	//Copy in milli-radians (int16, signed)
	gAttitudeSensors.aHeading_urad = (Int32) (1000000* aDataResult.QX.f);
	gAttitudeSensors.aPitch_urad   = (Int32) (1000000* aDataResult.QY.f);
	gAttitudeSensors.aRoll_urad    = (Int32) (1000000* aDataResult.QZ.f);

	//Add offset
	gAttitudeSensors.aPitch_urad   += gFlightCompute.aPitch_urad_offset;
	gAttitudeSensors.aRoll_urad    += gFlightCompute.aRoll_urad_offset;

	//Store time
	gAttitudeSensors.aTimeStamp = aDataResult.QTime;
}
