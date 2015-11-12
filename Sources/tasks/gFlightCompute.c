/*
 * gFlightCompute.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */


#include "gFlightCompute.h"
#include "../modules/mGpio.h"
#include "../misc/PID.h"
//-----------------------------------
// Static functions
// TODO comment
//-----------------------------------
static void gFlightCompute_MotorMix(Int16 aThrottle, Int16 aPIDPitchOutput, Int16 aPIDRollOutput, Int16 aPIDYawOutput, Int16* aOutput);
static void gFlightCompute_ConstrainSendMotorsValues(Int16* aOutput);


//static void gFlightCompute_ProcessUserAction()

//-----------------------------------
// Flight controller (regulation,..) initialization
//-----------------------------------
void gFlightCompute_Setup()
{
	//TODO implement (init state,...)

	//Init attitude offset
	//offset to apply to attitude
	gFlightCompute.aPitch_rad_offset	= 0.0;
	gFlightCompute.aRoll_rad_offset		= 0.0;

	//Init state of motors
	gFlightCompute.aState = kDisarmed;

	//Init motors output
	UInt8 i = 0;
	for (i=0; i<8; i++)
	{
		gFlightCompute.aMotorsOutput[i] = 0;
	}


	//Init PIDs
	misc_ResetPID(gFlightCompute.aPIDRate);
	misc_ResetPID(gFlightCompute.aPIDAngle);


	//Init PIDs parameters
	//Rate
	gFlightCompute.aPIDRate[kPIDRoll].aKp = kPIDRollRate_Kp;
	gFlightCompute.aPIDRate[kPIDRoll].aKd = kPIDRollRate_Kd;
	gFlightCompute.aPIDRate[kPIDRoll].aKi = kPIDRollRate_Ki;
	gFlightCompute.aPIDRate[kPIDRoll].aWindupGuard = kWindupGuardRate;

	gFlightCompute.aPIDRate[kPIDPitch].aKp = kPIDPitchRate_Kp;
	gFlightCompute.aPIDRate[kPIDPitch].aKd = kPIDPitchRate_Kd;
	gFlightCompute.aPIDRate[kPIDPitch].aKi = kPIDPitchRate_Ki;
	gFlightCompute.aPIDRate[kPIDRoll].aWindupGuard = kWindupGuardRate;

	gFlightCompute.aPIDRate[kPIDYaw].aKp = kPIDYawRate_Kp;
	gFlightCompute.aPIDRate[kPIDYaw].aKd = kPIDYawRate_Kd;
	gFlightCompute.aPIDRate[kPIDYaw].aKi = kPIDYawRate_Ki;
	gFlightCompute.aPIDRate[kPIDYaw].aWindupGuard = kWindupGuardRate;

	//Angle
	gFlightCompute.aPIDAngle[kPIDRoll].aKp = kPIDRollAngle_Kp;
	gFlightCompute.aPIDAngle[kPIDRoll].aKd = kPIDRollAngle_Kd;
	gFlightCompute.aPIDAngle[kPIDRoll].aKi = kPIDRollAngle_Ki;
	gFlightCompute.aPIDAngle[kPIDRoll].aWindupGuard = kWindupGuardAngle;

	gFlightCompute.aPIDAngle[kPIDPitch].aKp = kPIDPitchAngle_Kp;
	gFlightCompute.aPIDAngle[kPIDPitch].aKd = kPIDPitchAngle_Kd;
	gFlightCompute.aPIDAngle[kPIDPitch].aKi = kPIDPitchAngle_Ki;
	gFlightCompute.aPIDAngle[kPIDRoll].aWindupGuard = kWindupGuardAngle;

	gFlightCompute.aPIDAngle[kPIDYaw].aKp = kPIDYawAngle_Kp;
	gFlightCompute.aPIDAngle[kPIDYaw].aKd = kPIDYawAngle_Kd;
	gFlightCompute.aPIDAngle[kPIDYaw].aKi = kPIDYawAngle_Ki;
	gFlightCompute.aPIDAngle[kPIDYaw].aWindupGuard = kWindupGuardAngle;
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
		misc_ResetPID(gFlightCompute.aPIDRate);
		misc_ResetPID(gFlightCompute.aPIDAngle);
		gFlightCompute.aState = kArmed;
	}

	//Check controls and state to calibrate the attitude sensor
	if(
			(gReceiver.aChannels[kReceiverThrottle] < kReceiverMIN) &&
			(gReceiver.aChannels[kReceiverYaw] < kReceiverMIN) &&
			(gReceiver.aChannels[kReceiverPitch] > kReceiverMAX) &&
			(gReceiver.aChannels[kReceiverRoll] > kReceiverMAX) &&
			(gFlightCompute.aState == kDisarmed)
	)
	{
		gFlightCompute.aPitch_rad_offset -= gAttitudeSensors.aPitch_rad;
		gFlightCompute.aRoll_rad_offset	-= gAttitudeSensors.aRoll_rad;
	}

	Int16 aToMotors[NUMBER_OF_MOTORS];
	float aThrottle = (float) gReceiver.aChannels[kReceiverThrottle];

	float aPIDRollRateOutput;
	float aPIDPitchRateOutput;
	float aPIDYawRateOutput;

	//Check if IDLE
	if(aThrottle < kReceiverIDLE)
	{
		aThrottle = MOTOR_IDLE_VALUE;
		aPIDRollRateOutput = 0;
		aPIDPitchRateOutput = 0;
		aPIDYawRateOutput = 0;
		misc_ResetPID(gFlightCompute.aPIDRate);
		misc_ResetPID(gFlightCompute.aPIDAngle);
	}
	else
	{
		//Get time
		UInt16 aTime = sTicker100Us[0];

		//Call regulation for roll axis rate
		misc_PID(&aPIDRollRateOutput, &(gFlightCompute.aPIDRate[kPIDRoll]), gReceiver.aChannels_radS[kReceiverRoll], gAttitudeSensors.aRollRate_rads, aTime);

		//Call regulation for pitch axis rate
		misc_PID(&aPIDPitchRateOutput, &(gFlightCompute.aPIDRate[kPIDPitch]), gReceiver.aChannels_radS[kReceiverPitch], gAttitudeSensors.aPitchRate_rads, aTime);

		//Call regulation for yaw axis
		//TODO implement
		aPIDYawRateOutput = gReceiver.aChannels_rad[kReceiverYaw]/0.002;
	}

	//Call motor mix
	gFlightCompute_MotorMix(aThrottle, aPIDPitchRateOutput, aPIDRollRateOutput, aPIDYawRateOutput, aToMotors);
	//Constrain and send to motors
	gFlightCompute_ConstrainSendMotorsValues(aToMotors);
}



static void gFlightCompute_MotorMix(Int16 aThrottle, Int16 aPIDPitchOutput, Int16 aPIDRollOutput, Int16 aPIDYawOutput, Int16* aOutput)
{
	//4 motors, X configuration
	// Motor 0: Front right, counter-clockwise
	// Motor 1: Rear right, clockwise
	// Motor 2: Rear left, counter-clockwise
	// Motor 3: Front left, clockwise
#if defined(MOTORMIX_X4)
	//Calculate outputs
	aOutput[0] = aThrottle + aPIDPitchOutput - aPIDRollOutput + aPIDYawOutput;
	aOutput[1] = aThrottle - aPIDPitchOutput - aPIDRollOutput - aPIDYawOutput;
	aOutput[2] = aThrottle - aPIDPitchOutput + aPIDRollOutput + aPIDYawOutput;
	aOutput[3] = aThrottle + aPIDPitchOutput + aPIDRollOutput - aPIDYawOutput;
#else
#error "Bad motor mix configuration"
#endif
}

static void gFlightCompute_ConstrainSendMotorsValues(Int16* aOutput)
{
	//Constrain and export to mailbox
	for (int i=0; i<NUMBER_OF_MOTORS; i++)
	{
		if(aOutput[i]<MOTOR_IDLE_VALUE)
		{
			gFlightCompute.aMotorsOutput[i] = MOTOR_IDLE_VALUE;
		}
		else if (aOutput[i]>MOTOR_MAX_VALUE)
		{
			gFlightCompute.aMotorsOutput[i] = MOTOR_MAX_VALUE;
		}
		else
		{
			gFlightCompute.aMotorsOutput[i] = aOutput[i];
		}
	}
}
