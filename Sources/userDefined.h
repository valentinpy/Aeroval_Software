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
#define MOTOR_MAX_VALUE 	1000
#define MOTOR_IDLE_VALUE	50


//------------------------------------------------------------------------
//----------------------- Flight parameters ------------------------------
//------------------------------------------------------------------------

//PID Roll
#define kPIDRoll_Kp		8
#define kPIDRoll_Ki		1
#define kPIDRoll_Kd		4

//PID Pitch
#define kPIDPitch_Kp	8
#define kPIDPitch_Ki	1
#define kPIDPitch_Kd	4//8

//PID Yaw
#define kPIDYaw_Kp		0
#define kPIDYaw_Ki		0
#define kPIDYaw_Kd		0//500

#define kWindupGuard	150

//Convert time measured be receiver module to an angle.
//Used to convert roll & pitch commands to angle for PID
//Currently limit between -45;+45° => -1000*pi/4; +1000*pi/4
#define kReceiverMaxAngle_urad	(Int32)(785000)
#define kReceiverUsTomrad		(float)1570

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
