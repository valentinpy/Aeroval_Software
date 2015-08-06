/*
 * mSwitches.c
 *
 *  Created on: 25 juil. 2015
 *      Author: valentin.py
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
	iDio_SetPortDirection(kPortB, kMaskSwitchesAll, kIoInput);

}

//Get Switches
UInt8 mSwitches_Get()
{
	UInt32 aPortE = iDio_GetPortE();
	UInt32 aRet = 0;
	aRet |= ((aPortE>>7) & 0x3F); //SW0-5
	aRet |= ((aPortE>>21) & 0x40); //SW6
	aRet |= ((aPortE >>19) & 0x80); //SW7
	return (UInt8) aRet;
}
