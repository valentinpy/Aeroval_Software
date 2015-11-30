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

#include "gMiscSensors.h"

//-----------------------------------
// Miscellaneous sensors initialization
//-----------------------------------
void gMiscSensors_Setup()
{
	mAd_Setup();
}

//-----------------------------------
// Miscellaneous sensors measurement
//-----------------------------------
void gMiscSensors_Run()
{
	//Get battery voltage
	gMiscSensors.aBatteryVoltage_mV = (UInt16)(1000 * mAd_readBattVoltage());
	//TODO store/check battery warning in mailbox
}



