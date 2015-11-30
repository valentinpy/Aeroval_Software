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

#include "mSwitches.h"

//Setup switches
void mSwitches_Setup()
{
	//set crossbar (GPIO: alternate 1)
	iDio_PinConfig(kPortE, kPin7, kAlternate1);
	iDio_PinConfig(kPortE, kPin8, kAlternate1);
	iDio_PinConfig(kPortE, kPin9, kAlternate1);
	iDio_PinConfig(kPortE, kPin10, kAlternate1);
	iDio_PinConfig(kPortE, kPin11, kAlternate1);
	iDio_PinConfig(kPortE, kPin12, kAlternate1);
	iDio_PinConfig(kPortE, kPin26, kAlternate1);
	iDio_PinConfig(kPortE, kPin27, kAlternate1);

	//set direction: input
	iDio_SetPortDirection(kPortB, 0xC001F80, kIoInput);

}

//Get Switches
UInt8 mSwitches_Get(SwitchesMaskEnum aMask)
{
	UInt32 aPortE = iDio_GetPortE();
	UInt32 aRet = 0;
	aRet |= ((aPortE>>7) & 0x3F); //SW0-5
	aRet |= ((aPortE>>21) & 0x40); //SW6
	aRet |= ((aPortE >>19) & 0x80); //SW7
	aRet &= aMask;
	return (UInt8) aRet;
}
