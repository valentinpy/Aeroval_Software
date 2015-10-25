/*
 * gFlightCompute.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_TASKS_GFLIGHTCOMPUTE_H_
#define SOURCES_TASKS_GFLIGHTCOMPUTE_H_

#include "userDefined.h"
#include "../misc/def.h"
#include "../gMbox.h"
#include "../modules/mReceiver.h"
#include "../modules/mDelay.h"

//enum that contains the PID data variables
typedef enum {
	kPIDRoll,
	kPIDPitch,
	kPIDYaw
} sPIDenum;

//Struct that contains the PID datas for each PID
typedef struct {
	Int16 aKp, aKi, aKd;
	Int16 aPreviousError;
	Int16 aIntegral;
	UInt16 aPreviousTime;
} PIDdata;
PIDdata sPID [3];



//-----------------------------------
// Flight controller (regulation,..) initialization
//-----------------------------------
void gFlightCompute_Setup();

//-----------------------------------
// Run the flight controller
//-----------------------------------
void gFlightCompute_Run();



#endif /* SOURCES_TASKS_GFLIGHTCOMPUTE_H_ */
