/*
 * gMiscSensors.h
 *
 *  Created on: 12 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_TASKS_GMISCSENSORS_H_
#define SOURCES_TASKS_GMISCSENSORS_H_

#include "../misc/def.h"
#include "../modules/mAd.h"
#include "../gMbox.h"

//-----------------------------------
// Miscellaneous sensors initialization
//-----------------------------------
void gMiscSensors_Setup();

//-----------------------------------
// Miscellaneous sensors measurement
//-----------------------------------
void gMiscSensors_Run();


#endif /* SOURCES_TASKS_GMISCSENSORS_H_ */
