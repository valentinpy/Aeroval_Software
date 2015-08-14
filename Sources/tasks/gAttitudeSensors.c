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
	gAttitudeSensors.aHeading_rad = 0.0;
	gAttitudeSensors.aPitch_rad   =	0.0;
	gAttitudeSensors.aRoll_rad 	  = 0.0;

	gAttitudeSensors.aHeading_mrad = 0;
	gAttitudeSensors.aPitch_mrad   = 0;
	gAttitudeSensors.aRoll_mrad    = 0;

	gAttitudeSensors.aTimeStamp = 0;
}

//-----------------------------------
// Attitude measurement
//-----------------------------------
void gAttitudeSensors_Run()
{
	EM7180_DataStruct aDataResult;

	//Get values from sensor
	mEm7180_GetEuler(&aDataResult);

	//Copy into mailbox
	gAttitudeSensors.aHeading_rad = aDataResult.QX.f;
	gAttitudeSensors.aPitch_rad = 	aDataResult.QZ.f;
	gAttitudeSensors.aRoll_rad = 	aDataResult.QY.f;

	gAttitudeSensors.aHeading_mrad = (Int16) (1000* aDataResult.QX.f);
	gAttitudeSensors.aPitch_mrad   = (Int16) (1000* aDataResult.QY.f);
	gAttitudeSensors.aRoll_mrad    = (Int16) (1000* aDataResult.QZ.f);

	gAttitudeSensors.aTimeStamp = aDataResult.QTime;
}
