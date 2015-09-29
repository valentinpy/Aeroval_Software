/*
 * userDefined.h
 *
 *  Created on: 20 sept. 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_USERDEFINED_H_
#define SOURCES_USERDEFINED_H_

// Define which kind of multicopter is used
// Currently, only MOTORMIX_X4 is supported
#define MOTORMIX_X4
//#define MOTORMIX_X6
//#define MOTORMIX_X8
//...

// Set the min and max value for motors (in flight).
// Idle value must be greater than 0 to prevent shuting down of motors in flight
#define MOTOR_MAX_VALUE 	1000
#define MOTOR_IDLE_VALUE	50
#endif /* SOURCES_USERDEFINED_H_ */


// ------------------------ DO NOT MANUALLY MODIFy BELOW -----------------

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
