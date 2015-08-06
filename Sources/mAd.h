/*
 * mAd.h
 *
 *  Created on: 26 juil. 2015
 *      Author: valentin.py
 */

#ifndef SOURCES_MAD_H_
#define SOURCES_MAD_H_

#include "iAd.h"

#define kAdNbOfBit	12
#define kAdConvertVal (float)((3.3)/(4096.0))

// ADC enum
typedef enum
{
	kSonar0,
	kSonar1,
	kSonar2,
	kSonar3,
	kSonar4,
	kSonar5
}SonarsEnum;

//-----------------------------------------------------------------------
// ADC 0 & 1 setup
//-----------------------------------------------------------------------
void mAd_Setup(void);


//-----------------------------------------------------------------------
// ADC conversion input value read --> Voltage of the battery
//-----------------------------------------------------------------------
float mAd_readBattVoltage(void);

//-----------------------------------------------------------------------
// ADC conversion input value read --> Current
// TODO implement
//-----------------------------------------------------------------------
float mAd_readCurrent(void);

//-----------------------------------------------------------------------
// ADC conversion input value read --> Sonars
//-----------------------------------------------------------------------
float mAd_readSonars(SonarsEnum kSonar);



#endif /* SOURCES_MAD_H_ */
