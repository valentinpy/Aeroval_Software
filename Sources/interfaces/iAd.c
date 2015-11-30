/*
 * Copyright (C) 2015 Valentin Py
 *
 * This file is part of Aeroval.
 *
 * Aeroval is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Aeroval is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "iAd.h"

//---------------------------------------------------------------------------
// Calibrate ADC0-1
//---------------------------------------------------------------------------
bool iAd_Cal(ADCEnum aAd)
{
	UInt16 aCalVar=0;
	bool aRet = false;

	switch(aAd)
	{
	case kAdc0:

		// Max ADC clock -> 4MHz
		ADC0_CFG1&=((~ADC_CFG1_ADIV_MASK)&(~ADC_CFG1_ADICLK_MASK));
		ADC0_CFG1|=(ADC_CFG1_ADIV(3)|ADC_CFG1_MODE(1)|ADC_CFG1_ADICLK(1)|ADC_CFG1_ADLSMP_MASK);

		// Enable Software Conversion Trigger for Calibration Process
		ADC0_SC2&=(~ADC_SC2_ADTRG_MASK);

		// Set single conversion, clear avgs bitfield for next writing
		ADC0_SC3&= ((~ADC_SC3_ADCO_MASK) & (~ADC_SC3_AVGS_MASK));

		// Turn averaging ON and set at max value ( 32 )
		ADC0_SC3|= (ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3) );

		// Start CAL
		ADC0_SC3 |= ADC_SC3_CAL_MASK ;

		// Wait calibration end
		while ( (ADC0_SC1A & ADC_SC1_COCO_MASK ) == FALSE );

		// Check for Calibration fail error and return
		if ((ADC0_SC3&ADC_SC3_CALF_MASK) == ADC_SC3_CALF_MASK)
		{
			//failed
			aRet=false;
		}
		else
		{
			// Calculate plus-side calibration
			aCalVar = 0x00;

			aCalVar =  ADC0_CLP0;
			aCalVar += ADC0_CLP1;
			aCalVar += ADC0_CLP2;
			aCalVar += ADC0_CLP3;
			aCalVar += ADC0_CLP4;
			aCalVar += ADC0_CLPS;
			aCalVar = aCalVar/2;
			aCalVar |= 0x8000; // Set MSB
			ADC0_PG= ADC_PG_PG(aCalVar);

			// Calculate minus-side calibration
			aCalVar = 0x00;

			aCalVar =  ADC0_CLM0;
			aCalVar += ADC0_CLM1;
			aCalVar += ADC0_CLM2;
			aCalVar += ADC0_CLM3;
			aCalVar += ADC0_CLM4;
			aCalVar += ADC0_CLMS;
			aCalVar = aCalVar/2;
			aCalVar |= 0x8000; // Set MSB
			ADC0_MG = ADC_MG_MG(aCalVar);

			// Clear CAL bit
			ADC0_SC3&= (~ADC_SC3_CAL_MASK);

			//success
			aRet = true;
		}
		break;

	case kAdc1:

		// Max ADC clock -> 4MHz
		ADC1_CFG1&=((~ADC_CFG1_ADIV_MASK)&(~ADC_CFG1_ADICLK_MASK));
		ADC1_CFG1|=(ADC_CFG1_ADIV(3)|ADC_CFG1_MODE(1)|ADC_CFG1_ADICLK(1)|ADC_CFG1_ADLSMP_MASK);

		// Enable Software Conversion Trigger for Calibration Process
		ADC1_SC2&=(~ADC_SC2_ADTRG_MASK);

		// Set single conversion, clear avgs bitfield for next writing
		ADC1_SC3&= ((~ADC_SC3_ADCO_MASK) & (~ADC_SC3_AVGS_MASK));

		// Turn averaging ON and set at max value ( 32 )
		ADC1_SC3|= (ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3) );

		// Start CAL
		ADC1_SC3 |= ADC_SC3_CAL_MASK ;

		// Wait calibration end
		while ( (ADC1_SC1A & ADC_SC1_COCO_MASK ) == FALSE );

		// Check for Calibration fail error and return
		if ((ADC1_SC3&ADC_SC3_CALF_MASK) == ADC_SC3_CALF_MASK)
		{
			//failed
			aRet = false;
		}
		else
		{
			// Calculate plus-side calibration
			aCalVar = 0x00;

			aCalVar =  ADC1_CLP0;
			aCalVar += ADC1_CLP1;
			aCalVar += ADC1_CLP2;
			aCalVar += ADC1_CLP3;
			aCalVar += ADC1_CLP4;
			aCalVar += ADC1_CLPS;
			aCalVar = aCalVar/2;
			aCalVar |= 0x8000; // Set MSB
			ADC1_PG= ADC_PG_PG(aCalVar);

			// Calculate minus-side calibration
			aCalVar = 0x00;

			aCalVar =  ADC1_CLM0;
			aCalVar += ADC1_CLM1;
			aCalVar += ADC1_CLM2;
			aCalVar += ADC1_CLM3;
			aCalVar += ADC1_CLM4;
			aCalVar += ADC1_CLMS;
			aCalVar = aCalVar/2;
			aCalVar |= 0x8000; // Set MSB
			ADC1_MG = ADC_MG_MG(aCalVar);

			// Clear CAL bit
			ADC1_SC3&= (~ADC_SC3_CAL_MASK);

			//success
			aRet = true;

		}
		break;
	}
	return aRet;
}


//---------------------------------------------------------------------------
// Init de l'ADC0-1
//---------------------------------------------------------------------------
void iAd_Config(void)
{

	//Crossbar configuration
	PORTB_PCR0 |= (PORT_PCR_MUX(0)); //PTB0
	PORTB_PCR1 |= (PORT_PCR_MUX(0)); //PTB1
	PORTB_PCR2 |= (PORT_PCR_MUX(0)); //PTB2
	PORTB_PCR3 |= (PORT_PCR_MUX(0)); //PTB3

	//ADC0

	// Init du clock de l'ADC
	SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK);

	// Lets calibrate the ADC. 1st setup how the channel will be used.
	//disable_irq(INT_ADC0-16);

	// ADC configuration register 1 (ADCx_CFG1)
	// ADLPC=0, Normal power configuration
	// ADIV=10,The divide ratio is 1 and the clock rate is (input clock)/4
	// ADLSMP=0,short sample time
	// MODE=01,It is single-ended 12-bit conversion
	// ADICLK=0,Bus clock divided by 1 --> 50MHz
	ADC0_CFG1=0;
	ADC0_CFG1|=(ADC_CFG1_ADIV(10)|ADC_CFG1_MODE(1)|ADC_CFG1_ADICLK(0));

	// Configuration register 2 (ADCx_CFG2)
	// MUXSEL=0,ADxxa channels are selected (not used here)
	// ADACKEN=0,Asynchronous clock output disabled
	// ADHSC=1,high speed conversion sequence selected
	// ADLSTS=3,2 extra ADCK cycles; 6 ADCK cycles total sample time
	ADC0_CFG2=0|ADC_CFG2_ADHSC_MASK|ADC_CFG2_ADLSTS(3);


	// Status and control register 2 (ADCx_SC2)
	// ADTRG=0,Software trigger selected
	// ACFE=0,Compare function disabled
	// ACFGT=0,Configures less than threshold, outside range not inclusive and inside range not inclusive functionality
	// based on the values placed in the CV1 and CV2 registers
	// ACREN=0,Range function disabled. Only the compare value 1 register (CV1) is compared
	// DMAEN=0,DMA is disabled
	// REFSEL=0,Default voltage reference pin pair (external pins VREFH and VREFL)
	ADC0_SC2=0;

	// Status and control register 2 (ADCx_SC3)
	// ADCO=0, One conversion or one set of conversions if the hardware average function is enabled (AVGE=1) after initiating a conversion.
	// AVGE=1, Hardware average function enabled
	// AVGS=0, 4 samples averaged
	ADC0_SC3=0|ADC_SC3_AVGE_MASK|ADC_SC3_AVGS(0);

	// ADC status and control registers 1 (ADCx_SC1n)
	// AIEN=0,Conversion complete interrupt disabled
	// DIFF=0,Differential mode enable -> Single-ended conversions and input channels are selected
	// ADCH=0x1f,Input channel select -> Module disabled
	ADC0_SC1A=0;
	ADC0_SC1A=0|ADC_SC1_AIEN_MASK|(ADC_SC1_ADCH(0x1f));


	//ADC1

	// Init du clock de l'ADC
	SIM_SCGC3 |= (SIM_SCGC3_ADC1_MASK);

	// Lets calibrate the ADC. 1st setup how the channel will be used.
	//disable_irq(INT_ADC0-16);

	// ADC configuration register 1 (ADCx_CFG1)
	// ADLPC=0, Normal power configuration
	// ADIV=10,The divide ratio is 1 and the clock rate is (input clock)/4
	// ADLSMP=0,short sample time
	// MODE=01,It is single-ended 12-bit conversion
	// ADICLK=0,Bus clock divided by 1 --> 50MHz
	ADC1_CFG1=0;
	ADC1_CFG1|=(ADC_CFG1_ADIV(10)|ADC_CFG1_MODE(1)|ADC_CFG1_ADICLK(0));

	// Configuration register 2 (ADCx_CFG2)
	// MUXSEL=0,ADxxa channels are selected (not used here)
	// ADACKEN=0,Asynchronous clock output disabled
	// ADHSC=1,high speed conversion sequence selected
	// ADLSTS=3,2 extra ADCK cycles; 6 ADCK cycles total sample time
	ADC1_CFG2=0|ADC_CFG2_ADHSC_MASK|ADC_CFG2_ADLSTS(3);

	// Status and control register 2 (ADCx_SC2)
	// ADTRG=0,Software trigger selected
	// ACFE=0,Compare function disabled
	// ACFGT=0,Configures less than threshold, outside range not inclusive and inside range not inclusive functionality
	// based on the values placed in the CV1 and CV2 registers
	// ACREN=0,Range function disabled. Only the compare value 1 register (CV1) is compared
	// DMAEN=0,DMA is disabled
	// REFSEL=0,Default voltage reference pin pair (external pins VREFH and VREFL)
	ADC1_SC2=0;

	// Status and control register 2 (ADCx_SC3)
	// ADCO=0, One conversion or one set of conversions if the hardware average function is enabled (AVGE=1) after initiating a conversion.
	// AVGE=1, Hardware average function enabled
	// AVGS=0, 4 samples averaged
	ADC1_SC3=0|ADC_SC3_AVGE_MASK|ADC_SC3_AVGS(0);

	// ADC status and control registers 1 (ADCx_SC1n)
	// AIEN=0,Conversion complete interrupt disabled
	// DIFF=0,Differential mode enable -> Single-ended conversions and input channels are selected
	// ADCH=0x1f,Input channel select -> Module disabled
	ADC1_SC1A=0;
	ADC1_SC1A=0|ADC_SC1_AIEN_MASK|(ADC_SC1_ADCH(0x1f));
}

//---------------------------------------------------------------------------
// Interruption fin de conversion de l'AD
//---------------------------------------------------------------------------
void ADC0_IRQHandler(void)
{
	//TODO implement
}

//------------------------------------------------------------
// ADC x get conversion (12 bits unsigned right justified)
//------------------------------------------------------------
UInt16 iAd_GetResult(ADCEnum aAd)
{
	UInt16 aVal;

	switch(aAd)
	{
	case kAdc0:
		//Get value
		aVal=ADC0_RA;

		break;

	case kAdc1:
		//Get value
		aVal=ADC1_RA;
		break;
	}
	return aVal;
}

//------------------------------------------------------------
// ADC x select channel
// aCh: which ADC channel
//------------------------------------------------------------
void iAd_SelectChannel(ADCEnum aAd, ADCChannelEnum aCh)
{
	static UInt16 aVal;

	switch(aAd)
	{
	case kAdc0:
		// Clear ADCH field
		ADC0_SC1A&=(~ADC_SC1_ADCH_MASK);

		// To clear the flag COCO after reseting ADCH
		aVal=ADC0_RA;

		//Change channel
		ADC0_SC1A|=(ADC_SC1_ADCH(aCh));
		break;

	case kAdc1:
		// Clear ADCH field
		ADC1_SC1A&=(~ADC_SC1_ADCH_MASK);

		// To clear the flag COCO after reseting ADCH
		aVal=ADC1_RA;

		//Change channel
		ADC1_SC1A|=(ADC_SC1_ADCH(aCh));
		break;
	}
}

//------------------------------------------------------------
// ADC x get conversion complete flag
//------------------------------------------------------------
bool iAd_GetCompleteConvStatus(ADCEnum aAd)
{
	bool aRet=FALSE;

	switch(aAd)
	{
	case kAdc0:
		aRet=(ADC0_SC1A&ADC_SC1_COCO_MASK)==ADC_SC1_COCO_MASK;
		break;

	case kAdc1:
		aRet=(ADC1_SC1A&ADC_SC1_COCO_MASK)==ADC_SC1_COCO_MASK;
		break;
	}
	return aRet;
}

