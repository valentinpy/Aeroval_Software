/*
 * userDefined.h
 *
 *  Created on: 20 sept. 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_USERDEFINED_H_
#define SOURCES_USERDEFINED_H_


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
//----------------------- Receiver configuration ---------------------------
//------------------------------------------------------------------------

// Order of channels for the receiver
//TODO conflict with mReceiver
#define THROTTLE	0
#define YAW			1
#define PITCH		2
#define ROLL		3
#define GEAR		4
#define AUX1		5
#define AUX2		6
#define AUX3		7

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
#define MOTOR_IDLE_VALUE	(UInt16)(50)


//------------------------------------------------------------------------
//----------------------- Flight parameters ------------------------------
//------------------------------------------------------------------------

//------------------------------------------------------
// PID Rate
//------------------------------------------------------

//PID Rate Roll
#define kPIDRollRate_Kp		(float)100
#define kPIDRollRate_Ki		(float)0
#define kPIDRollRate_Kd		(float)40000

//PID Rate Pitch
#define kPIDPitchRate_Kp	(float)-100
#define kPIDPitchRate_Ki	(float)0
#define kPIDPitchRate_Kd	(float)-40000

//PID Rate Yaw
#define kPIDYawRate_Kp		(float)100
#define kPIDYawRate_Ki		(float)0
#define kPIDYawRate_Kd		(float)0

#define kWindupGuardRate	(float)150

//------------------------------------------------------
// PID Angle
//------------------------------------------------------

//PID Angle_Roll
#define kPIDRollAngle_Kp	(float)20
#define kPIDRollAngle_Ki	(float)0
#define kPIDRollAngle_Kd	(float)1000

//PID Angle_Pitch
#define kPIDPitchAngle_Kp	(float)-20
#define kPIDPitchAngle_Ki	(float)0
#define kPIDPitchAngle_Kd	(float)-1000

#define kWindupGuardAngle	(float)150

//Convert time measured be receiver module to an angle or in angular velocity, depending on the flight mode (Rate/Angle)
//Used to convert roll & pitch commands to angle/angular velocity for PID

#define kReceiverUsToRadS		(float)0.0314
#define kReceiverMaxRate_radS	(float)(15.7)


//Currently limit between -45;+45° => -pi/4; +pi/4
#define kReceiverUsToRad		(float)0.00157
#define kReceiverMaxAngle_rad	(float)(0.785)


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
