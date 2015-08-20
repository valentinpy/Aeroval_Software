/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "misc/derivative.h"
#include "misc/def.h"

#include "modules/mCpu.h"
#include "modules/mLeds.h"
#include "modules/mDelay.h"

#include "tasks/gAltitudeSensors.h"
#include "tasks/gAttitudeSensors.h"
#include "tasks/gFlightCompute.h"
#include "tasks/gLight.h"
#include "tasks/gMonitoring.h"
#include "tasks/gMotors.h"
#include "tasks/gReceiver.h"
#include "tasks/gMiscSensors.h"

void main(void)
{
	//Non specific modules initialization
	mCpu_Setup();
	mDelay_Setup();
	mLeds_Setup();

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

	mLeds_AllOn();

	//Main loop
	while(1)
	{
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

	}

	//Never happens (infinite loop above)
	return;
}
