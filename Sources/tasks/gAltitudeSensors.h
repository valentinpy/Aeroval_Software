/*
 * gAltitudeSensors.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_TASKS_GALTITUDESENSORS_H_
#define SOURCES_TASKS_GALTITUDESENSORS_H_

#include "../modules/mPressure.h"
#include "../gMbox.h"


//-----------------------------------
// Altitude measurement initialization
//-----------------------------------
void gAltitudeSensors_Setup();

//-----------------------------------
// Altitude measurement
//-----------------------------------
void gAltitudeSensors_Run();

#endif /* SOURCES_TASKS_GALTITUDESENSORS_H_ */
