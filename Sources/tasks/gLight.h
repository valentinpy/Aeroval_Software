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
void gLight_Setup(void);

//-----------------------------------
// Run light
//-----------------------------------
void gLight_Run(void);

#endif /* SOURCES_TASKS_GLIGHT_H_ */
