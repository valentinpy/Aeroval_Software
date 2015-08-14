/*
 * gMiscSensors.c
 *
 *  Created on: 12 août 2015
 *      Author: valentinpy
 */

#include "gMiscSensors.h"

//-----------------------------------
// Miscellaneous sensors initialization
//-----------------------------------
void gMiscSensors_Setup()
{
	mAd_Setup();
}

//-----------------------------------
// Miscellaneous sensors measurement
//-----------------------------------
void gMiscSensors_Run()
{
	//Get battery voltage
	gMiscSensors.aBatteryVoltage_mV = (UInt16)(1000 * mAd_readBattVoltage());
}



