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
#ifndef SOURCES_MRECEIVER_H_
#define SOURCES_MRECEIVER_H_

#include "../interfaces/iFtm.h"
#include "../misc/def.h"

// Servos Enum
typedef enum
{
	kReceiverChannel0,
	kReceiverChannel1,
	kReceiverChannel2,
	kReceiverChannel3,
	kReceiverChannel4,
	kReceiverChannel5,
	kReceiverChannel6,
	kReceiverChannel7,
}ReceiverEnum;

#define kReceiverThrottle 	kReceiverChannel7
#define kReceiverRoll 		kReceiverChannel6
#define kReceiverPitch 		kReceiverChannel4
#define kReceiverYaw 		kReceiverChannel5

#define kReceiverGear 		kReceiverChannel0
#define kReceiverAux1 		kReceiverChannel2
#define kReceiverAux2 		kReceiverChannel3

//------------------------------------------------------------
// Setup receiver
//------------------------------------------------------------
void mReceiver_Setup();

//------------------------------------------------------------
// Get all channels
// *channelValue is a pointer on an array of 8 UInt16 that will contain the value of 8 channels (0-1000)
//------------------------------------------------------------
void mReceiver_GetAllChannels(UInt16 *channelValue);

//------------------------------------------------------------
// Get a channel
// aChannel: which channel
// Return: value of the channel, between 0 and 1000
//------------------------------------------------------------
UInt16 mReceiver_GetChannel(ReceiverEnum aChannel);

#endif /* SOURCES_MRECEIVER_H_ */
