/*
 * gReceiver.h
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_TASKS_GRECEIVER_H_
#define SOURCES_TASKS_GRECEIVER_H_


#include "../modules/mReceiver.h"
#include "../gMbox.h"

//-----------------------------------
// Receiver initialisation
//-----------------------------------
void gReceiver_Setup();

//-----------------------------------
// Read PWM from receiver
//-----------------------------------
void gReceiver_Run();

#endif /* SOURCES_TASKS_GRECEIVER_H_ */
