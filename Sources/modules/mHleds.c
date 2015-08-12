/*
 * mHleds.c
 *
 *  Created on: 25 juil. 2015
 *      Author: valentin.py
 */

#include "mHleds.h"

//Configure the leds (enable port, direction, crossbar,...)
void mHleds_Setup()
{
	//set crossbar (GPIO: alternate 1)
	iDio_PinConfig(kPortA, kPin24, kAlternate1);
	iDio_PinConfig(kPortA, kPin25, kAlternate1);
	iDio_PinConfig(kPortA, kPin26, kAlternate1);
	iDio_PinConfig(kPortA, kPin27, kAlternate1);

	//set direction: output
	iDio_SetPortDirection(kPortA, kMaskHledsAll, kIoOutput);
}

//All leds on
void mHleds_AllOn()
{
	iDio_SetPort(kPortA, kMaskHledsAll, kIoOn);
}

//All leds off
void mHleds_AllOff()
{
	iDio_SetPort(kPortA, kMaskHledsAll, kIoOff);
}

//Toggle all leds
void mHleds_AllToggle()
{
	iDio_TogglePort(kPortA, kMaskHledsAll);
}

//Toggle one led
void mHleds_Toggle(HledMaskEnum aGetMask)
{
	IoMaskEnum aSendMask = ((aGetMask & 0xF)<<24);
	iDio_TogglePort(kPortA, aSendMask);
}

//set/clear a mask of Leds
// aGetMask is a 4 bits mask. 0x0 => no leds, 0xf => 4 leds,...
void mHleds_Write(HledMaskEnum aGetMask, HledStateEnum aState)
{
	IoMaskEnum aSendMask = ((aGetMask & 0xF)<<24);
	iDio_SetPort(kPortA, aSendMask, aState);
}
