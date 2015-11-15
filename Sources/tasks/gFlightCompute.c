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
static void gFlightCompute_MotorMix(float aThrottle, float aPIDPitchOutput, float aPIDRollOutput, float aPIDYawOutput, float* aOutput);
static void gFlightCompute_ConstrainSendMotorsValues(float* aOutput, float aThrottle);


//static void gFlightCompute_ProcessUserAction()

//-----------------------------------
// Flight controller (regulation,..) initialization
//-----------------------------------
void gFlightCompute_Setup()
{
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

	//Get a delay
	gFlightCompute.aDelayAnglePID = mDelay_GetDelay(kPit0, 10);



	//Init PIDs
	misc_ResetPID(gFlightCompute.aPIDRate);
	misc_ResetPID(gFlightCompute.aPIDAngle);


	//Init PIDs parameters
	//Rate
	gFlightCompute.aPIDRate[kRoll].aKp = kPIDRollRate_Kp;
	gFlightCompute.aPIDRate[kRoll].aKi = kPIDRollRate_Ki;
	gFlightCompute.aPIDRate[kRoll].aKd = kPIDRollRate_Kd;
	gFlightCompute.aPIDRate[kRoll].aWindupGuard = kWindupGuardRate;

	gFlightCompute.aPIDRate[kPitch].aKp = kPIDPitchRate_Kp;
	gFlightCompute.aPIDRate[kPitch].aKi = kPIDPitchRate_Ki;
	gFlightCompute.aPIDRate[kPitch].aKd = kPIDPitchRate_Kd;
	gFlightCompute.aPIDRate[kPitch].aWindupGuard = kWindupGuardRate;

	gFlightCompute.aPIDRate[kYaw].aKp = kPIDYawRate_Kp;
	gFlightCompute.aPIDRate[kYaw].aKi = kPIDYawRate_Ki;
	gFlightCompute.aPIDRate[kYaw].aKd = kPIDYawRate_Kd;
	gFlightCompute.aPIDRate[kYaw].aWindupGuard = kWindupGuardRate;

	//Angle
	gFlightCompute.aPIDAngle[kRoll].aKp = kPIDRollAngle_Kp;
	gFlightCompute.aPIDAngle[kRoll].aKi = kPIDRollAngle_Ki;
	gFlightCompute.aPIDAngle[kRoll].aKd = kPIDRollAngle_Kd;
	gFlightCompute.aPIDAngle[kRoll].aWindupGuard = kWindupGuardAngle;

	gFlightCompute.aPIDAngle[kPitch].aKp = kPIDPitchAngle_Kp;
	gFlightCompute.aPIDAngle[kPitch].aKi = kPIDPitchAngle_Ki;
	gFlightCompute.aPIDAngle[kPitch].aKd = kPIDPitchAngle_Kd;
	gFlightCompute.aPIDAngle[kPitch].aWindupGuard = kWindupGuardAngle;
}

//-----------------------------------
// Run the flight controller
//-----------------------------------
void gFlightCompute_Run()
{
	float aToMotors[NUMBER_OF_MOTORS];
	float aThrottle = (float) gReceiver.aChannels[kReceiverThrottle];

	float aPIDRollRateOutput;
	float aPIDPitchRateOutput;
	float aPIDYawRateOutput;


	//Check controls to arm/disarm the motors
	if((gReceiver.aChannels[kReceiverThrottle] < kReceiverMIN) && (gReceiver.aChannels[kReceiverYaw] < kReceiverMIN))
	{
		gFlightCompute.aState = kDisarmed;
	}
	else if((gReceiver.aChannels[kReceiverThrottle] < kReceiverMIN) && (gReceiver.aChannels[kReceiverYaw] > kReceiverMAX))
	{
		misc_ResetPID(gFlightCompute.aPIDRate);
		misc_ResetPID(gFlightCompute.aPIDAngle);
		/* TODO check should be done to verify all is ok before arming (but wh must be sure we are not in flight while arming)
		 * For exemple, attitude sensor, battery level, GPS fix..
		 * Calibrate gyro, baro,...
		 */

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

	//Check controls to switch betwwen rate and angle mode
	if(gReceiver.aChannels[kReceiverGear]>kReceiverMIDDLE)
	{
		gFlightCompute.aFLightMode = kAngle;
	}
	else
	{
		gFlightCompute.aFLightMode = kRate;
	}

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

		if(gFlightCompute.aFLightMode == kAngle)
		{
			//Angle PID (outter loop) must be executed at a lower frequency than the inner loop
			if(mDelay_IsDelayDone(kPit0, gFlightCompute.aDelayAnglePID)==TRUE)
			{
				//Restart delay
				mDelay_ReStart(kPit0, gFlightCompute.aDelayAnglePID, 2);

				//Call regulation for roll axis rate
				misc_PID(&(gFlightCompute.aDesiredRate[kRoll]), &(gFlightCompute.aPIDAngle[kRoll]), gReceiver.aChannels_rad[kReceiverRoll], gAttitudeSensors.aRoll_rad, aTime);

				//Call regulation for pitch axis rate
				misc_PID(&(gFlightCompute.aDesiredRate[kPitch]), &(gFlightCompute.aPIDAngle[kPitch]), -gReceiver.aChannels_rad[kReceiverPitch], gAttitudeSensors.aPitch_rad, aTime);
			}

			gFlightCompute.aDesiredRate[kYaw] = gReceiver.aChannels_radS[kReceiverYaw];

		}
		else if(gFlightCompute.aFLightMode ==kRate)
		{
			gFlightCompute.aDesiredRate[kRoll] = gReceiver.aChannels_radS[kReceiverRoll];
			gFlightCompute.aDesiredRate[kPitch] = gReceiver.aChannels_radS[kReceiverPitch];
			gFlightCompute.aDesiredRate[kYaw] = gReceiver.aChannels_radS[kReceiverYaw];

			//Reset angle PID as it will be outdated if switched on later
			misc_ResetPID(gFlightCompute.aPIDAngle);
		}


		//Call regulation for roll axis rate
		misc_PID(&aPIDRollRateOutput, &(gFlightCompute.aPIDRate[kRoll]), gFlightCompute.aDesiredRate[kRoll], gAttitudeSensors.aRollRate_rads, aTime);

		//Call regulation for pitch axis rate
		misc_PID(&aPIDPitchRateOutput, &(gFlightCompute.aPIDRate[kPitch]), gFlightCompute.aDesiredRate[kPitch], gAttitudeSensors.aPitchRate_rads, aTime);

		//Call regulation for yaw axis
		misc_PID(&aPIDYawRateOutput, &(gFlightCompute.aPIDRate[kYaw]), gFlightCompute.aDesiredRate[kYaw], -gAttitudeSensors.aHeadingRate_rads, aTime);
	}

	//Call motor mix
	gFlightCompute_MotorMix(aThrottle, aPIDPitchRateOutput, aPIDRollRateOutput, aPIDYawRateOutput, aToMotors);

	//Constrain and send to motors
	gFlightCompute_ConstrainSendMotorsValues(aToMotors, aThrottle);
}



static void gFlightCompute_MotorMix(float aThrottle, float aPIDPitchOutput, float aPIDRollOutput, float aPIDYawOutput, float* aOutput)
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

static void gFlightCompute_ConstrainSendMotorsValues(float* aOutput, float aThrottle)
{
	for (int i=0; i<NUMBER_OF_MOTORS; i++)
	{
		//Constrain to min/max
		if(aOutput[i]<MOTOR_IDLE_VALUE)
		{
			aOutput[i] = MOTOR_IDLE_VALUE;
		}
		else if (aOutput[i]>MOTOR_MAX_VALUE)
		{
			aOutput[i] = MOTOR_MAX_VALUE;
		}

		//Reduce the output to not jump in the air if not leveled
		if(aOutput[i] > 2*aThrottle)
		{
			aOutput[i] = 2*aThrottle;
		}

		//Send
		gFlightCompute.aMotorsOutput[i] = (UInt16)(aOutput[i]);
	}
}
