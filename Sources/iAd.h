/*
 * iAd.h
 *
 *  Created on: 25 juil. 2015
 *      Author: valentin.py
 */

#ifndef SOURCES_IAD_H_
#define SOURCES_IAD_H_

#include "def.h"

// ADC enum
typedef enum
{
	kAdc0,
	kAdc1
}ADCEnum;

// ADC channel enum
typedef enum
{
	kAdcCh0=0,
	kAdcCh1,
	kAdcCh2,
	kAdcCh3,
	kAdcCh4,
	kAdcCh5,
	kAdcCh6,
	kAdcCh7,
	kAdcCh8,
	kAdcCh9,
	kAdcCh10,
	kAdcCh11,
	kAdcCh12,
	kAdcCh13,
	kAdcCh14,
	kAdcCh15,
	kAdcCh16,
	kAdcCh17,
	kAdcCh18,
	kAdcCh19,
	kAdcCh20,
	kAdcCh21,
	kAdcCh22,
	kAdcCh23,
	kAdcTempSensor=0x1a,
	kAdcBandgap,
	kAdcVrefSh=0x1d,
	kAdcVrefSL
}ADCChannelEnum;

//---------------------------------------------------------------------------
// Calibrate ADC0-1
//---------------------------------------------------------------------------
bool iAd_Cal(ADCEnum aAd);

//---------------------------------------------------------------------------
// Init de l'ADC0-1
//---------------------------------------------------------------------------
void iAd_Config(void);

//---------------------------------------------------------------------------
// Interruption fin de conversion de l'AD
//---------------------------------------------------------------------------
void ADC0_IRQHandler(void);

//------------------------------------------------------------
// ADC x get conversion (12 bits unsigned right justified)
//------------------------------------------------------------
UInt16 iAd_GetResult(ADCEnum aAd);

//------------------------------------------------------------
// ADC x select channel
// aCh: which ADC channel
//------------------------------------------------------------
void iAd_SelectChannel(ADCEnum aAd, ADCChannelEnum aCh);

//------------------------------------------------------------
// ADC x get conversion complete flag
//------------------------------------------------------------
bool iAd_GetCompleteConvStatus(ADCEnum aAd);


#endif /* SOURCES_IAD_H_ */
