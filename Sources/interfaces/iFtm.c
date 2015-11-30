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

#include "iFtm.h"

#define PERIPHERAL_BUS_CLOCK	 ((kClockCpu*1000000)/2)

#define FTM0_CLK_PRESCALE 		 5 // Prescale Selector value -> 5 = divide by 32
#define FTM0_OVERFLOW_FREQUENCY  50.0

#define FTM1_CLK_PRESCALE        7 	// Prescale Selector value -> 7 = divide by 128
#define FTM1_OVERFLOW_FREQUENCY  50.0  // Desired Frequency of PWM Signal

#define FTM2_CLK_PRESCALE        7 	// Prescale Selector value -> 7 = divide by 128
#define FTM2_OVERFLOW_FREQUENCY  50.0  // Desired Frequency of PWM Signal

#define FTM3_CLK_PRESCALE        7 	// Prescale Selector value -> 7 = divide by 128
#define FTM3_OVERFLOW_FREQUENCY  300.0  // Desired Frequency of PWM Signal

#define Ftm0IRQ	42


static UInt16 sPwmInCh0RiseTime = 0;
static UInt16 sPwmInCh1RiseTime = 0;
static UInt16 sPwmInCh2RiseTime = 0;
static UInt16 sPwmInCh3RiseTime = 0;
static UInt16 sPwmInCh4RiseTime = 0;
static UInt16 sPwmInCh5RiseTime = 0;
static UInt16 sPwmInCh6RiseTime = 0;
static UInt16 sPwmInCh7RiseTime = 0;

static UInt16 sPwmInCh0FallTime = 0;
static UInt16 sPwmInCh1FallTime = 0;
static UInt16 sPwmInCh2FallTime = 0;
static UInt16 sPwmInCh3FallTime = 0;
static UInt16 sPwmInCh4FallTime = 0;
static UInt16 sPwmInCh5FallTime = 0;
static UInt16 sPwmInCh6FallTime = 0;
static UInt16 sPwmInCh7FallTime = 0;

static UInt16 sPwmInCh0HighTime = 0;
static UInt16 sPwmInCh1HighTime = 0;
static UInt16 sPwmInCh2HighTime = 0;
static UInt16 sPwmInCh3HighTime = 0;
static UInt16 sPwmInCh4HighTime = 0;
static UInt16 sPwmInCh5HighTime = 0;
static UInt16 sPwmInCh6HighTime = 0;
static UInt16 sPwmInCh7HighTime = 0;


//------------------------------------------------------------
// Configure the FlexTimers
//------------------------------------------------------------
void iFtm_Config()
{
	static bool isAlreadyDone = false;
	if (isAlreadyDone==false)
	{
		//Prevent multiple execution
		isAlreadyDone = true;

		// Enable the Clock to the FTM 0-3 Modules
		SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK;
		SIM_SCGC6 |= (SIM_SCGC6_FTM0_MASK | SIM_SCGC6_FTM1_MASK | SIM_SCGC6_FTM2_MASK);

		// Enable the FTM functions on the the port

		//PWM In 0-3
		PORTC_PCR1 = PORT_PCR_MUX(4);
		PORTA_PCR4 = PORT_PCR_MUX(3);
		PORTA_PCR5 = PORT_PCR_MUX(3);
		PORTA_PCR6 = PORT_PCR_MUX(3);

		//PWM In 4-7
		PORTD_PCR4 = PORT_PCR_MUX(4);
		PORTD_PCR5 = PORT_PCR_MUX(4);
		PORTD_PCR6 = PORT_PCR_MUX(4);
		PORTD_PCR7 = PORT_PCR_MUX(4);

		//PWM Out 8-11
		PORTA_PCR8 = PORT_PCR_MUX(3);
		PORTA_PCR9 = PORT_PCR_MUX(3);
		PORTA_PCR10 = PORT_PCR_MUX(3);
		PORTA_PCR11 = PORT_PCR_MUX(3);

		//PWM Out 0-3
		PORTD_PCR0 = PORT_PCR_MUX(4);
		PORTD_PCR1 = PORT_PCR_MUX(4);
		PORTD_PCR2 = PORT_PCR_MUX(4);
		PORTD_PCR3 = PORT_PCR_MUX(4);

		//PWM Out 4-7
		PORTC_PCR8 = PORT_PCR_MUX(3);
		PORTC_PCR9 = PORT_PCR_MUX(3);
		PORTC_PCR10 = PORT_PCR_MUX(3);
		PORTC_PCR11 = PORT_PCR_MUX(3);


		//FTM0

		// Features Mode Selection (FTMx_MODE)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 900
		// Disable Write Protection - enables changes to QUADEN, DECAPEN, etc.
		FTM0_MODE |= FTM_MODE_WPDIS_MASK;
		//FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
		FTM0_MODE &= (~FTM_MODE_FTMEN_MASK);

		// Counter (FTMx_CNT)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 892
		// FTM Counter Value - reset counter to zero
		FTM0_CNT = 0x0; //FTM Counter Value - reset counter to zero

		// Modulo (FTMx_MOD)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 892
		//Set the overflow rate
		//In our case (input capture): 2^16-1 = 65535
		FTM0_MOD = 65535;

		// Counter Initial Value (FTMx_CNTIN)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 897
		//Set the Counter Initial Value to 0
		FTM0_CNTIN = 0;

		// Channel (n) Status and Control (FTMx_CSC)
		// Chanels 0-7
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 893
		// CHIE=1, Enable channel interrupts.
		// MSB/MSA/ELSB/ELSA --> Input Capture --> rising edge
		// DMA=0, Disable DMA transfers
		FTM0_C0SC =0;
		FTM0_C0SC |=(FTM_CnSC_ELSA_MASK|FTM_CnSC_CHIE_MASK);
		FTM0_C1SC =0;
		FTM0_C1SC |=(FTM_CnSC_ELSA_MASK|FTM_CnSC_CHIE_MASK);
		FTM0_C2SC =0;
		FTM0_C2SC |=(FTM_CnSC_ELSA_MASK|FTM_CnSC_CHIE_MASK);
		FTM0_C3SC =0;
		FTM0_C3SC |=(FTM_CnSC_ELSA_MASK|FTM_CnSC_CHIE_MASK);
		FTM0_C4SC =0;
		FTM0_C4SC |=(FTM_CnSC_ELSA_MASK|FTM_CnSC_CHIE_MASK);
		FTM0_C5SC =0;
		FTM0_C5SC |=(FTM_CnSC_ELSA_MASK|FTM_CnSC_CHIE_MASK);
		FTM0_C6SC =0;
		FTM0_C6SC |=(FTM_CnSC_ELSA_MASK|FTM_CnSC_CHIE_MASK);
		FTM0_C7SC =0;
		FTM0_C7SC |=(FTM_CnSC_ELSA_MASK|FTM_CnSC_CHIE_MASK);

		// Status and Control (FTMx_SC)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 890
		// CLKS=1, Clock Source Selection -> System clock -> 50Mhz
		// PS:3,Prescale Factor Selection -> Divide by 8 --> fr�quence de comptage de 50MHz/8
		// --> overflow � 50MHz/8/65535 => Fr�q min de 95Hz avec 2 aimants 1425 tr/mn min
		// Interruption overflow enable
		FTM0_SC = 0 | FTM_SC_TOIE_MASK | (FTM_SC_CLKS(1) | FTM_SC_PS(FTM0_CLK_PRESCALE));

		// IRQ Config FTM0
		//enable_irq FTM0
		// Clear prending interrupt for FTM0
		NVIC_ClearPendingIRQ(Ftm0IRQ);

		// Interrupt enable for UART0
		NVIC_EnableIRQ(Ftm0IRQ);

		// Set interrupt priority for UART0
		NVIC_SetPriority(Ftm0IRQ, 0);



		//FTM1

		// Features Mode Selection (FTMx_MODE)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 900
		// Disable Write Protection - enables changes to QUADEN, DECAPEN, etc.
		FTM1_MODE |= FTM_MODE_WPDIS_MASK;
		//FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
		FTM1_MODE &= (~FTM_MODE_FTMEN_MASK);

		// Quadrature Decoder Control and Status (FTMx_QDCTRL)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 923
		// Set Edge Aligned PWM
		FTM1_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;

		// Counter (FTMx_CNT)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 892
		// FTM Counter Value - reset counter to zero
		FTM1_CNT = 0x0; //FTM Counter Value - reset counter to zero

		// Modulo (FTMx_MOD)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 892
		//Set the overflow rate
		FTM1_MOD=(PERIPHERAL_BUS_CLOCK/(1<<FTM1_CLK_PRESCALE))/FTM1_OVERFLOW_FREQUENCY;

		// Counter Initial Value (FTMx_CNTIN)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 897
		//Set the Counter Initial Value to 0
		FTM1_CNTIN = 0;

		// Channel (n) Status and Control (FTMx_CSC) for channel 0-7
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 893
		// CHIE=0, Disable channel interrupts. Use software polling
		// MSB/MSA/ELSB/ELSA --> Edge-aligned PWM
		// DMA=0, Disable DMA transfers
		FTM1_C0SC=0;
		FTM1_C0SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
		FTM1_C1SC=0;
		FTM1_C1SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);

		// Status and Control (FTMx_SC)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 890
		// Edit registers when no clock is fed to timer so the MOD value, gets pushed in immediately
		FTM1_SC=0;

		// Channel (n) Value (FTMx_CV)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 896
		// FTMx_CnV contains the captured FTM counter value, this value determines the pulse width

		//FTM1_C0V = FTM1_MOD * DutyCycle; //Dutycycle: [0;1]

		//Dutycycle
		FTM1_C0V = 0;
		FTM1_C1V = 0;

		// Status and Control (FTMx_SC)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 890
		// CPWMS=0,Center-aligned PWM Select -> FTM counter operates in up counting mode
		// CLKS=1, Clock Source Selection -> System clock -> 50Mhz
		// PS:3,Prescale Factor Selection -> Divide by 8
		FTM1_SC|=(FTM_SC_CLKS(1)|FTM_SC_PS(FTM1_CLK_PRESCALE));

		// FTM PWM Load (FTMx_PWMLOAD)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 933
		FTM1_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;



		//FTM2

		// Features Mode Selection (FTMx_MODE)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 900
		// Disable Write Protection - enables changes to QUADEN, DECAPEN, etc.
		FTM2_MODE |= FTM_MODE_WPDIS_MASK;
		//FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
		FTM2_MODE &= (~FTM_MODE_FTMEN_MASK);

		// Quadrature Decoder Control and Status (FTMx_QDCTRL)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 923
		// Set Edge Aligned PWM
		FTM2_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;

		// Counter (FTMx_CNT)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 892
		// FTM Counter Value - reset counter to zero
		FTM2_CNT = 0x0; //FTM Counter Value - reset counter to zero

		// Modulo (FTMx_MOD)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 892
		//Set the overflow rate
		FTM2_MOD=(PERIPHERAL_BUS_CLOCK/(1<<FTM2_CLK_PRESCALE))/FTM2_OVERFLOW_FREQUENCY;

		// Counter Initial Value (FTMx_CNTIN)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 897
		//Set the Counter Initial Value to 0
		FTM2_CNTIN = 0;

		// Channel (n) Status and Control (FTMx_CSC) for channel 0-7
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 893
		// CHIE=0, Disable channel interrupts. Use software polling
		// MSB/MSA/ELSB/ELSA --> Edge-aligned PWM
		// DMA=0, Disable DMA transfers
		FTM2_C0SC=0;
		FTM2_C0SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
		FTM2_C1SC=0;
		FTM2_C1SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);

		// Status and Control (FTMx_SC)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 890
		// Edit registers when no clock is fed to timer so the MOD value, gets pushed in immediately
		FTM2_SC=0;

		// Channel (n) Value (FTMx_CV)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 896
		// FTMx_CnV contains the captured FTM counter value, this value determines the pulse width

		//FTM2_C0V = FTM2_MOD * DutyCycle; //Dutycycle: [0;1]

		//Dutycycle
		FTM2_C0V = 0;
		FTM2_C1V = 0;


		// Status and Control (FTMx_SC)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 890
		// CPWMS=0,Center-aligned PWM Select -> FTM counter operates in up counting mode
		// CLKS=1, Clock Source Selection -> System clock -> 50Mhz
		// PS:3,Prescale Factor Selection -> Divide by 8
		FTM2_SC|=(FTM_SC_CLKS(1)|FTM_SC_PS(FTM2_CLK_PRESCALE));

		// FTM PWM Load (FTMx_PWMLOAD)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 933
		FTM2_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;

		//FTM3

		// Features Mode Selection (FTMx_MODE)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 900
		// Disable Write Protection - enables changes to QUADEN, DECAPEN, etc.
		FTM3_MODE |= FTM_MODE_WPDIS_MASK;
		//FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
		FTM3_MODE &= (~FTM_MODE_FTMEN_MASK);

		// Quadrature Decoder Control and Status (FTMx_QDCTRL)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 923
		// Set Edge Aligned PWM
		FTM3_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;

		// Counter (FTMx_CNT)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 892
		// FTM Counter Value - reset counter to zero
		FTM3_CNT = 0x0; //FTM Counter Value - reset counter to zero

		// Modulo (FTMx_MOD)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 892
		//Set the overflow rate
		FTM3_MOD=(PERIPHERAL_BUS_CLOCK/(1<<FTM3_CLK_PRESCALE))/FTM3_OVERFLOW_FREQUENCY;

		// Counter Initial Value (FTMx_CNTIN)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 897
		//Set the Counter Initial Value to 0
		FTM3_CNTIN = 0;

		// Channel (n) Status and Control (FTMx_CSC) for channel 0-7
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 893
		// CHIE=0, Disable channel interrupts. Use software polling
		// MSB/MSA/ELSB/ELSA --> Edge-aligned PWM
		// DMA=0, Disable DMA transfers
		FTM3_C0SC=0;
		FTM3_C0SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
		FTM3_C1SC=0;
		FTM3_C1SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
		FTM3_C2SC=0;
		FTM3_C2SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
		FTM3_C3SC=0;
		FTM3_C3SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
		FTM3_C4SC=0;
		FTM3_C4SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
		FTM3_C5SC=0;
		FTM3_C5SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
		FTM3_C6SC=0;
		FTM3_C6SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);
		FTM3_C7SC=0;
		FTM3_C7SC|=(FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK);


		// Status and Control (FTMx_SC)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 890
		// Edit registers when no clock is fed to timer so the MOD value, gets pushed in immediately
		FTM3_SC=0;

		// Channel (n) Value (FTMx_CV)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 896
		// FTMx_CnV contains the captured FTM counter value, this value determines the pulse width

		//FTM3_C0V = FTM3_MOD * DutyCycle; //Dutycycle: [0;1]

		// Duty at 0%
		FTM3_C0V = 0;
		FTM3_C1V = 0;
		FTM3_C2V = 0;
		FTM3_C3V = 0;
		FTM3_C4V = 0;
		FTM3_C5V = 0;
		FTM3_C6V = 0;
		FTM3_C7V = 0;



		// Status and Control (FTMx_SC)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 890
		// CPWMS=0,Center-aligned PWM Select -> FTM counter operates in up counting mode
		// CLKS=1, Clock Source Selection -> System clock -> 50Mhz
		// PS:3,Prescale Factor Selection -> Divide by 8
		FTM3_SC|=(FTM_SC_CLKS(1)|FTM_SC_PS(FTM3_CLK_PRESCALE));

		// FTM PWM Load (FTMx_PWMLOAD)
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 933
		FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
	}

	else //Do nothing... setup has already been done!
	{

	}

}

//------------------------------------------------------------
// Set a PWM output
//------------------------------------------------------------
void iFtm_SetPwm(PwmOutEnum aOut, UInt32 aTimeUs)
{
	switch(aOut)
	{
	case kPwmOut0:
		FTM3_C0V = (aTimeUs * FTM3_MOD * FTM3_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut1:
		FTM3_C1V = (aTimeUs * FTM3_MOD * FTM3_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut2:
		FTM3_C2V = (aTimeUs * FTM3_MOD * FTM3_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut3:
		FTM3_C3V = (aTimeUs * FTM3_MOD * FTM3_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut4:
		FTM3_C4V = (aTimeUs * FTM3_MOD * FTM3_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut5:
		FTM3_C5V = (aTimeUs * FTM3_MOD * FTM3_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut6:
		FTM3_C6V = (aTimeUs * FTM3_MOD * FTM3_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut7:
		FTM3_C7V = (aTimeUs * FTM3_MOD * FTM3_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut8:
		FTM1_C0V = (aTimeUs * FTM3_MOD * FTM1_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut9:
		FTM1_C1V = (aTimeUs * FTM3_MOD * FTM1_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut10:
		FTM2_C0V = (aTimeUs * FTM3_MOD * FTM2_OVERFLOW_FREQUENCY) / 1000000;
		break;
	case kPwmOut11:
		FTM2_C1V = (aTimeUs * FTM3_MOD * FTM2_OVERFLOW_FREQUENCY) / 1000000;
		break;

	}
}

//------------------------------------------------------------
// FTM0 IRQ Handler
// Used to measure hich time of PWM signals
// TODO clean! C'est très moche!
//------------------------------------------------------------
void FTM0_IRQHandler(void)
{
	UInt32 aVal;

	// Test si le compteur a fait un overflow
	// TODO à virer?
	if ((FTM0_SC & FTM_SC_TOF_MASK) == FTM_SC_TOF_MASK)
	{
		// Reset du flag
		FTM0_SC &= (~FTM_SC_TOF_MASK);
	}

	// teste si flanc sur input capture channel 0
	if ((FTM0_C0SC &FTM_CnSC_CHF_MASK)==FTM_CnSC_CHF_MASK)
	{
		// Reset du flag
		FTM0_C0SC&=(~FTM_CnSC_CHF_MASK);

		//If rising edge
		if((FTM0_C0SC & FTM_CnSC_ELSA_MASK) == FTM_CnSC_ELSA_MASK)
		{
			//Store time
			sPwmInCh0RiseTime = FTM0_C0V;

			//select falling edge for next interrupt
			FTM0_C0SC &= (~FTM_CnSC_ELSA_MASK);
			FTM0_C0SC |= FTM_CnSC_ELSB_MASK;

		}
		else //If falling edge
		{
			//Store time
			sPwmInCh0FallTime = FTM0_C0V;

			//select rising edge for next interrupt
			FTM0_C0SC &= (~FTM_CnSC_ELSB_MASK);
			FTM0_C0SC |= FTM_CnSC_ELSA_MASK;

			//get width
			if(sPwmInCh0FallTime>sPwmInCh0RiseTime) //Normal
			{
				sPwmInCh0HighTime = sPwmInCh0FallTime - sPwmInCh0RiseTime;
			}
			else //Overflow
			{
				sPwmInCh0HighTime = sPwmInCh0FallTime + (65535-sPwmInCh0RiseTime);
			}

		}
	}

	// teste si flanc sur input capture channel 1
	if ((FTM0_C1SC &FTM_CnSC_CHF_MASK)==FTM_CnSC_CHF_MASK)
	{
		// Reset du flag
		FTM0_C1SC&=(~FTM_CnSC_CHF_MASK);

		//If rising edge
		if((FTM0_C1SC & FTM_CnSC_ELSA_MASK) == FTM_CnSC_ELSA_MASK)
		{
			//Store time
			sPwmInCh1RiseTime = FTM0_C1V;

			//select falling edge for next interrupt
			FTM0_C1SC &= (~FTM_CnSC_ELSA_MASK);
			FTM0_C1SC |= FTM_CnSC_ELSB_MASK;

		}
		else //If falling edge
		{
			//Store time
			sPwmInCh1FallTime = FTM0_C1V;

			//select rising edge for next interrupt
			FTM0_C1SC &= (~FTM_CnSC_ELSB_MASK);
			FTM0_C1SC |= FTM_CnSC_ELSA_MASK;

			//get width
			if(sPwmInCh1FallTime>sPwmInCh1RiseTime) //Normal
			{
				sPwmInCh1HighTime = sPwmInCh1FallTime - sPwmInCh1RiseTime;
			}
			else //Overflow
			{
				sPwmInCh1HighTime = sPwmInCh1FallTime + (65535-sPwmInCh1RiseTime);
			}

		}
	}

	// teste si flanc sur input capture channel 2
	if ((FTM0_C2SC &FTM_CnSC_CHF_MASK)==FTM_CnSC_CHF_MASK)
	{
		// Reset du flag
		FTM0_C2SC&=(~FTM_CnSC_CHF_MASK);

		//If rising edge
		if((FTM0_C2SC & FTM_CnSC_ELSA_MASK) == FTM_CnSC_ELSA_MASK)
		{
			//Store time
			sPwmInCh2RiseTime = FTM0_C2V;

			//select falling edge for next interrupt
			FTM0_C2SC &= (~FTM_CnSC_ELSA_MASK);
			FTM0_C2SC |= FTM_CnSC_ELSB_MASK;

		}
		else //If falling edge
		{
			//Store time
			sPwmInCh2FallTime = FTM0_C2V;

			//select rising edge for next interrupt
			FTM0_C2SC &= (~FTM_CnSC_ELSB_MASK);
			FTM0_C2SC |= FTM_CnSC_ELSA_MASK;

			//get width
			if(sPwmInCh2FallTime>sPwmInCh2RiseTime) //Normal
			{
				sPwmInCh2HighTime = sPwmInCh2FallTime - sPwmInCh2RiseTime;
			}
			else //Overflow
			{
				sPwmInCh2HighTime = sPwmInCh2FallTime + (65535-sPwmInCh2RiseTime);
			}

		}
	}

	// teste si flanc sur input capture channel 3
	if ((FTM0_C3SC &FTM_CnSC_CHF_MASK)==FTM_CnSC_CHF_MASK)
	{
		// Reset du flag
		FTM0_C3SC&=(~FTM_CnSC_CHF_MASK);

		//If rising edge
		if((FTM0_C3SC & FTM_CnSC_ELSA_MASK) == FTM_CnSC_ELSA_MASK)
		{
			//Store time
			sPwmInCh3RiseTime = FTM0_C3V;

			//select falling edge for next interrupt
			FTM0_C3SC &= (~FTM_CnSC_ELSA_MASK);
			FTM0_C3SC |= FTM_CnSC_ELSB_MASK;

		}
		else //If falling edge
		{
			//Store time
			sPwmInCh3FallTime = FTM0_C3V;

			//select rising edge for next interrupt
			FTM0_C3SC &= (~FTM_CnSC_ELSB_MASK);
			FTM0_C3SC |= FTM_CnSC_ELSA_MASK;

			//get width
			if(sPwmInCh3FallTime>sPwmInCh3RiseTime) //Normal
			{
				sPwmInCh3HighTime = sPwmInCh3FallTime - sPwmInCh3RiseTime;
			}
			else //Overflow
			{
				sPwmInCh3HighTime = sPwmInCh3FallTime + (65535-sPwmInCh3RiseTime);
			}

		}
	}

	// teste si flanc sur input capture channel 4
	if ((FTM0_C4SC &FTM_CnSC_CHF_MASK)==FTM_CnSC_CHF_MASK)
	{
		// Reset du flag
		FTM0_C4SC&=(~FTM_CnSC_CHF_MASK);

		//If rising edge
		if((FTM0_C4SC & FTM_CnSC_ELSA_MASK) == FTM_CnSC_ELSA_MASK)
		{
			//Store time
			sPwmInCh4RiseTime = FTM0_C4V;

			//select falling edge for next interrupt
			FTM0_C4SC &= (~FTM_CnSC_ELSA_MASK);
			FTM0_C4SC |= FTM_CnSC_ELSB_MASK;

		}
		else //If falling edge
		{
			//Store time
			sPwmInCh4FallTime = FTM0_C4V;

			//select rising edge for next interrupt
			FTM0_C4SC &= (~FTM_CnSC_ELSB_MASK);
			FTM0_C4SC |= FTM_CnSC_ELSA_MASK;

			//get width
			if(sPwmInCh4FallTime>sPwmInCh4RiseTime) //Normal
			{
				sPwmInCh4HighTime = sPwmInCh4FallTime - sPwmInCh4RiseTime;
			}
			else //Overflow
			{
				sPwmInCh4HighTime = sPwmInCh4FallTime + (65535-sPwmInCh4RiseTime);
			}

		}
	}

	// teste si flanc sur input capture channel 5
	if ((FTM0_C5SC &FTM_CnSC_CHF_MASK)==FTM_CnSC_CHF_MASK)
	{
		// Reset du flag
		FTM0_C5SC&=(~FTM_CnSC_CHF_MASK);

		//If rising edge
		if((FTM0_C5SC & FTM_CnSC_ELSA_MASK) == FTM_CnSC_ELSA_MASK)
		{
			//Store time
			sPwmInCh5RiseTime = FTM0_C5V;

			//select falling edge for next interrupt
			FTM0_C5SC &= (~FTM_CnSC_ELSA_MASK);
			FTM0_C5SC |= FTM_CnSC_ELSB_MASK;

		}
		else //If falling edge
		{
			//Store time
			sPwmInCh5FallTime = FTM0_C5V;

			//select rising edge for next interrupt
			FTM0_C5SC &= (~FTM_CnSC_ELSB_MASK);
			FTM0_C5SC |= FTM_CnSC_ELSA_MASK;

			//get width
			if(sPwmInCh5FallTime>sPwmInCh5RiseTime) //Normal
			{
				sPwmInCh5HighTime = sPwmInCh5FallTime - sPwmInCh5RiseTime;
			}
			else //Overflow
			{
				sPwmInCh5HighTime = sPwmInCh5FallTime + (65535-sPwmInCh5RiseTime);
			}

		}
	}

	// teste si flanc sur input capture channel 6
	if ((FTM0_C6SC &FTM_CnSC_CHF_MASK)==FTM_CnSC_CHF_MASK)
	{
		// Reset du flag
		FTM0_C6SC&=(~FTM_CnSC_CHF_MASK);

		//If rising edge
		if((FTM0_C6SC & FTM_CnSC_ELSA_MASK) == FTM_CnSC_ELSA_MASK)
		{
			//Store time
			sPwmInCh6RiseTime = FTM0_C6V;

			//select falling edge for next interrupt
			FTM0_C6SC &= (~FTM_CnSC_ELSA_MASK);
			FTM0_C6SC |= FTM_CnSC_ELSB_MASK;

		}
		else //If falling edge
		{
			//Store time
			sPwmInCh6FallTime = FTM0_C6V;

			//select rising edge for next interrupt
			FTM0_C6SC &= (~FTM_CnSC_ELSB_MASK);
			FTM0_C6SC |= FTM_CnSC_ELSA_MASK;

			//get width
			if(sPwmInCh6FallTime>sPwmInCh6RiseTime) //Normal
			{
				sPwmInCh6HighTime = sPwmInCh6FallTime - sPwmInCh6RiseTime;
			}
			else //Overflow
			{
				sPwmInCh6HighTime = sPwmInCh6FallTime + (65535-sPwmInCh6RiseTime);
			}

		}
	}

	// teste si flanc sur input capture channel 7
	if ((FTM0_C7SC &FTM_CnSC_CHF_MASK)==FTM_CnSC_CHF_MASK)
	{
		// Reset du flag
		FTM0_C7SC&=(~FTM_CnSC_CHF_MASK);

		//If rising edge
		if((FTM0_C7SC & FTM_CnSC_ELSA_MASK) == FTM_CnSC_ELSA_MASK)
		{
			//Store time
			sPwmInCh7RiseTime = FTM0_C7V;

			//select falling edge for next interrupt
			FTM0_C7SC &= (~FTM_CnSC_ELSA_MASK);
			FTM0_C7SC |= FTM_CnSC_ELSB_MASK;

		}
		else //If falling edge
		{
			//Store time
			sPwmInCh7FallTime = FTM0_C7V;

			//select rising edge for next interrupt
			FTM0_C7SC &= (~FTM_CnSC_ELSB_MASK);
			FTM0_C7SC |= FTM_CnSC_ELSA_MASK;

			//get width
			if(sPwmInCh7FallTime>sPwmInCh7RiseTime) //Normal
			{
				sPwmInCh7HighTime = sPwmInCh7FallTime - sPwmInCh7RiseTime;
			}
			else //Overflow
			{
				sPwmInCh7HighTime = sPwmInCh7FallTime + (65535-sPwmInCh7RiseTime);
			}

		}
	}


}

//------------------------------------------------------------
// Get a PWM input
//------------------------------------------------------------
UInt16 iFtm_ReadPwm(PwmInEnum aIn)
{
	UInt32 aVal = 0;

	switch(aIn)
	{
	case kPwmIn0:
		aVal = sPwmInCh0HighTime;
		break;

	case kPwmIn1:
		aVal = sPwmInCh1HighTime;
		break;

	case kPwmIn2:
		aVal = sPwmInCh2HighTime;
		break;

	case kPwmIn3:
		aVal = sPwmInCh3HighTime;
		break;

	case kPwmIn4:
		aVal = sPwmInCh4HighTime;
		break;

	case kPwmIn5:
		aVal = sPwmInCh5HighTime;
		break;

	case kPwmIn6:
		aVal = sPwmInCh6HighTime;
		break;

	case kPwmIn7:
		aVal = sPwmInCh7HighTime;
		break;

	default:
		break;
	}

	//Convert in uS instead of ticks.
	// We multiply by 32 and divide per 50 (=1/1.5625) to convert timer ticks in uS. 50=periph clock [MHz] and 32 is prescaler
	aVal = aVal * 32 / 50;

	//Constrain
	if(aVal>2000)
	{
		aVal = 2000;
	}
	else if(aVal<1000)
	{
		aVal= 1000;
	}
	aVal-=1000;
	return (UInt16) aVal;
}
