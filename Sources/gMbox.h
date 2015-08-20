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
	UInt16 aSonarValues[6];
	UInt16 aBaroValue;
} gAltitudeSensorsStruct;
extern gAltitudeSensorsStruct gAltitudeSensors;

//-----------------------------------------------------------------------------
// gAttitudeSensors mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	float aHeading_rad;
	float aPitch_rad;
	float aRoll_rad;

	Int16 aHeading_mrad;
	Int16 aPitch_mrad;
	Int16 aRoll_mrad;

	UInt16 aTimeStamp;

} gAttitudeSensorsStruct;
extern gAttitudeSensorsStruct gAttitudeSensors;


// State enum
typedef enum
{
	kArmed,
	kDisarmed
}StateEnum;

//-----------------------------------------------------------------------------
// gFlightCompute mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	StateEnum aState;

	UInt16 aMotorsOuptut[8];
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
	Int16 aDelay;
	char aDataString[kMonitoringStringLength];

} gMonitoringStruct;
extern gMonitoringStruct gMonitoring;

//-----------------------------------------------------------------------------
// gMotors mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	UInt16 aMotorsValues[8];
	UInt16 aServosValues[8];
} gMotorsStruct;
extern gMotorsStruct gMotors;

//-----------------------------------------------------------------------------
// gReceiver mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	UInt16 aChannels[8];
} gReceiverStruct;
extern gReceiverStruct gReceiver ;

//-----------------------------------------------------------------------------
// gMiscSensors mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	UInt16 aBatteryVoltage_mV;
	UInt16 aBatteryCurrent_A;
	UInt16 aBatteryUsedCapacity_mAh;
} gMiscSensorsStruct;
extern gMiscSensorsStruct gMiscSensors ;


#endif /* SOURCES_GMBOX_H_ */
