/*
 * mReceiver.c
 *
 *  Created on: 4 ao�t 2015
 *      Author: valentin.py
 */


#include "mReceiver.h"

//------------------------------------------------------------
// Setup receiver
//------------------------------------------------------------
void mReceiver_Setup()
{
	iFtm_Config();
}

//------------------------------------------------------------
// Get all channels
// *channelValue is a pointer on an array of 8 UInt16 that will contain the value of 8 channels (0-1000)
//------------------------------------------------------------
void mReceiver_GetAllChannels(UInt16 *channelValue)
{
	*(channelValue+0) = iFtm_ReadPwm(kReceiverChannel0);
	*(channelValue+1) = iFtm_ReadPwm(kReceiverChannel1);
	*(channelValue+2) = iFtm_ReadPwm(kReceiverChannel2);
	*(channelValue+3) = iFtm_ReadPwm(kReceiverChannel3);

	*(channelValue+4) = iFtm_ReadPwm(kReceiverChannel4);
	*(channelValue+5) = iFtm_ReadPwm(kReceiverChannel5);
	*(channelValue+6) = iFtm_ReadPwm(kReceiverChannel6);
	*(channelValue+7) = iFtm_ReadPwm(kReceiverChannel7);
}

//------------------------------------------------------------
// Get a channel
// aChannel: which channel
// Return: value of the channel, between 0 and 1000
//------------------------------------------------------------
UInt16 mReceiver_GetChannel(ReceiverEnum aChannel)
{
	UInt16 aVal = 0;

	switch(aChannel)
	{
	case kReceiverChannel0:
		aVal = iFtm_ReadPwm(kReceiverChannel0);
		break;

	case kReceiverChannel1:
		aVal = iFtm_ReadPwm(kReceiverChannel1);
		break;

	case kReceiverChannel2:
		aVal = iFtm_ReadPwm(kReceiverChannel2);
		break;

	case kReceiverChannel3:
		aVal = iFtm_ReadPwm(kReceiverChannel3);
		break;

	case kReceiverChannel4:
		aVal = iFtm_ReadPwm(kReceiverChannel4);
		break;

	case kReceiverChannel5:
		aVal = iFtm_ReadPwm(kReceiverChannel5);
		break;

	case kReceiverChannel6:
		aVal = iFtm_ReadPwm(kReceiverChannel6);
		break;

	case kReceiverChannel7:
		aVal = iFtm_ReadPwm(kReceiverChannel7);
		break;

	default:
		aVal=0;
		break;
	}
	return aVal;
}
