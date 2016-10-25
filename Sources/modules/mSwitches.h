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

#ifndef SOURCES_MSWITCHES_H_
#define SOURCES_MSWITCHES_H_

#include "../interfaces/iDio.h"

#define kMaskSwitchesAll 0xC001F80

// Switch mask
typedef enum {
	kMaskSwitch0 = 0x1,		// Master motors: 	[0: Off, 1:ON]
	kMaskSwitch1 = 0x2,		// Algo orientation:[0:Sentral, 1:Madgwick]
	kMaskSwitch2 = 0x4,		// ND
	kMaskSwitch3 = 0x8,		// ND
	kMaskSwitch4 = 0x10,	// Monitoring: 		[0: Off, 1:On]
	kMaskSwitch5 = 0x20,	// USB Monitoring:	[0: Off, 1:On]
	kMaskSwitch6 = 0x40,	// BT Monitoring:	[0: Off, 1:On]
	kMaskSwitch7 = 0x80,	// RX Monitoring:	[0: Off, 1:On]
	kMaskSwitchAll = 0xFF
} SwitchesMaskEnum;

//Setup switches
void mSwitches_Setup(void);

//Get Switches
UInt8 mSwitches_Get(SwitchesMaskEnum aMask);

#endif /* SOURCES_MSWITCHES_H_ */
