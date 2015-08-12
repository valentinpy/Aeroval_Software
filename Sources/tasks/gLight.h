/*
 * gLight.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_TASKS_GLIGHT_H_
#define SOURCES_TASKS_GLIGHT_H_

#include "../modules/mHleds.h"
#include "../gMbox.h"
#include "../modules/mDelay.h"
#include "../modules/mLeds.h"
#include "../modules/mHleds.h"

//-----------------------------------
// Light (LED strips) inialisation
//-----------------------------------
void gLight_Setup();

//-----------------------------------
// Run light
//-----------------------------------
void gLight_Run();

#endif /* SOURCES_TASKS_GLIGHT_H_ */
