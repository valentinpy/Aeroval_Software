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

#ifndef SOURCES_MLEDS_H_
#define SOURCES_MLEDS_H_

#include "../interfaces/iDio.h"


#define kMaskLedsAll  0xFF0000


// Etat des Leds configur�s
typedef enum {
	kLedOn, kLedOff
} LedStateEnum;

// Masque des Leds
typedef enum {
	kMaskLed0 = 0x1,
	kMaskLed1 = 0x2,
	kMaskLed2 = 0x4,
	kMaskLed3 = 0x8,
	kMaskLed4 = 0x10,
	kMaskLed5 = 0x20,
	kMaskLed6 = 0x40,
	kMaskLed7 = 0x80,
	kMaskLedAll = 0xFF
} LedMaskEnum;


//---------------------------------------------------------------------------------
// Prototypes
//---------------------------------------------------------------------------------
//Configure the leds (enable port, direction, crossbar,...)
void mLeds_Setup();

//All leds on
void mLeds_AllOn();

//All leds off
void mLeds_AllOff();

//Toggle all leds
void mLeds_AllToggle();

//set/clear a mask of Leds
// aGetMask is a 8 bits mask. 0x00 => no leds, 0xff => 8 leds,...
void mLeds_Write(LedMaskEnum aGetMask, LedStateEnum aState);


#endif /* SOURCES_MLEDS_H_ */
