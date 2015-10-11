/*
 * mGpio.h
 *
 *  Created on: 11 oct. 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_MODULES_MGPIO_H_
#define SOURCES_MODULES_MGPIO_H_


#include "../interfaces/iDio.h"


#define kMaskGpiosAll  0xFF00


// Etat des Gpios configur�s
typedef enum {
	kGpioOn, kGpioOff
} GpioStateEnum;

// Masque des Gpios
typedef enum {
	kMaskGpio0 = 0x1,
	kMaskGpio1 = 0x2,
	kMaskGpio2 = 0x4,
	kMaskGpio3 = 0x8,
	kMaskGpio4 = 0x10,
	kMaskGpio5 = 0x20,
	kMaskGpio6 = 0x40,
	kMaskGpio7 = 0x80,
	kMaskGpioAll = 0xFF
} GpioMaskEnum;


//---------------------------------------------------------------------------------
// Prototypes
//---------------------------------------------------------------------------------
//Configure the Gpios (enable port, direction, crossbar,...)
void mGpio_Setup();

//All Gpios on
void mGpio_AllOn();

//All Gpios off
void mGpio_AllOff();

//Toggle all Gpios
void mGpio_AllToggle();

//set/clear a mask of Gpios
// aGetMask is a 8 bits mask. 0x00 => no Gpios, 0xff => 8 Gpios,...
void mGpio_Write(GpioMaskEnum aGetMask, GpioStateEnum aState);


#endif /* SOURCES_MODULES_MGPIO_H_ */
