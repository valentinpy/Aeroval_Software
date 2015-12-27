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

#ifndef SOURCES_MISC_PID_H_
#define SOURCES_MISC_PID_H_

#include "def.h"
#include "../gMbox.h"
#include "../modules/mDelay.h"


void pid_ResetPID(PIDdata* aPID);
void pid_PID(float* aOutput, PIDdata* aPIDstruct, float aTarget, float aMeasured, UInt16 aTime);



#endif /* SOURCES_MISC_PID_H_ */
