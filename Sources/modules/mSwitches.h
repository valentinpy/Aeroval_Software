/*
 * mSwitches.h
 *
 *  Created on: 25 juil. 2015
 *      Author: valentin.py
 */

#ifndef SOURCES_MSWITCHES_H_
#define SOURCES_MSWITCHES_H_

#include "../interfaces/iDio.h"

#define kMaskSwitchesAll 0xC001F80

// Switch mask
typedef enum {
	kMaskSwitch0 = 0x1,		//Motors: [1:On, 0: Off]
	kMaskSwitch1 = 0x2,
	kMaskSwitch2 = 0x4,
	kMaskSwitch3 = 0x8,
	kMaskSwitch4 = 0x10,	// Telemetry: [1:On, 0: Off]
	kMaskSwitch5 = 0x20,
	kMaskSwitch6 = 0x40,
	kMaskSwitch7 = 0x80,
	kMaskSwitchAll = 0xFF
} SwitchesMaskEnum;

//Setup switches
void mSwitches_Setup();

//Get Switches
UInt8 mSwitches_Get(SwitchesMaskEnum aMask);

#endif /* SOURCES_MSWITCHES_H_ */
