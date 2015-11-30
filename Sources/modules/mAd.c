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

#include "mAd.h"

//-----------------------------------------------------------------------
// ADC 0 & 1 setup
//-----------------------------------------------------------------------
void mAd_Setup(void)
{
	//set pin function
	//iDio_PinConfig(kPortC,kPin0, kAlternate0);

	//configure and calibrate iAd
	iAd_Config();
	iAd_Cal(kAdc0);
	iAd_Cal(kAdc1);
	iAd_Config();
}

//-----------------------------------------------------------------------
// ADC conversion input value read --> Voltage of the battery
// Return: voltage in volts
//-----------------------------------------------------------------------
float mAd_readBattVoltage(void)
{
	float aVal;
	iAd_SelectChannel(kAdc0, kAdcCh12);	//channel 12: output of voltage divider
	while(iAd_GetCompleteConvStatus(kAdc0)==false);
	aVal=(float)iAd_GetResult(kAdc0);

	return (aVal*kAdConvertVal*5.7); //5.7 : voltage divide ratio
}
//-----------------------------------------------------------------------
// ADC conversion input value read --> Current
// TODO test
// TODO add ratio to convert into amps
// Return: Current in A
//-----------------------------------------------------------------------
float mAd_readCurrent(void)
{
	float aVal;
	iAd_SelectChannel(kAdc0, kAdcCh13);	//channel 13: output of shunt
	while(iAd_GetCompleteConvStatus(kAdc0)==false);
	aVal=(float)iAd_GetResult(kAdc0);


	return (aVal*kAdConvertVal);
}

//-----------------------------------------------------------------------
// ADC conversion input value read --> Sonars
// TODO add conversion factor (maintenant: renvoie en volts (0...3.3)
//-----------------------------------------------------------------------
float mAd_readSonars(SonarsEnum kSonar)
{
	float aVal = 0;

	switch (kSonar)
	{
	case kSonar0:
		iAd_SelectChannel(kAdc0, kAdcCh22);
		while(iAd_GetCompleteConvStatus(kAdc0)==false);
		aVal=(float)iAd_GetResult(kAdc0);
		break;

	case kSonar1:
		iAd_SelectChannel(kAdc0, kAdcCh16);
		while(iAd_GetCompleteConvStatus(kAdc0)==false);
		aVal=(float)iAd_GetResult(kAdc0);
		break;

	case kSonar2:
		iAd_SelectChannel(kAdc0, kAdcCh23);
		while(iAd_GetCompleteConvStatus(kAdc0)==false);
		aVal=(float)iAd_GetResult(kAdc0);
		break;

	case kSonar3:
		iAd_SelectChannel(kAdc1, kAdcCh23);
		while(iAd_GetCompleteConvStatus(kAdc1)==false);
		aVal=(float)iAd_GetResult(kAdc1);
		break;

	case kSonar4:
		iAd_SelectChannel(kAdc0, kAdcCh8);
		while(iAd_GetCompleteConvStatus(kAdc0)==false);
		aVal=(float)iAd_GetResult(kAdc0);
		break;

	case kSonar5:
		iAd_SelectChannel(kAdc0, kAdcCh9);
		while(iAd_GetCompleteConvStatus(kAdc0)==false);
		aVal=(float)iAd_GetResult(kAdc0);
		break;

	}
	return (aVal*kAdConvertVal);
}
