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

#ifndef SOURCES_USERDEFINED_H_
#define SOURCES_USERDEFINED_H_


//------------------------------------------------------------------------
//----------------------- General informations ---------------------------
//------------------------------------------------------------------------
#define AEROVAL_VERSION	"0.1 beta"
//#define AEROVAL
#define ARCDRONE

#define USE_EM7180
//#define USE_MPU6000 //TODO Improv: implement
//In debug mode, more informations are read from sensors,... usefull only with debugger and breakpoints
#define DEBUG_MODE

//------------------------------------------------------------------------
//----------------------- FRAME CONFIGURATION ----------------------------
//------------------------------------------------------------------------

// Define which kind of multicopter is used
// Currently, only MOTORMIX_X4 is supported
#define MOTORMIX_X4
//#define MOTORMIX_X6
//#define MOTORMIX_X8
//...




//------------------------------------------------------------------------
//----------------------- Receiver configuration -------------------------
//------------------------------------------------------------------------

// Order of channels for the receiver
#define kReceiverThrottle 	7//
#define kReceiverRoll 		6//
#define kReceiverPitch 		5//
#define kReceiverYaw 		0//
#define kReceiverGear 		4//
#define kReceiverAux1 		3//
#define kReceiverAux2 		2
#define kReceiverAux3 		1

#define kReceiverIDLE		50		//Threshold value for throttle: below: idle, no regulation, above: regulation is applied
#define kReceiverMIN 		50		//Min value for detection of patterns
#define kReceiverMINMIDDLE	450		//Min value of a tri-state switch
#define kReceiverMIDDLE		500		//Middle of the range
#define kReceiverMAXMIDDLE	550		//Max value of a tri-state switch
#define kReceiverMAX		950		//Max value for detection of patterns


//------------------------------------------------------------------------
//----------------------- Motors configuration ---------------------------
//------------------------------------------------------------------------


// Order of motors
#define M0			0
#define M1			1
#define M2			2
#define M3			3
#define M4			4
#define M5			5
#define M6			6
#define M7			7


//------------------------------------------------------------------------
//----------------------- MOTOR / ESC configuration ----------------------
//------------------------------------------------------------------------

// Set the min and max value for motors (in flight).
// Idle value must be greater than 0 to prevent shutting down of motors in flight
#define MOTOR_MAX_VALUE 	(UInt16)(1000)
#define MOTOR_IDLE_VALUE	(UInt16)(110)

//#define MOTORS_NOMEDIANFILTER // The output of the motors are not median-filtered if defined (hide peaks)

//------------------------------------------------------------------------
//----------------------- SENSORS configuration ----------------------
//------------------------------------------------------------------------
#define GYRO_LP_FILTER //The angular speed is LP filtered if defined

//------------------------------------------------------------------------
//----------------------- Flight parameters ------------------------------
//------------------------------------------------------------------------
#ifdef ARCDRONE

	//------------------------------------------------------
	// PID Rate
	//------------------------------------------------------

	//PID Rate Roll
	#define kPIDRollRate_Kp		(float)120
	#define kPIDRollRate_Ki		(float)0//0.01//1
	#define kPIDRollRate_Kd		(float)4500

	//PID Rate Pitch
	#define kPIDPitchRate_Kp	(float)-120
	#define kPIDPitchRate_Ki	(float)-0//-0.01//-1
	#define kPIDPitchRate_Kd	(float)-4500

	//PID Rate Yaw
	#define kPIDYawRate_Kp		(float)100
	#define kPIDYawRate_Ki		(float)0
	#define kPIDYawRate_Kd		(float)0

	#define kWindupGuardRate	(float)100

	//------------------------------------------------------
	// PID Angle
	//------------------------------------------------------

	//PID Angle_Roll
	#define kPIDRollAngle_Kp	(float)2//15
	#define kPIDRollAngle_Ki	(float)0//0.01
	#define kPIDRollAngle_Kd	(float)20

	//PID Angle_Pitch
	#define kPIDPitchAngle_Kp	(float)-2//-15
	#define kPIDPitchAngle_Ki	(float)-0//-0.01
	#define kPIDPitchAngle_Kd	(float)0//-20

	#define kWindupGuardAngle	(float)0.5
	#define kAngleLoopDelay_Ms		(UInt32) 5 //ms

	//Convert time measured be receiver module to an angle or in angular velocity, depending on the flight mode (Rate/Angle)
	//Used to convert roll & pitch commands to angle/angular velocity for PID

	#define kReceiverUsToRadS		(float)0.003925//0.00785//0.0157
	#define kReceiverMaxRate_radS	(float)1.9625//3.925//(7.85)


	//Currently limit between -45;+45� => -pi/8; +pi/8
	#define kReceiverUsToRad		(float)(0.000785)
	#define kReceiverMaxAngle_rad	(float)(0.3925)


#else //Aeroval ?

	//------------------------------------------------------
	// PID Rate
	//------------------------------------------------------

	//PID Rate Roll
	#define kPIDRollRate_Kp		(float)100//60
	#define kPIDRollRate_Ki		(float)0//1
	#define kPIDRollRate_Kd		(float)30000//15000

	//PID Rate Pitch
	#define kPIDPitchRate_Kp	(float)-100 //-60
	#define kPIDPitchRate_Ki	(float)0//-1
	#define kPIDPitchRate_Kd	(float)-30000//-15000

	//PID Rate Yaw
	#define kPIDYawRate_Kp		(float)100
	#define kPIDYawRate_Ki		(float)0
	#define kPIDYawRate_Kd		(float)0

	#define kWindupGuardRate	(float)150

	//------------------------------------------------------
	// PID Angle
	//------------------------------------------------------

	//PID Angle_Roll
	#define kPIDRollAngle_Kp	(float)15//15
	#define kPIDRollAngle_Ki	(float)0//0.01
	#define kPIDRollAngle_Kd	(float)0

	//PID Angle_Pitch
	#define kPIDPitchAngle_Kp	(float)-15//-15
	#define kPIDPitchAngle_Ki	(float)-0//-0.01
	#define kPIDPitchAngle_Kd	(float)-0

	#define kWindupGuardAngle	(float)0.5

	//Convert time measured be receiver module to an angle or in angular velocity, depending on the flight mode (Rate/Angle)
	//Used to convert roll & pitch commands to angle/angular velocity for PID

	#define kReceiverUsToRadS		(float)0.0157
	#define kReceiverMaxRate_radS	(float)(7.85)


	//Currently limit between -45;+45� => -pi/8; +pi/8
	#define kReceiverUsToRad		(float)(0.000785)
	#define kReceiverMaxAngle_rad	(float)(0.3925)


#endif


//------------------------------------------------------------------------
//------------------------- DO NOT MANUALLY MODIFY BELOW -----------------
//------------------------------------------------------------------------

//Calculate number of motors
#if defined(MOTORMIX_X4)
	#define NUMBER_OF_MOTORS 4
#elif defined(MOTORMIX_X6)
	#define NUMBER_OF_MOTORS 6
#elif defined(MOTORMIX_X8)
	#define NUMBER_OF_MOTORS 8
#else
	#error "Bad motor mix configuration"
#endif

#endif /* SOURCES_USERDEFINED_H_ */
