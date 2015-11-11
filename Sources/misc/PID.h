/*
 * PID.h
 *
 *  Created on: 11 nov. 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_MISC_PID_H_
#define SOURCES_MISC_PID_H_

#include "def.h"
#include "../gMbox.h"
#include "../modules/mDelay.h"


void misc_ResetPID(PIDdata* aPID);
void misc_PID(float* aOutput, PIDdata* aPIDstruct, float aTarget, float aMeasured, UInt16 aTime);



#endif /* SOURCES_MISC_PID_H_ */
