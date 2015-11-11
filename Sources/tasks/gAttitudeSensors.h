/*
 * gAttitudeSensors.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_TASKS_GATTITUDESENSORS_H_
#define SOURCES_TASKS_GATTITUDESENSORS_H_

#include "modules/mMPU.h"
#include "modules/mMag.h"
#include "modules/mEm7180.h"
#include "../gMbox.h"

//Factor between Int16 (full range) to rad/s of the orientation sensor/gyro
#define kGyroToRadS ((float)0.00266)

//-----------------------------------
// Attitude measurement initialization
//-----------------------------------
void gAttitudeSensors_Setup();

//-----------------------------------
// Attitude measurement
//-----------------------------------
void gAttitudeSensors_Run();

#endif /* SOURCES_TASKS_GATTITUDESENSORS_H_ */
