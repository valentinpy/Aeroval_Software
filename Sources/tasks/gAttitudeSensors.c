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

#include "gAttitudeSensors.h"
#include "../misc/filters.h"

//-----------------------------------
// Attitude measurement initialization
//-----------------------------------
void gAttitudeSensors_Setup()
{
	//Setup and open mEm7180
	mEm7180_Setup();
	mEm7180_Open();

	//Initialize variables

	//floats
	gAttitudeSensors.aHeading_rad = 0.0;
	gAttitudeSensors.aPitch_rad   =	0.0;
	gAttitudeSensors.aRoll_rad 	  = 0.0;

	gAttitudeSensors.aHeadingRate_rads = 0.0;
	gAttitudeSensors.aPitchRate_rads   =	0.0;
	gAttitudeSensors.aRollRate_rads 	  = 0.0;

	//int
	gAttitudeSensors.aTimeStamp = 0;
}

//-----------------------------------
// Attitude measurement
//-----------------------------------
void gAttitudeSensors_Run()
{
	//Struct to stock data into
	EM7180_DataStruct aDataResult;

#ifdef DEBUG_MODE
	//readStatus
	mEM7180_readStatus();
#endif

	//Get values from sensor
	mEm7180_GetEuler(&aDataResult);

	//Copy into mailbox

	gAttitudeSensors.aHeading_rad = aDataResult.QX.f;
	gAttitudeSensors.aPitch_rad = 	aDataResult.QY.f; //Z
	gAttitudeSensors.aRoll_rad = 	aDataResult.QZ.f; //Y
#ifdef EM7180_GIRO_NOFILTER
	gAttitudeSensors.aHeadingRate_rads = kGyroToRadS * ((float)aDataResult.GZ);
	gAttitudeSensors.aPitchRate_rads = kGyroToRadS * (float)(aDataResult.GY);
	gAttitudeSensors.aRollRate_rads = kGyroToRadS * ((float)aDataResult.GX);

#else
	//Filter and unit conversion
	gAttitudeSensors.aHeadingRate_rads =  filter_lowPassFilter(kGyroToRadS * ((float)aDataResult.GZ), gAttitudeSensors.aHeadingRate_rads, 0.6);
	gAttitudeSensors.aPitchRate_rads =  filter_lowPassFilter(kGyroToRadS * ((float)aDataResult.GY), gAttitudeSensors.aPitchRate_rads, 0.6);
	gAttitudeSensors.aRollRate_rads =  filter_lowPassFilter(kGyroToRadS * ((float)aDataResult.GX), gAttitudeSensors.aRollRate_rads, 0.6);
#endif

	//Add offset
	gAttitudeSensors.aPitch_rad   += gFlightCompute.aPitch_rad_offset;
	gAttitudeSensors.aRoll_rad    += gFlightCompute.aRoll_rad_offset;

	//Store time
	gAttitudeSensors.aTimeStamp = aDataResult.QTime;
}
