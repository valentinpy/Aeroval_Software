/*
 * Copyright (C) 2015-2016 Valentin Py
 * Copyright (C) 2015-2016 Serge Monnerat
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


static void iI2C_Disable(I2cEnum aI2c);
static void iI2C_SetStartState(I2cEnum aI2c);
static void iI2C_SetRepeatedStartSate(I2cEnum aI2c);
static void iI2C_SetStopState(I2cEnum aI2c);
static void iI2C_SetAckMode(I2cEnum aI2c, I2CAckEnum aAck);
static void iI2C_TxRxSelect(I2cEnum aI2c, I2CTransmiteModeEnum aMode);
static void iI2C_SendData(I2cEnum aI2c, UInt8 aData);
static void iI2C_WaitEndOfRxOrTx(I2cEnum aI2c);
static UInt8 iI2C_ReadData(I2cEnum aI2c);
static bool iI2C_ReadStatus(I2cEnum aI2c, I2CStatusEnum aStatus);



//------------------------------------------------------------
// Configuration du module I2C
//------------------------------------------------------------
void iI2C_Config(void)
{
	//Send >8 clocks pulses to release the bus if the cpu crashed half-way through I2C communication

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

		//Small delay
		UInt8 j=0;
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
	//I2C0_F=0;
	//I2C0_F|=I2C_F_ICR(0x11)|I2C_F_MULT(0);

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
static void iI2C_Disable(I2cEnum aI2c)
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
static void iI2C_SetStartState(I2cEnum aI2c)
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
static void iI2C_SetRepeatedStartSate(I2cEnum aI2c)
{
	// I2C Control Register 1 (I2Cx_C1)
	switch(aI2c)
	{
	case kI2c0:
		I2C0_C1 |= I2C_C1_RSTA_MASK;
		break;

	case kI2c2:
		I2C2_C1 |= I2C_C1_RSTA_MASK;
		break;
	}
}

//------------------------------------------------------------
// Set STOP state
//------------------------------------------------------------
static void iI2C_SetStopState(I2cEnum aI2c)
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
static void iI2C_SetAckMode(I2cEnum aI2c, I2CAckEnum aAck)
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
static void iI2C_TxRxSelect(I2cEnum aI2c, I2CTransmiteModeEnum aMode)
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
static void iI2C_SendData(I2cEnum aI2c, UInt8 aData)
{
	// I2C Data I/O register (I2Cx_D)
	switch(aI2c)
	{
	case kI2c0:
		I2C0_D = aData;
		break;

	case kI2c2:
		I2C2_D = aData;
		break;
	}
}

//------------------------------------------------------------
// Wait End of transmit or receive
//------------------------------------------------------------
static void iI2C_WaitEndOfRxOrTx(I2cEnum aI2c)
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
static UInt8 iI2C_ReadData(I2cEnum aI2c)
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
static bool iI2C_ReadStatus(I2cEnum aI2c, I2CStatusEnum aStatus)
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

//-------------------------------------------------------------------
// Send a byte to aAddr_W over I2C
// aAddr_W: Address of the device (Write)
// aReg: register to write into
// aVal: value to write in aReg
// return: true: write successful, false: error when writing
//-------------------------------------------------------------------
bool iI2C_SetData8(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg, UInt8 aVal)
{
	bool aNoAck=false;

	// Disable transmit ACK
	iI2C_SetAckMode(aI2c, kNoAck);

	// Attend que le bus soit libre
	while(true==iI2C_ReadStatus(aI2c, kBUSY));

	//-----------------------------------------------------------------------------
	// D'abords en WRITE afin de transmettre le registre
	// que l'on veut lire ainsi que l'adresse du slave
	//-----------------------------------------------------------------------------

	// DÃ©but de la transmission --> mode write et START condition
	iI2C_TxRxSelect(aI2c, kTxMode);
	iI2C_SetStartState(aI2c);

	// Transmission de l'adresse en WRITE du slave dans le registre de donnÃ©es
	// --> obligatoire protocolle I2C, le slave doit d'abords rÃ©pondre Ã  son adresse
	iI2C_SendData(aI2c, aAddr_W);


	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return false;
	}


	// Transmission de l'adresse du registre que l'on veut Ã©crire
	iI2C_SendData(aI2c, aReg);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return false;
	}


	// Transmission de la donnÃ©e que l'on veut Ã©crire dans le registre
	iI2C_SendData(aI2c, aVal);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	// FIN de la lecture
	iI2C_TxRxSelect(aI2c, kTxMode);
	iI2C_SetAckMode(aI2c, kNoAck);
	iI2C_SetStopState(aI2c);
	if(aNoAck==true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//-----------------------------------------------------------------------------
// Read one register (8 bits) from sensor
// aReg:    Address of the register we want to read
// aAddr_W:	Address of the device (Write)
// Return:	Value of the requested register
//-----------------------------------------------------------------------------
UInt8 iI2C_GetData8(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg)
{
	bool aNoAck=false;

	// Disable transmit ACK
	iI2C_SetAckMode(aI2c, kNoAck);

	// Attend que le bus soit libre
	while(true==iI2C_ReadStatus(aI2c, kBUSY));

	//-----------------------------------------------------------------------------
	// D'abords en WRITE afin de transmettre le registre
	// que l'on veut lire ainsi que l'adresse du slave
	//-----------------------------------------------------------------------------

	// DÃ©but de la transmission --> mode write et START condition
	iI2C_TxRxSelect(aI2c, kTxMode);
	iI2C_SetStartState(aI2c);

	// Transmission de l'adresse en WRITE du slave dans le registre de donnÃ©es
	// --> obligatoire protocolle I2C, le slave doit d'abords rÃ©pondre Ã  son adresse
	iI2C_SendData(aI2c, aAddr_W);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return 0;
	}

	// Transmission de l'adresse du registre que l'on veut lire
	iI2C_SendData(aI2c, aReg);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return 0;
	}

	// Nouvelle condition START
	iI2C_SetRepeatedStartSate(aI2c);

	//-----------------------------------------------------------------------------
	// Passage en READ
	//-----------------------------------------------------------------------------

	// Transmission de l'adresse en READ du slave dans le registre de donnÃ©es
	// --> obligatoire protocolle I2C, le slave doit d'abords rÃ©pondre Ã  son adresse
	iI2C_SendData(aI2c, aAddr_W+1);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return 0;
	}

	// Passage en mode READ
	// --> En lecture c'est au master d'envoyer le ACK mais comme on
	// lit q'un byte pas besoin de ACK
	//iI2C_EnableTxAck();
	iI2C_TxRxSelect(aI2c, kRxMode);

	// Lecture qui ne sert Ã  rien --> permet l'Ã©mission de l'horloge nÃ©cessaire au
	// slave afin de transmettre sa donnÃ©e
	iI2C_ReadData(aI2c);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// FIN de la lecture
	// GÃ©nÃ©ration de la condition STOP
	// Obligatoire de faire le STOP avant la lecture pour
	// ne pas Ã©mettre de clock Ã  nouveau!
	iI2C_TxRxSelect(aI2c, kTxMode);
	iI2C_SetAckMode(aI2c, kNoAck);
	iI2C_SetStopState(aI2c);

	// Lecture de la valeur du registre demandÃ©
	return iI2C_ReadData(aI2c);
}

//-----------------------------------------------------------------------------
// Read two registers (8 bits) from sensor
// aReg:    Address of the register we want to read
// aAddr_W:	Address of the device (Write)
// Return:	Value of the requested register
//-----------------------------------------------------------------------------
UInt16 iI2C_GetData16(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg)
{
	bool aNoAck=false;
	UInt16 aRet=0;


	// Disable transmit ACK
	iI2C_SetAckMode(aI2c, kNoAck);

	// Attend que le bus soit libre
	while(true==iI2C_ReadStatus(aI2c, kBUSY));

	//-----------------------------------------------------------------------------
	// D'abords en WRITE afin de transmettre le registre
	// que l'on veut lire ainsi que l'adresse du slave
	//-----------------------------------------------------------------------------

	// DÃ©but de la transmission --> mode write et START condition
	iI2C_TxRxSelect(aI2c, kTxMode);
	iI2C_SetStartState(aI2c);

	// Transmission de l'adresse en WRITE du slave dans le registre de donnÃ©es
	// --> obligatoire protocolle I2C, le slave doit d'abords rÃ©pondre Ã  son adresse
	iI2C_SendData(aI2c, aAddr_W);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return 0;
	}

	// Transmission de l'adresse du registre que l'on veut lire
	iI2C_SendData(aI2c, aReg);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return 0;
	}

	// Nouvelle condition START
	iI2C_SetRepeatedStartSate(aI2c);

	//-----------------------------------------------------------------------------
	// Passage en READ
	//-----------------------------------------------------------------------------

	// Transmission de l'adresse en READ du slave dans le registre de donnÃ©es
	// --> obligatoire protocolle I2C, le slave doit d'abords rÃ©pondre Ã  son adresse
	iI2C_SendData(aI2c, aAddr_W+1);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return 0;
	}

	// Passage en mode READ
	// --> En lecture c'est au master d'envoyer le ACK
	iI2C_SetAckMode(aI2c, kAckAuto);
	iI2C_TxRxSelect(aI2c, kRxMode);

	// Lecture qui ne sert à  rien --> permet l'émission de l'horloge nécessaire au slave afin de transmettre sa donnée
	iI2C_ReadData(aI2c);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	iI2C_SetAckMode(aI2c, kNoAck);
	aRet = iI2C_ReadData(aI2c);
	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// FIN de la lecture
	// Génération de la condition STOP
	// Obligatoire de faire le STOP avant la lecture pour
	// ne pas émettre de clock à nouveau!
	iI2C_TxRxSelect(aI2c, kTxMode);
	iI2C_SetAckMode(aI2c, kNoAck);
	iI2C_SetStopState(aI2c);

	// Lecture de la dernière valeur du registre demandé
	aRet +=  (iI2C_ReadData(aI2c)<<8);

	return aRet;
}


//-----------------------------------------------------------------------------
// Read aLength registers (8 bits) from sensor
// aReg:    Address of the register we want to read
// aAddr_W:	Address of the device (Write)
// aLength: Number of bytes to read
// aRet*:	Pointer to return the data, must be big enough, according to aLength
// Return:	true if success, false else
//-----------------------------------------------------------------------------
bool iI2C_GetData(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg, UInt8 aLength, UInt8 *aRetData)
{
	bool aNoAck=false;
	bool aRet=true; //TODO Security: handle errors

	// Disable transmit ACK
	iI2C_SetAckMode(aI2c, kNoAck);

	// Attend que le bus soit libre
	while(true==iI2C_ReadStatus(aI2c, kBUSY));

	//-----------------------------------------------------------------------------
	// D'abords en WRITE afin de transmettre le registre
	// que l'on veut lire ainsi que l'adresse du slave
	//-----------------------------------------------------------------------------

	// DÃ©but de la transmission --> mode write et START condition
	iI2C_TxRxSelect(aI2c, kTxMode);
	iI2C_SetStartState(aI2c);

	// Transmission de l'adresse en WRITE du slave dans le registre de donnÃ©es
	// --> obligatoire protocolle I2C, le slave doit d'abords rÃ©pondre Ã  son adresse
	iI2C_SendData(aI2c, aAddr_W);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return 0;
	}

	// Transmission de l'adresse du registre que l'on veut lire
	iI2C_SendData(aI2c, aReg);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return 0;
	}

	// Nouvelle condition START
	iI2C_SetRepeatedStartSate(aI2c);

	//-----------------------------------------------------------------------------
	// Passage en READ
	//-----------------------------------------------------------------------------

	// Transmission de l'adresse en READ du slave dans le registre de donnÃ©es
	// --> obligatoire protocolle I2C, le slave doit d'abords rÃ©pondre Ã  son adresse
	iI2C_SendData(aI2c, aAddr_W+1);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(aI2c);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(aI2c, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);
		return 0;
	}

	if(aLength==1)
	{
			// Passage en mode READ
			// --> En lecture c'est au master d'envoyer le ACK mais comme on
			// lit q'un byte pas besoin de ACK
			//iI2C_EnableTxAck();
			iI2C_TxRxSelect(aI2c, kRxMode);

			// Lecture qui ne sert à rien --> permet l'émission de l'horloge nécessaire slave afin de transmettre sa donnée
			iI2C_ReadData(aI2c);

			// Attend la fin de la transmission
			iI2C_WaitEndOfRxOrTx(aI2c);

			// FIN de la lecture
			// Génération de la condition STOP
			// Obligatoire de faire le STOP avant la lecture pour
			// ne pas émettre de clock à nouveau!
			iI2C_TxRxSelect(aI2c, kTxMode);
			iI2C_SetAckMode(aI2c, kNoAck);
			iI2C_SetStopState(aI2c);

			// Lecture de la valeur du registre demandée
			*aRetData = iI2C_ReadData(aI2c);
	}
	else if(aLength>=1)
	{
		// Passage en mode READ
		// --> En lecture c'est au master d'envoyer le ACK
		iI2C_SetAckMode(aI2c, kAckAuto);
		iI2C_TxRxSelect(aI2c, kRxMode);

		// Lecture qui ne sert à  rien --> permet l'émission de l'horloge nécessaire au slave afin de transmettre sa donnée
		iI2C_ReadData(aI2c);

		// Attend la fin de la transmission
		iI2C_WaitEndOfRxOrTx(aI2c);

		//iI2C_SetAckMode(aI2c, kNoAck);

		//Reading first bytes
		for(UInt8 i=0; i<(aLength-2); i++)
		{
			*(aRetData+i) = iI2C_ReadData(aI2c);

			// Attend la fin de la transmission
			iI2C_WaitEndOfRxOrTx(aI2c);
		}

		iI2C_SetAckMode(aI2c, kNoAck);
		*(aRetData+aLength-2) = iI2C_ReadData(aI2c);
		// Attend la fin de la transmission
		iI2C_WaitEndOfRxOrTx(aI2c);

		// FIN de la lecture
		// Génération de la condition STOP
		// Obligatoire de faire le STOP avant la lecture pour
		// ne pas émettre de clock à nouveau!
		iI2C_TxRxSelect(aI2c, kTxMode);
		iI2C_SetAckMode(aI2c, kNoAck);
		iI2C_SetStopState(aI2c);

		// Lecture de la dernière valeur du registre demandé
		*(aRetData+aLength-1) =  iI2C_ReadData(aI2c);

	}
	else
	{
		//Length incorrect, return error!
		aRet=false;
	}

	return aRet;
}


//-----------------------------------------------------------------------------
// Read 4 registers (4*8 bits) from sensor
// aReg:    Address of the register we want to read
// Return:	Value of the requested register
// TODO Improv: burst read
//-----------------------------------------------------------------------------
float iI2C_GetDataFloat32(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg)
{
	floatcharUnion tmp;
	tmp.s[0] = iI2C_GetData8(aI2c, aAddr_W, aReg);
	tmp.s[1] = iI2C_GetData8(aI2c, aAddr_W, aReg+1);
	tmp.s[2] = iI2C_GetData8(aI2c, aAddr_W, aReg+2);
	tmp.s[3] = iI2C_GetData8(aI2c, aAddr_W, aReg+3);

	return tmp.f;
}
