/*
 * Copyright (C) 2015 Valentin Py
 * Copyright (C) 2014 Serge Monnerat
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

#include "mRS232.h"


//------------------------------------------------------------------------------------------------------------------------------
// General configuration
//------------------------------------------------------------------------------------------------------------------------------

/*
 * 2 UART Modules are used
 * UART0 => USB/UART, communication with PC, full duplex
 * UART1 => RS485, communication with split-flap display, half duplex, direction has to been set
 */

//-----------------------------------------------------------------------
// UART 0, 3, 4 module configuration
//-----------------------------------------------------------------------
void mRs232_Setup(void)
{
	// UART 0, 3, 4 setup
	iUart_Config();

	//Init UART 0, 3, 4 RX buffers

	//Interrupts must be disabled
	DisableInterrupts;

	iUart_ResetBuffer(kUart0Aux);
	iUart_ResetBuffer(kUart3USB);
	iUart_ResetBuffer(kUart4Aux);

	EnableInterrupts;
}

//-----------------------------------------------------------------------------
// String send
// The transmission stop at the char NULL
// *aDataPtr	: string address
// uart			: which UART to use
//-----------------------------------------------------------------------------
void mRs232_WriteString(UartEnum uart, UInt8 *aDataPtr)
{
	// Send char until NULL char
	while(*aDataPtr!=0)
	{
		// Wait end of transmit
		while(!iUart_GetStatus(uart,kSciTransmitComplete));

		// Write data
		iUart_SetData(uart,*aDataPtr);

		// Next char
		aDataPtr++;
	}
}

//-----------------------------------------------------------------------------
// String send (fixed size)
// The transmission is size defined
// *aDataPtr	: string address
// uart			: which UART to use
// aSize		: length of the frame (bytes)
//-----------------------------------------------------------------------------
void mRs232_WriteStringFixedSize(UartEnum uart, char *aDataPtr, UInt16 aSize)
{
	// Send char until NULL char
	UInt16 i;
	for(i=0; i<aSize; i++)
	{
		// Wait end of transmit
		while(!iUart_GetStatus(uart,kSciTransmitComplete));

		// Write data
		iUart_SetData(uart,*aDataPtr);

		// Next char
		aDataPtr++;
	}
}

//-----------------------------------------------------------------------------
// Byte send
// aData		: byte to send
// uart			: which UART to use
//-----------------------------------------------------------------------------
void mRs232_WriteChar(UartEnum uart, UInt8 aData)
{
	// Write data
	iUart_SetData(uart,aData);

	// Wait end of transmit
	while(iUart_GetStatus(uart,kSciTransmitComplete)==0);
}


//-----------------------------------------------------------------------------
// Buffer byte read. Rx interrupt fill the buffer
// *aBytePtr	: pointer to return the byte
// Return 	    : true --> the buffer is empty, false the buffer is not empty
// uart			: which UART to use
//-----------------------------------------------------------------------------
bool mRs232_ReadDataFromBuffer(UartEnum uart, UInt8 *aBytePtr)
{
	bool aRet=false;

	// Contr�le si le buffer est vide
	aRet=iUart_IsBufferEmpty(uart);

	// Si le buffer n'est pas vide --> lecture d'un byte
	if(false==aRet)
	{
		// Lecture d'un byte du buffer de r�ception
		*aBytePtr=iUart_GetCharFromBuffer(uart);
	}
	else
	{
		*aBytePtr = '\0';
	}

	return aRet;
}


//-----------------------------------------------------------------------------
// Clear the RX buffer
// uart			: which UART to use
//-----------------------------------------------------------------------------
void mRs232_ClearBuffer(UartEnum uart)
{
	UInt8 tmp;
	while(mRs232_ReadDataFromBuffer(uart, &tmp)!=true);
}
