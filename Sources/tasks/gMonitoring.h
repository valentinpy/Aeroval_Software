/*
 * gMonitoring.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_TASKS_GMONITORING_H_
#define SOURCES_TASKS_GMONITORING_H_

#include "../modules/mRS232.h"
#include "../gMbox.h"
#include "../modules/mDelay.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"


//-----------------------------------
// Monitoring initialisation
//-----------------------------------
void gMonitoring_Setup();

//-----------------------------------
// Run the monitoring
//-----------------------------------
void gMonitoring_Run();


#endif /* SOURCES_TASKS_GMONITORING_H_ */
