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

#include "mHleds.h"

//Configure the leds (enable port, direction, crossbar,...)
void mHleds_Setup()
{
	//set crossbar (GPIO: alternate 1)
	iDio_PinConfig(kPortA, kPin24, kAlternate1);
	iDio_PinConfig(kPortA, kPin25, kAlternate1);
	iDio_PinConfig(kPortA, kPin26, kAlternate1);
	iDio_PinConfig(kPortA, kPin27, kAlternate1);

	//set direction: output
	iDio_SetPortDirection(kPortA, kMaskHledsAll, kIoOutput);
}

//All leds on
void mHleds_AllOn()
{
	iDio_SetPort(kPortA, kMaskHledsAll, kIoOn);
}

//All leds off
void mHleds_AllOff()
{
	iDio_SetPort(kPortA, kMaskHledsAll, kIoOff);
}

//Toggle all leds
void mHleds_AllToggle()
{
	iDio_TogglePort(kPortA, kMaskHledsAll);
}

//Toggle one led
void mHleds_Toggle(HledMaskEnum aGetMask)
{
	IoMaskEnum aSendMask = ((aGetMask & 0xF)<<24);
	iDio_TogglePort(kPortA, aSendMask);
}

//set/clear a mask of Leds
// aGetMask is a 4 bits mask. 0x0 => no leds, 0xf => 4 leds,...
void mHleds_Write(HledMaskEnum aGetMask, HledStateEnum aState)
{
	IoMaskEnum aSendMask = ((aGetMask & 0xF)<<24);
	iDio_SetPort(kPortA, aSendMask, aState);
}
