/*
 * mLeds.c
 *
 *  Created on: 25 juil. 2015
 *      Author: valentin.py
 */
#include "mLeds.h"
#include "iDio.h"

//Configure the leds (enable port, direction, crossbar,...)
void mLeds_Setup()
{
	//set crossbar (GPIO: alternate 1)
	iDio_PinConfig(kPortB, kPin16, kAlternate1);
	iDio_PinConfig(kPortB, kPin17, kAlternate1);
	iDio_PinConfig(kPortB, kPin18, kAlternate1);
	iDio_PinConfig(kPortB, kPin19, kAlternate1);
	iDio_PinConfig(kPortB, kPin20, kAlternate1);
	iDio_PinConfig(kPortB, kPin21, kAlternate1);
	iDio_PinConfig(kPortB, kPin22, kAlternate1);
	iDio_PinConfig(kPortB, kPin23, kAlternate1);

	//set direction: output
	iDio_SetPortDirection(kPortB, kMaskLedsAll, kIoOutput);
}

//All leds on
void mLeds_AllOn()
{
	iDio_SetPort(kPortB, kMaskLedsAll, kIoOn);
}

//All leds off
void mLeds_AllOff()
{
	iDio_SetPort(kPortB, kMaskLedsAll, kIoOff);
}

//Toggle all leds
void mLeds_AllToggle()
{
	iDio_TogglePort(kPortB, kMaskLedsAll);
}

//set/clear a mask of Leds
// aGetMask is a 8 bits mask. 0x00 => no leds, 0xff => 8 leds,...
void mLeds_Write(LedMaskEnum aGetMask, LedStateEnum aState)
{
	IoMaskEnum aSendMask = 0;
	aSendMask |= ((aGetMask & 0x1)<<23);
	aSendMask |= ((aGetMask & 0x2)<<21);
	aSendMask |= ((aGetMask & 0x4)<<19);
	aSendMask |= ((aGetMask & 0x8)<<17);
	aSendMask |= ((aGetMask & 0x10)<<15);
	aSendMask |= ((aGetMask & 0x20)<<13);
	aSendMask |= ((aGetMask & 0x40)<<11);
	aSendMask |= ((aGetMask & 0x80)<<9);

	iDio_SetPort(kPortB, aSendMask, aState);
}
