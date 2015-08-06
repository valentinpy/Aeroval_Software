/*
 * mLeds.h
 *
 *  Created on: 25 juil. 2015
 *      Author: valentin.py
 */

#ifndef SOURCES_MLEDS_H_
#define SOURCES_MLEDS_H_

#define kMaskLedsAll  0xFF0000


// Etat des Leds configurés
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
