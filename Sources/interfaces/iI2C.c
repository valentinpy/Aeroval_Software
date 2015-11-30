/*
 * Copyright (C) 2015 Valentin Py
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

#include "iI2C.h"

//------------------------------------------------------------
// Configuration du module I2C
//------------------------------------------------------------
void iI2C_Config(void)
{
	//Send >8 clocks pulses to relesase the bus if the cpu crashed half-way through I2C communication

	//I2C0 & I2C2: SCL -> GPIO, output
	PORTA_PCR12&=(~PORT_PCR_MUX_MASK);
	PORTA_PCR12|=PORT_PCR_MUX(1);

	PORTE_PCR24&=(~PORT_PCR_MUX_MASK);
	PORTE_PCR24|=PORT_PCR_MUX(1);

	GPIOA_PDDR |= (0x1<<12);
	GPIOE_PDDR |= (0x1<<24);

	UInt8 i=0;
	for (i=0; i<20; i++)
	{
		//Toggles outputs
		GPIOA_PTOR |= (0x1<<12);
		GPIOE_PTOR |= (0x1<<24);
		UInt8 j=0;

		//Small delay
		for(j=0; j<0x8F; j++)
		{
			__asm("NOP");
		}
	}

	// I2C 0 & 2 clock enable
	// System Clock Gating Control Register 1&4 (SIM_SCGC1/SIM_SCGC4)
	SIM_SCGC1|=SIM_SCGC1_I2C2_MASK;
	SIM_SCGC4|=SIM_SCGC4_I2C0_MASK;

	// Port A I2C pin setup for I2C (alternate 5)
	// Pin Control Register n (PORTx_PCRn)
	PORTA_PCR12&=(~PORT_PCR_MUX_MASK);
	PORTA_PCR12|=PORT_PCR_MUX(5);
	PORTA_PCR13&=(~PORT_PCR_MUX_MASK);
	PORTA_PCR13|=PORT_PCR_MUX(5);

	// Port E I2C pin setup for I2C (alternate 5)
	// Pin Control Register n (PORTx_PCRn)
	PORTE_PCR24&=(~PORT_PCR_MUX_MASK);
	PORTE_PCR24|=PORT_PCR_MUX(5);
	PORTE_PCR25&=(~PORT_PCR_MUX_MASK);
	PORTE_PCR25|=PORT_PCR_MUX(5);


	// Baud rate speed and I2C timing
	// I2C Frequency Divider register (I2Cx_F)
	// I2C clock rate=375 kHz (max 400kHz)
	// Peripheral clock is divided by 128
	I2C0_F=0;
	I2C0_F|=I2C_F_ICR(0x1B)|I2C_F_MULT(0);

	I2C2_F=0;
	I2C2_F|=I2C_F_ICR(0x1B)|I2C_F_MULT(0);
}


//------------------------------------------------------------
// I2C interface enable
//------------------------------------------------------------
void iI2C_Enable(I2cEnum aI2c)
{
	// I2C0 enable
	// I2C Control Register 1 (I2Cx_C1)
	switch(aI2c)
	{
	case kI2c0:
		I2C0_C1 |= I2C_C1_IICEN_MASK;
		break;

	case kI2c2:
		I2C2_C1 |= I2C_C1_IICEN_MASK;
		break;
	}


}

//------------------------------------------------------------
// I2C interface disable
//------------------------------------------------------------
void iI2C_Disable(I2cEnum aI2c)
{
	// I2C0 disable
	// I2C Control Register 1 (I2Cx_C1)
	switch(aI2c)
	{
	case kI2c0:
		I2C0_C1 &= (~I2C_C1_IICEN_MASK);
		break;

	case kI2c2:
		I2C2_C1 &= (~I2C_C1_IICEN_MASK);
		break;
	}
}

//------------------------------------------------------------
// Set START state
//------------------------------------------------------------
void iI2C_SetStartState(I2cEnum aI2c)
{
	// I2C Control Register 1 (I2Cx_C1)
	switch(aI2c)
	{
	case kI2c0:
		I2C0_C1 |= I2C_C1_MST_MASK;
		break;

	case kI2c2:
		I2C2_C1 |= I2C_C1_MST_MASK;
		break;
	}
}

//------------------------------------------------------------
// Set repeated START state
//------------------------------------------------------------
void iI2C_SetRepeatedStartSate(I2cEnum aI2c)
{
	// I2C Control Register 1 (I2Cx_C1)
	switch(aI2c)
	{
	case kI2c0:
		I2C0_C1 |= I2C_C1_RSTA_MASK;
		break;

	case kI2c2:
		I2C0_C1 |= I2C_C1_RSTA_MASK;
		break;
	}
}

//------------------------------------------------------------
// Set STOP state
//------------------------------------------------------------
void iI2C_SetStopState(I2cEnum aI2c)
{
	// I2C Control Register 1 (I2Cx_C1)
	switch(aI2c)
	{
	case kI2c0:
		I2C0_C1 &= (~I2C_C1_MST_MASK);
		break;

	case kI2c2:
		I2C2_C1 &= (~I2C_C1_MST_MASK);
		break;
	}
}

//------------------------------------------------------------
// Generate automatic ACK or not
//------------------------------------------------------------
void iI2C_SetAckMode(I2cEnum aI2c, I2CAckEnum aAck)
{
	switch(aI2c)
	{
	case kI2c0:
		if (aAck == kAckAuto)
		{
			// I2C Control Register 1 (I2Cx_C1)
			I2C0_C1 &= (~I2C_C1_TXAK_MASK);
		}
		else if (aAck == kNoAck)
		{
			// I2C Control Register 1 (I2Cx_C1)
			I2C0_C1 |= I2C_C1_TXAK_MASK;
		}
		break;

	case kI2c2:
		if (aAck == kAckAuto)
		{
			// I2C Control Register 1 (I2Cx_C1)
			I2C2_C1 &= (~I2C_C1_TXAK_MASK);
		}
		else if (aAck == kNoAck)
		{
			// I2C Control Register 1 (I2Cx_C1)
			I2C2_C1 |= I2C_C1_TXAK_MASK;
		}
		break;
	}



}

//------------------------------------------------------------
// Select if we transmit or receive
//------------------------------------------------------------
void iI2C_TxRxSelect(I2cEnum aI2c, I2CTransmiteModeEnum aMode)
{
	switch(aI2c)
	{
	case kI2c0:
		if (kTxMode == aMode)
		{
			// TX
			I2C0_C1 |= I2C_C1_TX_MASK;
		}
		else if (kRxMode == aMode)
		{
			// RX
			I2C0_C1 &= ~I2C_C1_TX_MASK;
		}
		break;

	case kI2c2:
		if (kTxMode == aMode)
		{
			// TX
			I2C2_C1 |= I2C_C1_TX_MASK;
		}
		else if (kRxMode == aMode)
		{
			// RX
			I2C2_C1 &= ~I2C_C1_TX_MASK;
		}
		break;
	}
}

//------------------------------------------------------------
// Send a data
//------------------------------------------------------------
void iI2C_SendData(I2cEnum aI2c, UInt8 aData)
{
	// I2C Data I/O register (I2Cx_D)
	switch(aI2c)
	{
	case kI2c0:
		I2C0_D = aData;
		break;

	case kI2c2:
		I2C0_D = aData;
		break;
	}
}

//------------------------------------------------------------
// Wait End of transmit or receive
//------------------------------------------------------------
void iI2C_WaitEndOfRxOrTx(I2cEnum aI2c)
{
	// Wait for IICIF flag
	switch(aI2c)
	{
	case kI2c0:
		// I2C Status register (I2Cx_S)
		while ((I2C0_S & I2C_S_IICIF_MASK) == 0);
		// Clear the IICIF flag
		I2C0_S |= I2C_S_IICIF_MASK;
		break;

	case kI2c2:
		// I2C Status register (I2Cx_S)
		while ((I2C2_S & I2C_S_IICIF_MASK) == 0);
		// Clear the IICIF flag
		I2C2_S |= I2C_S_IICIF_MASK;
		break;
	}
}

//------------------------------------------------------------
// Read received data, ! generate I2C clock if not in STOP mode
//------------------------------------------------------------
UInt8 iI2C_ReadData(I2cEnum aI2c)
{
	UInt8 aReturnData = 0;

	switch(aI2c)
	{
	case kI2c0:
		// I2C Data I/O register (I2Cx_D)
		aReturnData = I2C0_D;
		break;

	case kI2c2:
		// I2C Data I/O register (I2Cx_D)
		aReturnData = I2C2_D;
		break;
	}

	return aReturnData;
}

//------------------------------------------------------------
// Get I2C status flags
//------------------------------------------------------------
bool iI2C_ReadStatus(I2cEnum aI2c, I2CStatusEnum aStatus)
{
	bool aReturnData=false;
	switch(aI2c)
	{
	case kI2c0:
		aReturnData = (bool)(((I2C0_S&aStatus)==aStatus));
		break;

	case kI2c2:
		aReturnData = (bool)(((I2C2_S&aStatus)==aStatus));
		break;
	}
	return aReturnData;
}
