/*
 * mReceiver.h
 *
 *  Created on: 4 ao�t 2015
 *      Author: valentin.py
 */

#ifndef SOURCES_MRECEIVER_H_
#define SOURCES_MRECEIVER_H_

#include "iFtm.h"
#include "def.h"

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
