/*
------------------------------------------------------------
Copyright 2003-2015 Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
------------------------------------------------------------
File name : 		mRs232.h
Author and date :	Serge Monnerat	26.09.2014
					Valentin Py		15.06.2015

Goal :
This file provides all the necessary functions to use RS232 and Rs485

*/

#ifndef __mRS232__
#define __mRS232__

#include "../misc/def.h"
#include "../interfaces/iUart.h"

/*
 * 3 UART  are used
 * UART0 => AUX
 * UART3 => USB/UART, communication with PC, full duplex
 * UART4 => AUX
 */

//-----------------------------------------------------------------------------
// RS232 module setup
//-----------------------------------------------------------------------------
void mRs232_Setup(void);


//-----------------------------------------------------------------------------
// String send
// The transmission stop at the char NULL
// *aDataPtr	: string address
// uart			: which UART to use
//-----------------------------------------------------------------------------
void mRs232_WriteString(UartEnum uart, char *aDataPtr);


//-----------------------------------------------------------------------------
// Byte send
// aData		: byte to send
// uart			: which UART to use
//-----------------------------------------------------------------------------
void mRs232_WriteChar(UartEnum uart, UInt8 aData);


//-----------------------------------------------------------------------------
// Buffer byte read. Rx interrupt fill the buffer
// *aBytePtr	: pointer to return the byte
// Return 	    : true --> the buffer is empty, false the buffer is not empty
// uart			: which UART to use
//-----------------------------------------------------------------------------
bool mRs232_ReadDataFromBuffer(UartEnum uart, UInt8 *aBytePtr);


//-----------------------------------------------------------------------------
// Clear the RX buffer
// uart			: which UART to use
//-----------------------------------------------------------------------------
void mRs232_ClearBuffer(UartEnum uart);


#endif
