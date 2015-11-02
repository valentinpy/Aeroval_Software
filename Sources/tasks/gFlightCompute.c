/*
 * gFlightCompute.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */


#include "gFlightCompute.h"
#include "../modules/mGpio.h"
//-----------------------------------
// Static functions
// TODO comment
//-----------------------------------
static void gFlightCompute_ResetPID(PIDdata* sPID);
static void gFlightCompute_PID(float* aOutput, PIDdata* aPIDstruct, float aSetPoint, float aMeasured, UInt16 aTime);
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


	//Init PID
	gFlightCompute_ResetPID(sPID);

	//Init PID parametes
	sPID[kPIDRoll].aKp = kPIDRoll_Kp;
	sPID[kPIDRoll].aKd = kPIDRoll_Kd;
	sPID[kPIDRoll].aKi = kPIDRoll_Ki;

	sPID[kPIDPitch].aKp = kPIDPitch_Kp;
	sPID[kPIDPitch].aKd = kPIDPitch_Kd;
	sPID[kPIDPitch].aKi = kPIDPitch_Ki;

	sPID[kPIDYaw].aKp = kPIDYaw_Kp;
	sPID[kPIDYaw].aKd = kPIDYaw_Kd;
	sPID[kPIDYaw].aKi = kPIDYaw_Ki;
}

//-----------------------------------
// Run the flight controller
//-----------------------------------
void gFlightCompute_Run()
{
	mGpio_AllOn();

	//Check controls to arm/disarm the motors
	if((gReceiver.aChannels[kReceiverThrottle] < kReceiverMIN) && (gReceiver.aChannels[kReceiverYaw] < kReceiverMIN))
	{
		gFlightCompute.aState = kDisarmed;
	}
	else if((gReceiver.aChannels[kReceiverThrottle] < kReceiverMIN) && (gReceiver.aChannels[kReceiverYaw] > kReceiverMAX))
	{
		gFlightCompute_ResetPID(sPID);
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
		gFlightCompute.aPitch_rad_offset 	-= gAttitudeSensors.aPitch_rad;
		gFlightCompute.aRoll_rad_offset	-= gAttitudeSensors.aRoll_rad;
	}

	Int16 aToMotors[NUMBER_OF_MOTORS];
	float aThrottle = (float) gReceiver.aChannels[kReceiverThrottle];

	float aPIDRollOutput;
	float aPIDPitchOutput;
	float aPIDYawOutput;

	//Check if IDLE
	if(aThrottle < kReceiverIDLE)
	{
		aThrottle = MOTOR_IDLE_VALUE;
		aPIDRollOutput = 0;
		aPIDPitchOutput = 0;
		aPIDYawOutput = 0;
		gFlightCompute_ResetPID(sPID);
	}
	else
	{
		//Get time
		UInt16 aTime = sTicker100Us[0];

		//Call regulation for roll axis
		gFlightCompute_PID(&aPIDRollOutput, &sPID[kPIDRoll], gReceiver.aChannels_rad[kReceiverRoll], gAttitudeSensors.aRoll_rad, aTime);

		//Call regulation for pitch axis
		gFlightCompute_PID(&aPIDPitchOutput, &sPID[kPIDPitch], gReceiver.aChannels_rad[kReceiverPitch], gAttitudeSensors.aPitch_rad, aTime);

		//Call regulation for yaw axis
		//TODO implement
		aPIDYawOutput = gReceiver.aChannels_rad[kReceiverYaw]/0.002;
	}

	//Call motor mix
	gFlightCompute_MotorMix(aThrottle, aPIDPitchOutput, aPIDRollOutput, aPIDYawOutput, aToMotors);
	//Constrain and send to motors
	gFlightCompute_ConstrainSendMotorsValues(aToMotors);

	mGpio_AllOff();
}


static void gFlightCompute_ResetPID(PIDdata* aPID)
{
	UInt8 i;
	for(i=0; i<3; i++)
	{
		aPID[i].aIntegral=0;
		aPID[i].aPreviousError=0;
		aPID[i].aPreviousTime = sTicker100Us[0];
	}
}

static void gFlightCompute_PID(float* aOutput, PIDdata* aPIDstruct, float aTarget, float aMeasured, UInt16 aTime)
{
	float aDeltaTime;

	float aError, aProportional, aDerivative;

	aDeltaTime = (float)(aTime - aPIDstruct->aPreviousTime);

	//Constrain time if abnormal
	if (aDeltaTime <1.0)
	{
		aDeltaTime = 1.0;
	}
	else if (aDeltaTime >1000.0)
	{
		aDeltaTime = 1000.0; //100ms ?
	}

	//Constrain integral
	if(aPIDstruct->aIntegral > kWindupGuard)
	{
		aPIDstruct->aIntegral = kWindupGuard;
	}
	else if(aPIDstruct->aIntegral < kWindupGuard)
	{
		aPIDstruct->aIntegral = -kWindupGuard;
	}

	//Compute error
	aError = (aTarget - aMeasured);

	//Compute separate terms
	aProportional = (aError * aPIDstruct->aKp);
	aPIDstruct->aIntegral += (aError * aPIDstruct->aKi * aDeltaTime);
	aDerivative = ((aError-(aPIDstruct->aPreviousError)) * aPIDstruct->aKd)/aDeltaTime;

	//Compute output
	*aOutput = aProportional + (aPIDstruct->aIntegral) + aDerivative;

	//Sore previous parameters
	aPIDstruct->aPreviousTime = aTime;
	aPIDstruct->aPreviousError= aError;
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
