/*
 * iFtm.h
 *
 *  Created on: 3 ao�t 2015
 *      Author: valentin.py
 */

#ifndef SOURCES_IFTM_H_
#define SOURCES_IFTM_H_

#include "../misc/def.h"
#include "../misc/derivative.h"
#include "iDio.h"

// PWM Out Enum
typedef enum
{
	kPwmOut0,
	kPwmOut1,
	kPwmOut2,
	kPwmOut3,
	kPwmOut4,
	kPwmOut5,
	kPwmOut6,
	kPwmOut7,
	kPwmOut8,
	kPwmOut9,
	kPwmOut10,
	kPwmOut11
}PwmOutEnum;

// PWM In Enum
typedef enum
{
	kPwmIn0,
	kPwmIn1,
	kPwmIn2,
	kPwmIn3,
	kPwmIn4,
	kPwmIn5,
	kPwmIn6,
	kPwmIn7
}PwmInEnum;


//------------------------------------------------------------
// Configure the FlexTimers
//------------------------------------------------------------
void iFtm_Config();

//------------------------------------------------------------
// Set a PWM output
//------------------------------------------------------------
void iFtm_SetPwm(PwmOutEnum aOut, UInt32 aTimeUs);


//------------------------------------------------------------
// Get a PWM input
//------------------------------------------------------------
UInt16 iFtm_ReadPwm(PwmInEnum aIn);

#endif /* SOURCES_IFTM_H_ */
