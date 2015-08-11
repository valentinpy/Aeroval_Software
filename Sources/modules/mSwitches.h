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

//Setup switches
void mSwitches_Setup();

//Get Switches
UInt8 mSwitches_Get();

#endif /* SOURCES_MSWITCHES_H_ */
