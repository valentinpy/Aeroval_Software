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
	gLight.aDelayLeds = mDelay_GetDelay(kPit0, 100);
	gLight.aDelayHLeds = mDelay_GetDelay(kPit0, 100);
}

//-----------------------------------
// Run light
//-----------------------------------
void gLight_Run()
{
	//PCB LEDS
	if(mDelay_IsDelayDone(kPit0, gLight.aDelayLeds)==true)
	{
		if(kAngle==gFlightCompute.aFLightMode) //Angle / stable mode - blink slow
		{
			mLeds_AllToggle();

			mDelay_ReStart(kPit0, gLight.aDelayLeds, 500);

		}
		else if(kRate==gFlightCompute.aFLightMode) //Angular speed (acro) mode - blink fast
		{
			mLeds_AllToggle();

			mDelay_ReStart(kPit0, gLight.aDelayLeds, 100);

		}
		else //Other flight mode
		{
			mLeds_AllOff();

			mDelay_ReStart(kPit0, gLight.aDelayLeds, 100);
		}
	}

	//Power LEDS
	if(mDelay_IsDelayDone(kPit0, gLight.aDelayHLeds)==true)
	{
		mDelay_ReStart(kPit0, gLight.aDelayHLeds, 100);

		//If battery voltage is sufficient, blink to indicate orientation.
		//TODO store/check battery warning in mailbox
		if(gMiscSensors.aBatteryVoltage_mV > kBatLevelWarning)
		{
			//Forward-left
			if((gAttitudeSensors.aRoll_rad<-0.09) && (gAttitudeSensors.aPitch_rad<-0.09))
			{
				mHleds_Toggle(kMaskHled2);

				mHleds_Write(kMaskHled0, kHledOn);
				mHleds_Write(kMaskHled1, kHledOn);
				mHleds_Write(kMaskHled3, kHledOn);

			}

			//Forward-right
			else if((gAttitudeSensors.aRoll_rad>0.09) && (gAttitudeSensors.aPitch_rad<-0.09))
			{
				mHleds_Toggle(kMaskHled3);

				mHleds_Write(kMaskHled0, kHledOn);
				mHleds_Write(kMaskHled1, kHledOn);
				mHleds_Write(kMaskHled2, kHledOn);

			}

			//Backward-left
			else if((gAttitudeSensors.aRoll_rad<-0.09) && (gAttitudeSensors.aPitch_rad>0.09))
			{
				mHleds_Toggle(kMaskHled1);

				mHleds_Write(kMaskHled0, kHledOn);
				mHleds_Write(kMaskHled2, kHledOn);
				mHleds_Write(kMaskHled3, kHledOn);

			}

			//Backward-right
			else if((gAttitudeSensors.aRoll_rad>0.09) && (gAttitudeSensors.aPitch_rad>0.09))
			{
				mHleds_Toggle(kMaskHled0);

				mHleds_Write(kMaskHled1, kHledOn);
				mHleds_Write(kMaskHled2, kHledOn);
				mHleds_Write(kMaskHled3, kHledOn);

			}

			//Forward
			else if(gAttitudeSensors.aPitch_rad<-0.09)
			{
				mHleds_Toggle(kMaskHled2);
				mHleds_Toggle(kMaskHled3);

				mHleds_Write(kMaskHled0, kHledOn);
				mHleds_Write(kMaskHled1, kHledOn);
			}

			//Backward
			else if(gAttitudeSensors.aPitch_rad>0.09)
			{
				mHleds_Toggle(kMaskHled0);
				mHleds_Toggle(kMaskHled1);

				mHleds_Write(kMaskHled2, kHledOn);
				mHleds_Write(kMaskHled3, kHledOn);
			}

			//Left
			else if(gAttitudeSensors.aRoll_rad<-0.09)
			{
				mHleds_Toggle(kMaskHled1);
				mHleds_Toggle(kMaskHled2);

				mHleds_Write(kMaskHled0, kHledOn);
				mHleds_Write(kMaskHled3, kHledOn);
			}

			//Right
			else if(gAttitudeSensors.aRoll_rad>0.09)
			{
				mHleds_Toggle(kMaskHled0);
				mHleds_Toggle(kMaskHled3);

				mHleds_Write(kMaskHled1, kHledOn);
				mHleds_Write(kMaskHled2, kHledOn);
			}

			else
			{
				mHleds_AllOn();
			}


		}

		//Battery is low, blink all leds to indicate.
		else
		{
			mHleds_AllToggle();
		}

	}
}
