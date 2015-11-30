/*
 * Copyright (C) 2015 Valentin Py
 * Copyright (C) 2015 Maurice Billmann
 * Copyright (C) 2015 Timithée Fivaz
 * Copyright (C) 2015 Serge Monnerat
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

#include "iCpu.h"

// Peripherals clock init
static void iCpu_PeriphClkInit(void);

// Core and peripheral clock init
static void iCpu_PllInit(void);

// K64 pin functions configuration
static void iCpu_PinFctCfg(void);

//------------------------------------------------------------
// Core and peripheral clock init
// External clock = 8MHz 	(20MHz)
// Core clock = 100MHz		(100MHz)
// Peripheral bus = 50MHz	(50MHz)
// Flexbus = 50MHz
// Flash = 25MHz
//------------------------------------------------------------
static void iCpu_PllInit(void) {
		// If the internal load capacitors are being used, they should be selected
		// before enabling the oscillator. Application specific. 16pF and 8pF selected
		// in this example
		//OSC_CR = OSC_CR_SC16P_MASK | OSC_CR_SC8P_MASK;

		// Enable external oscillator, RANGE=2, HGO=1, EREFS=1, LP=0, IRCS=0
		MCG_C2 = MCG_C2_RANGE0(2) | MCG_C2_HGO0_MASK | MCG_C2_EREFS0_MASK;

		// after initialization of oscillator release latched state of oscillator and GPIO
		//SIM_SCGC4 |= SIM_SCGC4_LLWU_MASK;
		//LLWU_CS |= LLWU_CS_ACKISO_MASK;

		// Select external oscilator and Reference Divider and clear IREFS to start ext osc
		// CLKS=2, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
		MCG_C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);

		// Wait for oscillator to initialize
		while (!(MCG_S & MCG_S_OSCINIT0_MASK));

		// Wait for Reference clock Status bit to clear
		while (MCG_S & MCG_S_IREFST_MASK);

		// Wait for clock status bits to show clock source is ext ref clk
		while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2);

		// Now in FBE

		// Configure PLL Ref Divider, PLLCLKEN=0, PLLSTEN=0, PRDIV=5
		// The crystal frequency is used to select the PRDIV value. Only even frequency crystals are supported
		// that will produce a 2MHz reference clock to the PLL.
		// 3 = divide factor -> 4 --> 8MHz/4 = 2MHz
		MCG_C5 = MCG_C5_PRDIV0(3);

		// Ensure MCG_C6 is at the reset default of 0. LOLIE disabled, PLL disabled, clk monitor disabled, PLL VCO divider is clear
		//MCG_C6 = 0x0;

		// Set the VCO divider and enable the PLL for 100MHz, LOLIE=0, PLLS=1, CME=0, VDIV=26 (2MHz * 50)
		MCG_C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV0(26);

		// Wait for PLL status bit to set
		while (!(MCG_S & MCG_S_PLLST_MASK));

		// Wait for LOCK bit to set
		while (!(MCG_S & MCG_S_LOCK0_MASK));

		// Set up the SIM clock dividers BEFORE switching to the PLL to ensure the
		// system clock speeds are in spec.
		// core = PLL (100MHz), bus = PLL/2 (50MHz), flexbus = PLL/2 (50MHz), flash = PLL/4 (25MHz)
		SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(1)| SIM_CLKDIV1_OUTDIV3(1) | SIM_CLKDIV1_OUTDIV4(3);

		// Now running PBE Mode

		// Transition into PEE by setting CLKS to 0
		// CLKS=0, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
		MCG_C1 &= ~MCG_C1_CLKS_MASK;

		// Wait for clock status bits to update
		while (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3);

		// Now running PEE Mode

		// Set the trace clock to the core clock frequency
		SIM_SOPT2 |= SIM_SOPT2_TRACECLKSEL_MASK;

		// Enable the clock to the FlexBus module
		SIM_SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;
}

//------------------------------------------------------------
// K10 pin functions configuration
//------------------------------------------------------------
static void iCpu_PinFctCfg(void) {
//	// PTB21 --> LEDRGB_BLUE
//	PORTB_PCR21 = 0|PORT_PCR_PS_MASK|PORT_PCR_PE_MASK|PORT_PCR_DSE_MASK|(PORT_PCR_MUX(0x1));
}

//------------------------------------------------------------
// Peripherals clock init
//------------------------------------------------------------
void iCpu_PeriphClkInit(void) {
	// K60 Sub-Family Reference Manual, Rev. 2, January 2014 page 314
	// System Clock Gating Control Register 5 (SIM_SCGC5)
	// PORTA,PORTA,PORTB,PORTC,PORTD clock enable
	// LPTMR clock disable
	SIM_SCGC5 |=
			(SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK
					| SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK);


	// K60 Sub-Family Reference Manual, Rev. 2, January 2014 page 319
	// System Clock Gating Control Register 7 (SIM_SCGC7)
	// Clock enable for MPU,DMA, FLEXBUS
	SIM_SCGC7 |= (SIM_SCGC7_DMA_MASK | SIM_SCGC7_FLEXBUS_MASK
			| SIM_SCGC7_MPU_MASK);

}

//------------------------------------------------------------
// CPU configuration
//------------------------------------------------------------
void iCpu_SysInit(void) {

	// Peripherals clock init
	iCpu_PeriphClkInit();

	// Disable MPU
	MPU_CESR &= (~MPU_CESR_VLD_MASK);

	// Core and peripheral clock init
	iCpu_PllInit();

	// K10 pin functions configuration
	iCpu_PinFctCfg();
}
