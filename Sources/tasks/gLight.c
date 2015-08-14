/*
 * gLight.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */


#include "gLight.h"

//-----------------------------------
// Light (LED strips) inialisation
//-----------------------------------
void gLight_Setup()
{
	//Configure LEDS and High-LEDS
	mLeds_Setup();
	mHleds_Setup();

	//Shut down lights
	mLeds_AllOff();
	mHleds_AllOff();

	//Get delays for 2 slow speed loops (human visible blink)
	gLight.aDelay2Hz = mDelay_GetDelay(kPit0, 250);
	gLight.aDelay5Hz = mDelay_GetDelay(kPit0, 100);
}

//-----------------------------------
// Run light
//-----------------------------------
void gLight_Run()
{

	// 2Hz loop
	if(mDelay_IsDelayDone(kPit0, gLight.aDelay2Hz)==true)
	{
		mDelay_ReStart(kPit0, gLight.aDelay2Hz, 250);

		mLeds_AllToggle();
	}

	// 5Hz loop
	if(mDelay_IsDelayDone(kPit0, gLight.aDelay5Hz)==true)
	{
		mDelay_ReStart(kPit0, gLight.aDelay5Hz, 100);

		if(gMiscSensors.aBatteryVoltage_mV > kBatLevelWarning)
		{
			//Roll
			if(gAttitudeSensors.aRoll_rad<-0.09)
			{
				mHleds_Toggle(kMaskHled0);
				mHleds_Write(kMaskHled1, kHledOn);
			}
			else if (gAttitudeSensors.aRoll_rad>0.09)
			{
				mHleds_Toggle(kMaskHled1);
				mHleds_Write(kMaskHled0, kHledOn);
			}
			else
			{
				mHleds_Write(kMaskHled0, kHledOn);
				mHleds_Write(kMaskHled1, kHledOn);
			}


			//Pitch
			if(gAttitudeSensors.aPitch_rad<-0.09)
			{
				mHleds_Toggle(kMaskHled2);
				mHleds_Write(kMaskHled3, kHledOn);
			}
			else if (gAttitudeSensors.aPitch_rad>0.09)
			{
				mHleds_Toggle(kMaskHled3);
				mHleds_Write(kMaskHled2, kHledOn);
			}
			else
			{
				mHleds_Write(kMaskHled2, kHledOn);
				mHleds_Write(kMaskHled3, kHledOn);
			}
		}
		else
		{
			mHleds_AllToggle();
		}

	}
}
