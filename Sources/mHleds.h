/*
 * mHleds.h
 *
 *  Created on: 25 juil. 2015
 *      Author: valentin.py
 */

#ifndef SOURCES_MHLEDS_H_
#define SOURCES_MHLEDS_H_

#define kMaskHledsAll  0xF000000


// Etat des Leds configurés
typedef enum {
	kHledOn, kHledOff
} HledStateEnum;

// Masque des Leds
typedef enum {
	kMaskHled0 = 0x1,
	kMaskHled1 = 0x2,
	kMaskHled2 = 0x4,
	kMaskHled3 = 0x8,
	kMaskHledAll = 0xF
} HledMaskEnum;


//---------------------------------------------------------------------------------
// Prototypes
//---------------------------------------------------------------------------------
//Configure the leds (enable port, direction, crossbar,...)
void mHleds_Setup();

//All leds on
void mHleds_AllOn();

//All leds off
void mHleds_AllOff();

//Toggle all leds
void mHleds_AllToggle();

//set/clear a mask of Leds
// aGetMask is a 4 bits mask. 0x0 => no leds, 0xf => 4 leds,...
void mHleds_Write(HledMaskEnum aMask, HledStateEnum aState);


#endif /* SOURCES_MHLEDS_H_ */
