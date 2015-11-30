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

#ifndef __iUart__
#define __iUart__

#include "../misc/def.h"
#include "../misc/derivative.h"


#define kUart0BaudRate 115200
#define kUart3BaudRate 921600
//#define kUart3BaudRate 115200
#define kUart4BaudRate 921600


// Uart reception buffer sizes
#define kUartRecBufSize ((UInt8)(200)) 

// RX buffer control struct
typedef struct
{
	Int8 SciRecBuf[kUartRecBufSize];
	UInt16 InIndex;
	UInt16 OutIndex;
	UInt16 ByteCount;
	bool BufferIsFull;
} UartRecBufStruct;

//------------------------------------------------------------
// UART number enum
//------------------------------------------------------------
typedef enum
{
	kUart0Aux, kUart3USB, kUart4Aux, kUartAll
} UartEnum;

//------------------------------------------------------------
// UART status flag
//------------------------------------------------------------
typedef enum
{
	kSciTransmitDataRegEmpty = 0x80,
	kSciTransmitComplete = 0x40,
	kSciReceiveDataRegFull = 0x20,
	kSciIdleLineDetect = 0x10,
	kSciOverrunErr = 0x08,
	kSciNoiseErr = 0x04,
	kSciFramingErr = 0x02,
	kSciParityErr = 0x01
} UartStatusEnum;

//------------------------------------------------------------
// UART fifo status flag
//------------------------------------------------------------
typedef enum
{
	kTxFifoEmpty = 0x80,
	kRxFifoEmpty = 0x40,
	kTxFifoOverflow = 0x02,
	kRxFifoUnderflow = 0x01
} UartFifoStatusEnum;

//-----------------------------------------------------------------------
// UART 0,3,4 module configuration
//-----------------------------------------------------------------------
void iUart_Config(void);

//------------------------------------------------------------
// Get Uart flags state
// uart : which uart to use
// aStatus: which flag to read
// retour	: flag state
//------------------------------------------------------------
bool iUart_GetStatus(UartEnum uart, UartStatusEnum aStatus);

//------------------------------------------------------------
// Get Uart3 fifo flags state
// uart : which uart to use
// aStatus: which flag to read
// retour	: flag state
//------------------------------------------------------------
bool iUart_GetFifoStatus(UartEnum uart, UartFifoStatusEnum aStatus);

//------------------------------------------------------------
// Return : true if we have received a new tram otherwise false
// uart : which uart to use
//------------------------------------------------------------
bool iUart_IsNewTram(UartEnum uart);

//------------------------------------------------------------
// Uart3 Data register write
// aData: datas to transmit
// uart : which uart to use
//------------------------------------------------------------
void iUart_SetData(UartEnum uart, UInt8 aData);

//------------------------------------------------------------
// Check if the buffer is empty
// Return : true --> buffer empty, false --> buffer not empty
// uart : which uart to use
//------------------------------------------------------------
bool iUart_IsBufferEmpty(UartEnum uart);

//------------------------------------------------------------
// Byte read in the RX buffer
// Return : oldest byte in the buffer
// uart : which uart to use
//------------------------------------------------------------
Int8 iUart_GetCharFromBuffer(UartEnum uart);

//------------------------------------------------------------
// Return : Nb of bytes received
// uart : which uart to use
//------------------------------------------------------------
UInt16 iUart_NbByteReceive(UartEnum uart);

//-----------------------------------------------------------------------
// Reset RX buffer
// uart : which uart to use
//-----------------------------------------------------------------------
void iUart_ResetBuffer(UartEnum uart);

#endif
