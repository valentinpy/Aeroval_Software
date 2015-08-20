/*
 * gFlightCompute.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */


#include "gFlightCompute.h"

//-----------------------------------
// Flight controller (regulation,..) initialization
//-----------------------------------
void gFlightCompute_Setup()
{
	//TODO implement (init state,...)

	//Init state of motors
	gFlightCompute.aState = kDisarmed;

	//Init motors output
	UInt8 i = 0;
	for (i=0; i<8; i++)
	{
		gFlightCompute.aMotorsOuptut[i] = 0;
	}
}

//-----------------------------------
// Run the flight controller
//-----------------------------------
void gFlightCompute_Run()
{
	//Check controls to arm/disarm the motors
	if((gReceiver.aChannels[kReceiverThrottle] < kReceiverMIN) && (gReceiver.aChannels[kReceiverYaw] < kReceiverMIN))
	{
		gFlightCompute.aState = kDisarmed;
	}
	else if((gReceiver.aChannels[kReceiverThrottle] < kReceiverMIN) && (gReceiver.aChannels[kReceiverYaw] > kReceiverMAX))
	{
		gFlightCompute.aState = kArmed;
	}

	//TESTS
	gFlightCompute.aMotorsOuptut[0] = gReceiver.aChannels[0];
	gFlightCompute.aMotorsOuptut[1] = gReceiver.aChannels[1];
	gFlightCompute.aMotorsOuptut[2] = gReceiver.aChannels[2];
	gFlightCompute.aMotorsOuptut[3] = gReceiver.aChannels[3];

	gFlightCompute.aMotorsOuptut[4] = gReceiver.aChannels[4];
	gFlightCompute.aMotorsOuptut[5] = gReceiver.aChannels[5];
	gFlightCompute.aMotorsOuptut[6] = gReceiver.aChannels[6];
	gFlightCompute.aMotorsOuptut[7] = gReceiver.aChannels[7];


}
