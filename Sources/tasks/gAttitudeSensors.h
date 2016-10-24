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

#ifndef SOURCES_TASKS_GATTITUDESENSORS_H_
#define SOURCES_TASKS_GATTITUDESENSORS_H_

#include "modules/mMPU.h"
#include "modules/mMag.h"
#include "modules/mEm7180.h"
#include "modules/mMPU6000.h"
#include "../gMbox.h"

//Factor between Int16 (full range) to rad/s of the orientation sensor/gyro
//TODO ERROR: As the coefficient changed since last real test, the PID need to be updated!
#define kEM7180_GyroToRadS ((float)0.0010653) //=0.061035dps * pi/180, according to acquire_data.m matlab script
//#define kEM7180_GyroToRadS ((float)0.00266)

#define kEM7180_AccelToG ((float)0.0020534) //TODO: Warn: select, compute, test scaling!

//-----------------------------------
// Attitude measurement initialization
//-----------------------------------
void gAttitudeSensors_Setup(void);

//-----------------------------------
// Attitude measurement
//-----------------------------------
void gAttitudeSensors_Run(void);

#endif /* SOURCES_TASKS_GATTITUDESENSORS_H_ */
