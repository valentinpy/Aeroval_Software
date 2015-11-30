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

#ifndef SOURCES_MHLEDS_H_
#define SOURCES_MHLEDS_H_

#include "../interfaces/iDio.h"

#define kMaskHledsAll  0xF000000


// Etat des Leds configur�s
typedef enum {
	kHledOn, kHledOff
} HledStateEnum;

// Masque des Leds
typedef enum {
	kMaskHled0 = 0x1,
	kMaskHled1 = 0x2,
	kMaskHled2 = 0x4,
	kMaskHled3 = 0x8,
	kMaskHledAll = 0xF
} HledMaskEnum;


//---------------------------------------------------------------------------------
// Prototypes
//---------------------------------------------------------------------------------
//Configure the leds (enable port, direction, crossbar,...)
void mHleds_Setup();

//All leds on
void mHleds_AllOn();

//All leds off
void mHleds_AllOff();

//Toggle all leds
void mHleds_AllToggle();

//Toggle one led
void mHleds_Toggle(HledMaskEnum aGetMask);

//set/clear a mask of Leds
// aGetMask is a 4 bits mask. 0x0 => no leds, 0xf => 4 leds,...
void mHleds_Write(HledMaskEnum aMask, HledStateEnum aState);


#endif /* SOURCES_MHLEDS_H_ */
