/*
 * Copyright (C) 2015 Valentin Py
 *
 * This file is part of Aeroval.
 *
 * Aeroval is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Aeroval is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SOURCES_MSERVOS_H_
#define SOURCES_MSERVOS_H_

#include "../misc/def.h"
#include "../interfaces/iFtm.h"

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
