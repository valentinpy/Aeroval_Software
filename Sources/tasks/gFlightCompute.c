/*
 * gFlightCompute.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */


#include "gFlightCompute.h"

//-----------------------------------
// Static functions
// TODO comment
//-----------------------------------
static void gFlightCompute_PID();
static void gFlightCompute_MotorMix(Int16 aThrottle, Int16 aPIDPitchOutput, Int16 aPIDRollOutput, Int16 aPIDYawOutput);
//static void gFlightCompute_ProcessUserAction()

//-----------------------------------
// Flight controller (regulation,..) initialization
//-----------------------------------
void gFlightCompute_Setup()
{
	//TODO implement (init state,...)

	//Init attitude offset
	//offset to apply to attitude
	gFlightCompute.aPitch_mrad_offset		= 0;
	gFlightCompute.aRoll_mrad_offset		= 0;

	//Init state of motors
	gFlightCompute.aState = kDisarmed;

	//Init motors output
	UInt8 i = 0;
	for (i=0; i<8; i++)
	{
		gFlightCompute.aMotorsOutput[i] = 0;
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

	//Check controls and state to calibrate the attitude sensor
	if(
			(gReceiver.aChannels[kReceiverThrottle] < kReceiverMIN) &&
			(gReceiver.aChannels[kReceiverYaw] < kReceiverMIN) &&
			(gReceiver.aChannels[kReceiverPitch] < kReceiverMIN) &&
			(gReceiver.aChannels[kReceiverRoll] > kReceiverMAX) &&
			(gFlightCompute.aState == kDisarmed)
	)
	{
		gFlightCompute.aPitch_mrad_offset 	-= gAttitudeSensors.aPitch_mrad;
		gFlightCompute.aRoll_mrad_offset	-= gAttitudeSensors.aRoll_mrad;
	}


	//Test
	gFlightCompute.aMotorsOutput[0] = MOTOR_IDLE_VALUE;
	gFlightCompute.aMotorsOutput[1] = MOTOR_IDLE_VALUE;
	gFlightCompute.aMotorsOutput[2] = MOTOR_IDLE_VALUE;
	gFlightCompute.aMotorsOutput[3] = MOTOR_IDLE_VALUE;



	//Call regulation for roll axis


	//Call regulation for pitch axis

	//Call regulation for yaw axis

	//Call motor mix

}

static void gFlightCompute_PID()
{

}

static void gFlightCompute_MotorMix(Int16 aThrottle, Int16 aPIDPitchOutput, Int16 aPIDRollOutput, Int16 aPIDYawOutput)
{
	//4 motors, X configuration
	// Motor 0: Front right, counter-clockwise
	// Motor 1: Rear right, clockwise
	// Motor 2: Rear left, counter-clockwise
	// Motor 3: Front left, clockwise

	Int16 aMotorsOutput[NUMBER_OF_MOTORS];

#if defined(MOTORMIX_X4)

	//Calculate outputs
	aMotorsOutput[0] = aThrottle + aPIDPitchOutput + aPIDRollOutput + aPIDYawOutput;
	aMotorsOutput[1] = aThrottle - aPIDPitchOutput + aPIDRollOutput - aPIDYawOutput;
	aMotorsOutput[2] = aThrottle - aPIDPitchOutput - aPIDRollOutput + aPIDYawOutput;
	aMotorsOutput[3] = aThrottle + aPIDPitchOutput - aPIDRollOutput - aPIDYawOutput;

#else
#error "Bad motor mix configuration"
#endif

	//Constrain and export to mailbox
	for (int i=0; i<NUMBER_OF_MOTORS; i++)
	{
		if(aMotorsOutput[i]<MOTOR_IDLE_VALUE)
		{
			gFlightCompute.aMotorsOutput[i] = MOTOR_IDLE_VALUE;
		}
		else if (aMotorsOutput[i]>MOTOR_MAX_VALUE)
		{
			gFlightCompute.aMotorsOutput[i] = MOTOR_MAX_VALUE;
		}
		else
		{
			gFlightCompute.aMotorsOutput[i] = aMotorsOutput[i];
		}
	}
}
