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

#ifndef SOURCES_GMBOX_H_
#define SOURCES_GMBOX_H_

#include "misc/PID.h"
#include "misc/def.h"
#include "userDefined.h"
#include "lib/Fusion/Fusion.h"


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
	//Values by sensor
	gIMUSensorStruct aSensorValuesEM7180;
	gIMUSensorStruct aSensorValuesMPU6000;

	//Quaternions
	FusionAhrs aEM7180FusionAhrs;
	FusionQuaternion aQuatMadgwickEM7180;

	//Global values, which are fusioned using sensors choosen by user
	float aHeading_rad;
	float aPitch_rad;
	float aRoll_rad;

	float aHeadingRate_rads;
	float aPitchRate_rads;
	float aRollRate_rads;

	//TODO Warn: select scale/normalize
	float aAccel_X;
	float aAccel_Y;
	float aAccel_Z;

	//TODO Warn: read time and copy it here
	UInt16 aDeltaTimeEuler_us;
	UInt16 aDeltaTimeGyro_us;

} gAttitudeSensorsStruct;
extern gAttitudeSensorsStruct gAttitudeSensors;


// State enum
typedef enum
{
	kDisarmed,
	kArmed
}StateEnum;

// Flight Mode enum
typedef enum
{
	kRate,
	kAngle
}FlightModeEnum;

//-----------------------------------------------------------------------------
// gFlightCompute mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	//Armed/Disarmed
	StateEnum aState;

	FlightModeEnum aFLightMode;

	//Orientation offsets to be transmitted to gAttitude
	float aPitch_rad_offset;
	float aRoll_rad_offset;

	//Delay for outter PID regulation
	Int16 aDelayAnglePID;

	//Desired rate (angular speed)
	//If rate/angle mode: output of first PID
	//If accro mode: output of receiver
	float aDesiredRate[3];

	//PID structures
	PIDdata aPIDRate [3];
	PIDdata aPIDAngle [3];

	//Output of the flightcomputer, to transmit to motor control
	UInt16 aMotorsOutput[8];

	float aError; //DEBUG

} gFlightComputeStruct;
extern gFlightComputeStruct gFlightCompute;

//-----------------------------------------------------------------------------
// gLight mailbox
//-----------------------------------------------------------------------------
typedef struct
{
	Int16 aDelayLeds;
	Int16 aDelayHLeds;
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
	char aReceived[50];
	UInt8 aReceivedIdx;

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
