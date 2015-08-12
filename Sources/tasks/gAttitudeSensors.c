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
	gAttitudeSensors.aHeading = 0.0;
	gAttitudeSensors.aPitch = 	0.0;
	gAttitudeSensors.aRoll = 	0.0;

}

//-----------------------------------
// Attitude measurement
//-----------------------------------
void gAttitudeSensors_Run()
{
	EM7180_DataStruct aDataResult;

	//Get values from sensor
	mEm7180_GetQuaternions(&aDataResult);

	//Copy into mailbox
	gAttitudeSensors.aHeading = aDataResult.QX.f;
	gAttitudeSensors.aPitch = 	aDataResult.QZ.f;
	gAttitudeSensors.aRoll = 	aDataResult.QY.f;
	gAttitudeSensors.aTimeStamp = aDataResult.QTime;
}
