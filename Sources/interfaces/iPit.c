/*
 * Copyright (C) 2015 Valentin Py
 * Copyright (C) 2015 Thimothée Fivaz
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

#include "iPit.h"

UInt32 sTicker100Us[kNbTickers100Us];


//------------------------------------------------------------
// PIT setup
// aPit					: which PIT (0 to 3)
// aPeriodeMs  	: PIT period in ms
//------------------------------------------------------------
void iPit_Config(PitEnum aPit, UInt16 aPeriodeUs)
{
	//Initialize tickers to 0
	int i;
	for(i=0; i< kNbTickers100Us; i++)
	{
		sTicker100Us[i]=0;
	}

	//Config PIT
	static UInt32 aTmp = 0;

	// Enable du clock du p�riph�rique PIT
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

	// PIT Module Control Register (PIT_MCR)
	// --> Timers are stopped in debug mode
	PIT_MCR |= PIT_MCR_FRZ_MASK;

	// PIT interrupts setup
	if (aPit == kPit0)
	{
		// Counting value to do the delay
		// Counting Value=Delay Time/(1/Core clock)
		aTmp = ((aPeriodeUs / (1 / kClockBus))) - 1;

		// Timer Load Value Register (PIT_LDVALn)
		PIT_LDVAL0 =aTmp;

		// Timer Control Register (PIT_TCTRLn)
		// Enable PIT interrupt
		PIT_TCTRL0 |=PIT_TCTRL_TIE_MASK;
		// Enable de l'interrupt
		//enable_irq(INT_PIT0-16);

		//enable_irq PIT0
		// Clear prending interrupt for PIT0
		NVIC_ClearPendingIRQ(PIT0IRQ);

		// Interrupt enable for PIT0
		NVIC_EnableIRQ(PIT0IRQ);

		// Set interrupt priority for PIT0
		NVIC_SetPriority(PIT0IRQ, 0);
	}
	else if(aPit==kPit1)
	{
		// Counting value to do the delay
		// Counting Value=Delay Time/(1/Core clock)
		aTmp = ((aPeriodeUs / (1 / kClockBus))) - 1;

		// Timer Load Value Register (PIT_LDVALn)
		PIT_LDVAL1=aTmp;

		// Timer Control Register (PIT_TCTRLn)
		// Enable PIT interrupt
		PIT_TCTRL1|=PIT_TCTRL_TIE_MASK;
		// IRQ bit offset in the following registers
		aTmp=69%32;

		// Enable de l'interrupt
		//enable_irq(INT_PIT1-16);

		//enable_irq PIT1
		// Clear prending interrupt for PIT1
		NVIC_ClearPendingIRQ(PIT1IRQ);

		// Interrupt enable for PIT1
		NVIC_EnableIRQ(PIT1IRQ);

		// Set interrupt priority for PIT1
		NVIC_SetPriority(PIT1IRQ, 0);
	}
	else if(aPit==kPit2)
	{
		// Counting value to do the delay
		// Counting Value=Delay Time/(1/Core clock)
		aTmp = ((aPeriodeUs / (1 / kClockBus))) - 1;

		// Timer Load Value Register (PIT_LDVALn)
		PIT_LDVAL2=aTmp;

		// Timer Control Register (PIT_TCTRLn)
		// Enable PIT interrupt
		PIT_TCTRL2|=PIT_TCTRL_TIE_MASK;
		// Enable de l'interrupt
		//enable_irq(INT_PIT2-16);

		//enable_irq PIT2
		// Clear prending interrupt for PIT2
		NVIC_ClearPendingIRQ(PIT2IRQ);

		// Interrupt enable for PIT2
		NVIC_EnableIRQ(PIT2IRQ);

		// Set interrupt priority for PIT2
		NVIC_SetPriority(PIT2IRQ, 0);
	}
	else if(aPit==kPit3)
	{
		// Counting value to do the delay
		// Counting Value=Delay Time/(1/Core clock)
		aTmp = ((aPeriodeUs / (1 / kClockBus))) - 1;

		// Timer Load Value Register (PIT_LDVALn)
		PIT_LDVAL3=aTmp;

		// Timer Control Register (PIT_TCTRLn)
		// Enable PIT interrupt
		PIT_TCTRL3|=PIT_TCTRL_TIE_MASK;
		// Enable de l'interrupt
		//enable_irq(INT_PIT3-16);

		//enable_irq PIT3
		// Clear prending interrupt for PIT3
		NVIC_ClearPendingIRQ(PIT3IRQ);

		// Interrupt enable for PIT3
		NVIC_EnableIRQ(PIT3IRQ);

		// Set interrupt priority for PIT3
		NVIC_SetPriority(PIT3IRQ, 0);
	}

	// Clock for PIT Timers is enabled
	PIT_MCR &= (~PIT_MCR_MDIS_MASK);
}

//------------------------------------------------------------
// Start Pit
// aPit		: which PIT
//------------------------------------------------------------
void iPit_StartPit(PitEnum aPit)
{
	// Start PIT
	if (aPit == kPit0)
	{
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 1018
		// Timer Control Register (PIT_TCTRLn)
		// Timer is active
		PIT_TCTRL0 |=PIT_TCTRL_TEN_MASK;
	}
	else if(aPit==kPit1)
	{
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 1018
		// Timer Control Register (PIT_TCTRLn)
		// Timer is active
		PIT_TCTRL1|=PIT_TCTRL_TEN_MASK;
	}
	else if(aPit==kPit2)
	{
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 1018
		// Timer Control Register (PIT_TCTRLn)
		// Timer is active
		PIT_TCTRL2|=PIT_TCTRL_TEN_MASK;
	}
	else if(aPit==kPit3)
	{
		// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 1018
		// Timer Control Register (PIT_TCTRLn)
		// Timer is active
		PIT_TCTRL3|=PIT_TCTRL_TEN_MASK;
	}
}

//------------------------------------------------------------
// Setup the delay structure
// aPit		: which PIT
//------------------------------------------------------------
void iPit_InitDelay(PitEnum aPit)
{
	UInt16 i = 0;

	for (i = 0; i < kNbDelays; i++)
	{
		sDly[aPit].CounterTab[i].DelayDone = false;
		sDly[aPit].CounterTab[i].Counter = 0;
		sDly[aPit].CounterTab[i].isFree = true;
	}
}

//------------------------------------------------------------
// Get and setup a delay
// aPit		: which PIT
// aDelay	: the delay (ms)
// Retour	: the delay number
//------------------------------------------------------------
Int16 iPit_GetDelay(PitEnum aPit, UInt16 aDelay)
{
	Int16 aDelayNb = 0;
	UInt16 i = 0;

	// By default
	aDelayNb = 0;

	// Find and configure a free delay
	for (i = 0;
			(i < kNbDelays) && (false == sDly[aPit].CounterTab[i].isFree);
			i++, aDelayNb = i)
		;

	// Check if a delay was found
	if ((i == kNbDelays) && (false == sDly[aPit].CounterTab[i - 1].isFree))
		aDelayNb = -1;
	else
	{
		// Delay setup
		sDly[aPit].CounterTab[aDelayNb].isFree = false;
		sDly[aPit].CounterTab[aDelayNb].Counter = aDelay;
		sDly[aPit].CounterTab[aDelayNb].DelayDone = false;
	}

	return aDelayNb;
}

//------------------------------------------------------------
// Check if the delay is done
// aPit			: which PIT
// aDelayNb	: the delay number
// Retour		: state of the delay
//------------------------------------------------------------
bool iPit_IsDelayDone(PitEnum aPit, UInt16 aDelayNb)
{
	return sDly[aPit].CounterTab[aDelayNb].DelayDone;
}

//------------------------------------------------------------
// Release a delay
// aPit			: which PIT
// aDelayNb	: the delay number
//------------------------------------------------------------
void iPit_DelayRelease(PitEnum aPit, UInt16 aDelayNb)
{
	sDly[aPit].CounterTab[aDelayNb].DelayDone = false;
	sDly[aPit].CounterTab[aDelayNb].Counter = 0;
	sDly[aPit].CounterTab[aDelayNb].isFree = true;
}

//------------------------------------------------------------
// Restart un delay
// aPit			: which PIT
// aDelayNb	: the delay number
// aDelay		: the delay time
//------------------------------------------------------------
void iPit_ReStart(PitEnum aPit, UInt16 aDelayNb, UInt16 aDelay)
{
	sDly[aPit].CounterTab[aDelayNb].DelayDone = false;
	sDly[aPit].CounterTab[aDelayNb].Counter = aDelay;
	sDly[aPit].CounterTab[aDelayNb].isFree = false;
}

//------------------------------------------------------------
// PIT 0 interrupt routine
//------------------------------------------------------------
void PIT0_IRQHandler(void)
{
	UInt16 i=0;
	UInt32 aTmp;

	// PIT TIF flag clear
	PIT_TFLG0|=PIT_TFLG_TIF_MASK;
	// ! errata e2682 !
	// Workaround: In order to enable the use of subsequent interrupts from the PIT, the user must access any PIT
	// register after clearing the interrupt flag in the ISR.?
	aTmp=PIT_CVAL0;

	// Counter update
	for(i=0;i<kNbDelays;i++)
	{
		if((false==sDly[kPit0].CounterTab[i].isFree)&&(sDly[kPit0].CounterTab[i].Counter>0))
			sDly[kPit0].CounterTab[i].Counter--;

		if((false==sDly[kPit0].CounterTab[i].isFree)&&(sDly[kPit0].CounterTab[i].Counter==0))
			sDly[kPit0].CounterTab[i].DelayDone=true;
	}
}

//------------------------------------------------------------
// PIT 1 interrupt routine
//------------------------------------------------------------
void PIT1_IRQHandler(void)
{
	UInt16 i = 0;
	UInt32 aTmp;

	// PIT TIF flag clear
	PIT_TFLG1 |=PIT_TFLG_TIF_MASK;
	// ! errata e2682 !
	// Workaround: In order to enable the use of subsequent interrupts from the PIT, the user must access any PIT
	// register after clearing the interrupt flag in the ISR.?
	aTmp = PIT_CVAL1 ;

	// Counter update
	for (i = 0; i < kNbTickers100Us; i++)
	{
		sTicker100Us[i]++;
	}
}

//------------------------------------------------------------
// PIT 2 interrupt routine
//------------------------------------------------------------
void PIT2_IRQHandler(void)
{
	UInt16 i = 0;
	UInt32 aTmp;

	// PIT TIF flag clear
	PIT_TFLG2 |=PIT_TFLG_TIF_MASK;
	// ! errata e2682 !
	// Workaround: In order to enable the use of subsequent interrupts from the PIT, the user must access any PIT
	// register after clearing the interrupt flag in the ISR.?
	aTmp = PIT_CVAL2 ;

	// Counter update
	for (i = 0; i < kNbDelays; i++)
	{
		if ((false == sDly[kPit2].CounterTab[i].isFree)
				&& (sDly[kPit2].CounterTab[i].Counter > 0))
			sDly[kPit2].CounterTab[i].Counter--;

		if ((false == sDly[kPit2].CounterTab[i].isFree)
				&& (sDly[kPit2].CounterTab[i].Counter == 0))
			sDly[kPit2].CounterTab[i].DelayDone = true;
	}
}

//------------------------------------------------------------
// PIT 3 interrupt routine
//------------------------------------------------------------
void PIT3_IRQHandler(void)
{
	UInt16 i = 0;
	UInt32 aTmp;

	// PIT TIF flag clear
	PIT_TFLG3 |=PIT_TFLG_TIF_MASK;
	// ! errata e2682 !
	// Workaround: In order to enable the use of subsequent interrupts from the PIT, the user must access any PIT
	// register after clearing the interrupt flag in the ISR.?
	aTmp = PIT_CVAL3 ;

	// Counter update
	for (i = 0; i < kNbDelays; i++)
	{
		if ((false == sDly[kPit3].CounterTab[i].isFree)
				&& (sDly[kPit3].CounterTab[i].Counter > 0))
			sDly[kPit3].CounterTab[i].Counter--;

		if ((false == sDly[kPit3].CounterTab[i].isFree)
				&& (sDly[kPit3].CounterTab[i].Counter == 0))
			sDly[kPit3].CounterTab[i].DelayDone = true;
	}
}
