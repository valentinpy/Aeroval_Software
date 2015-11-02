/*
 * gReceiver.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */


#include "gReceiver.h"

//-----------------------------------
// Receiver initialisation
//-----------------------------------
void gReceiver_Setup()
{
	mReceiver_Setup();

	//Initialize variables
	UInt8 i;
	for(i=0; i<8; i++)
	{
		gReceiver.aChannels[i] = 0;
		gReceiver.aChannels_urad[i]=0;
	}

}

//-----------------------------------
// Read PWM from receiver
//-----------------------------------
void gReceiver_Run()
{
	//Get all channels
	mReceiver_GetAllChannels(gReceiver.aChannels);

	//Constrain and map all channels between 0 and 1000
	// My receiver transmit values between 110 and 910, that's why there is a factor 1.25
	// TODO calibration using monitoring
	UInt16 i=0;
	for(i=0; i<8; i++)
	{
		Int16 aTmp = (1.25 * (gReceiver.aChannels[i])) -135;
		if(aTmp>1000)
		{
			gReceiver.aChannels[i] = 1000;
			gReceiver.aChannels_urad[i] = kReceiverMaxAngle_urad;
		}
		else if(aTmp<0)
		{
			gReceiver.aChannels[i] = 0;
			gReceiver.aChannels_urad[i] = -kReceiverMaxAngle_urad;
		}
		else
		{
			gReceiver.aChannels[i] = (UInt16)aTmp;

			//-500 => half range of time => center between +kReceiverMaxAngle and -kReceiverMaxAngle
			gReceiver.aChannels_urad[i] = (aTmp-500) * kReceiverUsTomrad;

		}
	}
}
