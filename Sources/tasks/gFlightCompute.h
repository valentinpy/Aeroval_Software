/*
 * gFlightCompute.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_TASKS_GFLIGHTCOMPUTE_H_
#define SOURCES_TASKS_GFLIGHTCOMPUTE_H_

#include "../misc/def.h"
#include "../gMbox.h"
#include "../modules/mReceiver.h"


//-----------------------------------
// Flight controller (regulation,..) initialization
//-----------------------------------
void gFlightCompute_Setup();

//-----------------------------------
// Run the flight controller
//-----------------------------------
void gFlightCompute_Run();



#endif /* SOURCES_TASKS_GFLIGHTCOMPUTE_H_ */
