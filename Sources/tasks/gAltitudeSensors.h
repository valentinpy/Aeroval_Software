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

#ifndef SOURCES_TASKS_GALTITUDESENSORS_H_
#define SOURCES_TASKS_GALTITUDESENSORS_H_

#include "../modules/mPressure.h"
#include "../gMbox.h"


//-----------------------------------
// Altitude measurement initialization
//-----------------------------------
void gAltitudeSensors_Setup(void);

//-----------------------------------
// Altitude measurement
//-----------------------------------
void gAltitudeSensors_Run(void);

#endif /* SOURCES_TASKS_GALTITUDESENSORS_H_ */
