/*
 * gMbox.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_GMBOX_H_
#define SOURCES_GMBOX_H_

#include "misc/PID.h"
#include "misc/def.h"
#include "userDefined.h"



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

	float aHeadingRate_rads;
	float aPitchRate_rads;
	float aRollRate_rads;

	UInt16 aTimeStamp;
} gAttitudeSensorsStruct;
extern gAttitudeSensorsStruct gAttitudeSensors;


// State enum
typedef enum
{
	kDisarmed,
	kArmed
}StateEnum;

//-----------------------------------------------------------------------------
// gFlightCompute mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	StateEnum aState;

	float aPitch_rad_offset;
	float aRoll_rad_offset;

	PIDdata aPIDRate [3];
	PIDdata aPIDAngle [3];
	UInt16 aMotorsOutput[8];
	float aError;

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
typedef enum
{
	kTerminalDisarm,
	kTerminalArm,
	kTerminalCalibrate,

} TerminalActionEnum;

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
	UInt16 aMotorsValuesIn_0[8];
	UInt16 aMotorsValuesIn_1[8];
	UInt16 aMotorsValuesIn_2[8];
	UInt16 aMotorsValuesOut[8];


	UInt16 aServosValues[4];
} gMotorsStruct;
extern gMotorsStruct gMotors;

//-----------------------------------------------------------------------------
// gReceiver mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	UInt16 aChannels[8];
	float aChannels_rad[8];
	float aChannels_radS[8];

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
