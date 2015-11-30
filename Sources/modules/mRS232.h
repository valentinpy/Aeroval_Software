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
void mRs232_WriteString(UartEnum uart, UInt8 *aDataPtr);

//-----------------------------------------------------------------------------
// String send (fixed size)
// The transmission is size defined
// *aDataPtr	: string address
// uart			: which UART to use
// aSize		: length of the frame (bytes)
//-----------------------------------------------------------------------------
void mRs232_WriteStringFixedSize(UartEnum uart, char *aDataPtr, UInt16 aSize);

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
