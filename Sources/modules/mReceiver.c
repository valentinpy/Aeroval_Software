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
