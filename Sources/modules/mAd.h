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

#ifndef SOURCES_MAD_H_
#define SOURCES_MAD_H_

#include "../interfaces/iAd.h"
#include "../misc/def.h"


#define kAdNbOfBit	12
#define kAdConvertVal (float)((3.3)/(4096.0))

// ADC enum
typedef enum
{
	kSonar0,
	kSonar1,
	kSonar2,
	kSonar3,
	kSonar4,
	kSonar5
}SonarsEnum;

//-----------------------------------------------------------------------
// ADC 0 & 1 setup
//-----------------------------------------------------------------------
void mAd_Setup(void);


//-----------------------------------------------------------------------
// ADC conversion input value read --> Voltage of the battery
//-----------------------------------------------------------------------
float mAd_readBattVoltage(void);

//-----------------------------------------------------------------------
// ADC conversion input value read --> Current
// TODO implement
//-----------------------------------------------------------------------
float mAd_readCurrent(void);

//-----------------------------------------------------------------------
// ADC conversion input value read --> Sonars
//-----------------------------------------------------------------------
float mAd_readSonars(SonarsEnum kSonar);



#endif /* SOURCES_MAD_H_ */
