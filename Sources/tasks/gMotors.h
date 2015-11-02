/*
 * gMotors.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_TASKS_GMOTORS_H_
#define SOURCES_TASKS_GMOTORS_H_

#include "../modules/mMotors.h"
#include "../modules/mSwitches.h"
#include "../gMbox.h"


//-----------------------------------
// Motors initialisation
//-----------------------------------
void gMotors_Setup();

//-----------------------------------
// Send commands to motors
//-----------------------------------
void gMotors_Run();


#endif /* SOURCES_TASKS_GMOTORS_H_ */
