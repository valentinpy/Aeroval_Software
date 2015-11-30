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

#include "gLight.h"

//-----------------------------------
// Light (LED strips) initialisation
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
		mDelay_ReStart(kPit0, gLight.aDelay2Hz, 100);

		//TODO implement LEDS
		//Blink, as nothing else is implemented yet
		mLeds_AllToggle();
	}

	// 5Hz loop (10Hz?) //TODO fix frequency
	if(mDelay_IsDelayDone(kPit0, gLight.aDelay5Hz)==true)
	{
		mDelay_ReStart(kPit0, gLight.aDelay5Hz, 100);

		//If battery voltage is sufficient, blink to indicate orientation.
		//TODO store/check battery warning in mailbox
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

		//Battery is low, blink all leds to indicate.
		else
		{
			mHleds_AllToggle();
		}

	}
}
