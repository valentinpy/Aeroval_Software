/*
 * mServos.h
 *
 *  Created on: 4 ao�t 2015
 *      Author: valentin.py
 */

#ifndef SOURCES_MSERVOS_H_
#define SOURCES_MSERVOS_H_

#include "def.h"
#include "iFtm.h"

// Servos Enum
typedef enum
{
	kServo0,
	kServo1,
	kServo2,
	kServo3
}ServosEnum;

//------------------------------------------------------------
// Setup servos
//------------------------------------------------------------
void mServos_Setup();

//------------------------------------------------------------
// Set min and max for the servos
// TODO implement
//------------------------------------------------------------
void mServos_SetMinMax();

//------------------------------------------------------------
// Freewheel
// aServo: which servo
//------------------------------------------------------------
void mServos_Freewheel(ServosEnum aServo);

//------------------------------------------------------------
// Set position of a servo
// aPosition: 0-1000
// aServo: which servo
//------------------------------------------------------------
void mServos_SetPosition(ServosEnum aServo, UInt16 aPosition);

#endif /* SOURCES_MSERVOS_H_ */
