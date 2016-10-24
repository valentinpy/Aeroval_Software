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

#ifndef SOURCES_TASKS_GMONITORING_H_
#define SOURCES_TASKS_GMONITORING_H_

#include "../modules/mRS232.h"
#include "../gMbox.h"
#include "../modules/mDelay.h"
#include "../modules/mSwitches.h"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"


//-----------------------------------
// Monitoring initialisation
//-----------------------------------
void gMonitoring_Setup(void);

//-----------------------------------
// Run the monitoring
//-----------------------------------
void gMonitoring_Run(void);


#endif /* SOURCES_TASKS_GMONITORING_H_ */


/* Frame sent over RS232:
 *
 * -------------------------------
 * TYPE		# BYTE		NAME
 * -------------------------------
 * Char		1	'L'		Beginning
 * Char		1	':'		Beginning
 * Int16	2			Heading
 * Int16	2			Pitch
 * Int16	2			Roll
 * UInt16	2			Receiver 0
 * UInt16	2			Receiver 1
 * UInt16	2			Receiver 2
 * UInt16	2			Receiver 3
 * UInt16	2			Receiver 4
 * UInt16	2			Receiver 5
 * UInt16	2			Receiver 6
 * UInt16	2			Receiver 7
 * UInt16	2			Motor 0
 * UInt16	2			Motor 1
 * UInt16	2			Motor 2
 * UInt16	2			Motor 3
 * UInt16	2			Motor 4
 * UInt16	2			Motor 5
 * UInt16	2			Motor 6
 * UInt16	2			Motor 7
 * UInt16	2			Servo 0
 * UInt16	2			Servo 1
 * UInt16	2			Servo 2
 * UInt16	2			Servo 3
 * UInt16	2			Sonar 0
 * UInt16	2			Sonar 1
 * UInt16	2			Sonar 2
 * UInt16	2			Sonar 3
 * UInt16	2			Sonar 4
 * UInt16	2			Sonar 5
 * UInt16	2			Baro
 * UInt16	2			Voltage
 * UInt16	2			Current
 * UInt16	2			Energy
 * UInt8	1			State (armed)
 *
 * Total : 69 bytes
 */
