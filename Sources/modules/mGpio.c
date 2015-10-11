/*
 * mGpio.c
 *
 *  Created on: 11 oct. 2015
 *      Author: valentinpy
 */

#include "mGpio.h"

// At the moment: only output is supported.
// Todo: add GPIO as input

//Configure the Gpios (enable port, direction, crossbar,...)
void mGpio_Setup()
{
	//set crossbar (GPIO: alternate 1)
	iDio_PinConfig(kPortD, kPin8, kAlternate1);
	iDio_PinConfig(kPortD, kPin9, kAlternate1);
	iDio_PinConfig(kPortD, kPin10, kAlternate1);
	iDio_PinConfig(kPortD, kPin11, kAlternate1);
	iDio_PinConfig(kPortD, kPin12, kAlternate1);
	iDio_PinConfig(kPortD, kPin13, kAlternate1);
	iDio_PinConfig(kPortD, kPin14, kAlternate1);
	iDio_PinConfig(kPortD, kPin15, kAlternate1);


	//set direction: output
	iDio_SetPortDirection(kPortD, kMaskGpiosAll, kIoOutput);
}

//All Gpios on
void mGpio_AllOn()
{
	iDio_SetPort(kPortD, kMaskGpiosAll, kIoOn);
}

//All Gpios off
void mGpio_AllOff()
{
	iDio_SetPort(kPortD, kMaskGpiosAll, kIoOff);
}

//Toggle all Gpios
void mGpio_AllToggle()
{
	iDio_TogglePort(kPortD, kMaskGpiosAll);
}

//set/clear a mask of Gpios
// aGetMask is a 8 bits mask. 0x00 => no Gpios, 0xff => 8 Gpios,...
void mGpio_Write(GpioMaskEnum aGetMask, GpioStateEnum aState)
{
	IoMaskEnum aSendMask = 0;
	aSendMask |= ((aGetMask & 0x1)<<15);
	aSendMask |= ((aGetMask & 0x2)<<14);
	aSendMask |= ((aGetMask & 0x4)<<13);
	aSendMask |= ((aGetMask & 0x8)<<12);
	aSendMask |= ((aGetMask & 0x10)<<11);
	aSendMask |= ((aGetMask & 0x20)<<10);
	aSendMask |= ((aGetMask & 0x40)<<9);
	aSendMask |= ((aGetMask & 0x80)<<8);

	iDio_SetPort(kPortD, aSendMask, aState);
}



