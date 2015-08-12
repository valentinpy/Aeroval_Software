/*
 * gMbox.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_GMBOX_H_
#define SOURCES_GMBOX_H_

#include "misc/def.h"

//-----------------------------------------------------------------------------
// gAltitudeSensors mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	//TODO implement
} gAltitudeSensorsStruct;
extern gAltitudeSensorsStruct gAltitudeSensors;

//-----------------------------------------------------------------------------
// gAttitudeSensors mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	float aHeading;
	float aPitch;
	float aRoll;
	UInt16 aTimeStamp;
} gAttitudeSensorsStruct;
extern gAttitudeSensorsStruct gAttitudeSensors;

//-----------------------------------------------------------------------------
// gFlightCompute mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	//TODO implement
} gFlightComputeStruct;
extern gFlightComputeStruct gFlightCompute;

//-----------------------------------------------------------------------------
// gLight mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	Int16 aDelay2Hz;
	Int16 aDelay5Hz;
} gLightStruct;
extern gLightStruct gLight;

//-----------------------------------------------------------------------------
// gMonitoring mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	Int16 aDelay5Hz;
	char aDataString[kMonitoringStringLength];

} gMonitoringStruct;
extern gMonitoringStruct gMonitoring;

//-----------------------------------------------------------------------------
// gMotors mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	//TODO implement
} gMotorsStruct;
extern gMotorsStruct gMotors;

//-----------------------------------------------------------------------------
// gReceiver mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	//TODO implement
} gReceiverStruct;
extern gReceiverStruct gReceiver ;


#endif /* SOURCES_GMBOX_H_ */
