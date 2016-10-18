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

#include "misc/derivative.h"
#include "misc/def.h"

#include "modules/mCpu.h"
#include "modules/mLeds.h"
#include "modules/mDelay.h"
#include "modules/mGpio.h"
#include "modules/mSwitches.h"

#include "tasks/gAltitudeSensors.h"
#include "tasks/gAttitudeSensors.h"
#include "tasks/gFlightCompute.h"
#include "tasks/gLight.h"
#include "tasks/gMonitoring.h"
#include "tasks/gMotors.h"
#include "tasks/gReceiver.h"
#include "tasks/gMiscSensors.h"

int main(void)
{
	//Non specific modules initialization
	mCpu_Setup();
	mDelay_Setup();
	mLeds_Setup();
	mGpio_Setup();
	mSwitches_Setup();

	//Tasks initialization
	gAltitudeSensors_Setup();
	gAttitudeSensors_Setup();
	gFlightCompute_Setup();
	gLight_Setup();
	gMonitoring_Setup();
	gReceiver_Setup();
	gMotors_Setup();
	gMiscSensors_Setup();

	//Wait 1second after setup
	UInt16 aDelayBoot = mDelay_GetDelay(kPit0, 1000);
	while(mDelay_IsDelayDone(kPit0, aDelayBoot)==false);
	mDelay_DelayRelease(kPit0, aDelayBoot);

	//Indicate that programm is ready.
	mLeds_AllOn();

	//Get delay for main loop
	UInt16 aDelayMainLoop = mDelay_GetDelay(kPit0, 5);

	//Main loop
	while(1)
	{
		while(mDelay_IsDelayDone(kPit0, aDelayMainLoop)==false);
		mDelay_ReStart(kPit0, aDelayMainLoop, 5);

		//Get inputs
		gAttitudeSensors_Run();
		gReceiver_Run();
		gAltitudeSensors_Run();
		gMiscSensors_Run();

		//Compute
		gFlightCompute_Run();

		//Export outputs
		gMotors_Run();
		gLight_Run();

		//Monitoring
		gMonitoring_Run();


		//Measure time with logic
		//mGpio_AllToggle();


	}

	//Never happens (infinite loop above)
	return 0;
}
