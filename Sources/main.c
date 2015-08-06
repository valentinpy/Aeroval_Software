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

#include "derivative.h"

#include "def.h"

#include "mCpu.h"
#include "mLeds.h"
#include "mHleds.h"
#include "mDelay.h"
#include "mSwitches.h"
#include "mAd.h"
#include "mRS232.h"
#include "iFtm.h"
#include "mMotors.h"
#include "mServos.h"
#include "mReceiver.h"

int main(void)
{
	//Setups

	mCpu_Setup();
	mLeds_Setup();
	mHleds_Setup();
	mDelay_Setup();
	mSwitches_Setup();
	mAd_Setup();
	mRs232_Setup();
	mServos_Setup();
	mMotors_Setup();
	mReceiver_Setup();

	//wait after setup
	mLeds_AllOff();
	UInt16 aDelayBoot = mDelay_GetDelay(kPit0, 2000);
	while(mDelay_IsDelayDone(kPit0, aDelayBoot)==false);
	mLeds_AllOn();


	float value = 0;
	UInt8 tmp0;
	UInt8 tmp3;
	UInt8 tmp4;
	UInt16 getchannel = 0;
	UInt16 motorsend=0;

	UInt16 aDelay = mDelay_GetDelay(kPit0, 250);

	//Main loop
	while(1)
	{
		//Get some infos
		value = mAd_readBattVoltage();
		value = mAd_readCurrent();
		value = mAd_readSonars(kSonar0);
		value = mAd_readSonars(kSonar1);
		value = mAd_readSonars(kSonar2);
		value = mAd_readSonars(kSonar3);
		value = mAd_readSonars(kSonar4);
		value = mAd_readSonars(kSonar5);

		getchannel=mReceiver_GetChannel(kReceiverChannel0);
		motorsend = getchannel-1000;
		mMotors_SetAllMotors(motorsend);

		//serial communication
		if(tmp0!=0)
		{
			mRs232_WriteChar(kUart3USB, tmp0);
		}


		//Is alive (leds toggle + uart)
		if(mDelay_IsDelayDone(kPit0, aDelay))
		{
			mRs232_WriteString(kUart3USB, "\r\nIs alive");

			mDelay_ReStart(kPit0, aDelay, 250);
			mLeds_AllToggle();


			//send to motors
			//			if(motorsend<1000)
			//			{
			//				motorsend+=25;
			//			}
			//			else
			//			{
			//				motorsend=0;
			//			}
		}

	}
	return 0;
}
