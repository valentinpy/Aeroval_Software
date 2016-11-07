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

#include "mGpio.h"

// At the moment: only output is supported.
// TODO implement: add GPIO as input

//Configure the Gpios (enable port, direction, crossbar,...)
void mGpio_Setup(UInt32 maskGpiosOutput)
{
	//set crossbar (GPIO: alternate 1)
	iDio_PinConfig(kPortD, kPin8, kAlternate1);
	iDio_PinConfig(kPortD, kPin9, kAlternate1);
	iDio_PinConfig(kPortD, kPin10, kAlternate1);
	iDio_PinConfig(kPortD, kPin11, kAlternate1);
	iDio_PinConfig(kPortD, kPin12, kAlternate1);
	iDio_PinConfig(kPortD, kPin13, kAlternate1);
	iDio_PinConfig(kPortD, kPin14, kAlternate1);
	iDio_PinConfig(kPortD, kPin15, kAlternate1);


	//set direction: input for all
	iDio_SetPortDirection(kPortD, 0xFFFFFFFF, kIoInput);

	//set direction: output only the the ones that have been expressly specified as output
	iDio_SetPortDirection(kPortD, maskGpiosOutput, kIoOutput);
}

//All Gpios on
void mGpio_AllOn()
{
	iDio_SetPort(kPortD, kMaskGpiosAll, kIoOn);
}

//All Gpios off
void mGpio_AllOff()
{
	iDio_SetPort(kPortD, kMaskGpiosAll, kIoOff);
}

//Toggle all Gpios
void mGpio_AllToggle()
{
	iDio_TogglePort(kPortD, kMaskGpiosAll);
}

//set/clear a mask of Gpios
// aGetMask is a 8 bits mask. 0x00 => no Gpios, 0xff => 8 Gpios,...
void mGpio_Write(GpioMaskEnum aGetMask, GpioStateEnum aState)
{
	IoMaskEnum aSendMask = 0;
	aSendMask |= ((aGetMask & 0x1)<<15);
	aSendMask |= ((aGetMask & 0x2)<<13);
	aSendMask |= ((aGetMask & 0x4)<<11);
	aSendMask |= ((aGetMask & 0x8)<<9);
	aSendMask |= ((aGetMask & 0x10)<<7);
	aSendMask |= ((aGetMask & 0x20)<<5);
	aSendMask |= ((aGetMask & 0x40)<<3);
	aSendMask |= ((aGetMask & 0x80)<<1);

	iDio_SetPort(kPortD, aSendMask, aState);
}



