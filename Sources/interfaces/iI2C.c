/*
------------------------------------------------------------
Copyright 2003-20xx Haute Ècole ARC IngÈniÈrie, Switzerland.
All rights reserved.
------------------------------------------------------------
Nom du fichier :	iI2C.c
Auteur et Date :	Monnerat Serge 8.5.20xx

Description dans le fichier iI2C.h
------------------------------------------------------------
 */

#include "iI2C.h"

//------------------------------------------------------------
// Configuration du module I2C
//------------------------------------------------------------
void iI2C_Config(void)
{

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
