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

#include "iUart.h"

#define Uart0StatusIRQ	31
#define Uart3StatusIRQ	37
#define Uart4StatusIRQ	66

UartRecBufStruct Uart0RecBuff;
UartRecBufStruct Uart3RecBuff;
UartRecBufStruct Uart4RecBuff;

/********************************************************************************************
 * iUart_ResetBuffer : Reset the corresponding UART buffer
 * @param UartEnum uart : Defines the UART buffer to reset. The enum is declared in iUart.h
 ********************************************************************************************/
void iUart_ResetBuffer(UartEnum uart)
{
	int i;
	UartRecBufStruct* pUartRecBuf;
	switch (uart)
	{
		case kUart0Aux:
			pUartRecBuf = &Uart0RecBuff;
			break;
		case kUart3USB:
			pUartRecBuf = &Uart3RecBuff;
			break;
		case kUart4Aux:
			pUartRecBuf = &Uart4RecBuff;
			break;
		case kUartAll:
			iUart_ResetBuffer(kUart0Aux);
			iUart_ResetBuffer(kUart3USB);
			iUart_ResetBuffer(kUart4Aux);
			break;
		default:
			iUart_ResetBuffer(kUartAll);
			break;
	}

	(*pUartRecBuf).InIndex = 0;
	(*pUartRecBuf).OutIndex = 0;
	(*pUartRecBuf).ByteCount = 0;
	(*pUartRecBuf).BufferIsFull = false;

	for (i = 0; i < kUartRecBufSize ; i++)
	{
		(*pUartRecBuf).SciRecBuf[i] = 0;
	}

}

/*-----------------------------------------------------------------------
 /UART configuration
 /-----------------------------------------------------------------------*/
void iUart_Config(void)
{
	UInt16 aSbr;
	UInt8 aTmp;
	UInt32 aBrfa;

	// Clock enable
	SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK | SIM_SCGC4_UART3_MASK;

	// Pins setup for UART0,3,4
	//UART0
	PORTA_PCR14 = 0|PORT_PCR_PS_MASK|PORT_PCR_PE_MASK|PORT_PCR_DSE_MASK|(PORT_PCR_MUX(0x3));
	PORTA_PCR15 = 0|PORT_PCR_PS_MASK|PORT_PCR_PE_MASK|PORT_PCR_DSE_MASK|(PORT_PCR_MUX(0x3));
	//UART3
	PORTB_PCR10 = 0|PORT_PCR_PS_MASK|PORT_PCR_PE_MASK|PORT_PCR_DSE_MASK|(PORT_PCR_MUX(0x3));
	PORTB_PCR11 = 0|PORT_PCR_PS_MASK|PORT_PCR_PE_MASK|PORT_PCR_DSE_MASK|(PORT_PCR_MUX(0x3));
	//UART4
	PORTC_PCR14 = 0|PORT_PCR_PS_MASK|PORT_PCR_PE_MASK|PORT_PCR_DSE_MASK|(PORT_PCR_MUX(0x3));
	PORTC_PCR15 = 0|PORT_PCR_PS_MASK|PORT_PCR_PE_MASK|PORT_PCR_DSE_MASK|(PORT_PCR_MUX(0x3));

	// UART Control Register 2 (UARTx_C2)
	// Disable TX & RX before setup by disabling transmitter and receiver
	UART0_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
	UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
	UART4_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

	// IRQ Config UART0
	//enable_irq UART0
	// Clear prending interrupt for UART0
	NVIC_ClearPendingIRQ(Uart0StatusIRQ);

	// Interrupt enable for UART0
	NVIC_EnableIRQ(Uart0StatusIRQ);

	// Set interrupt priority for UART0
	NVIC_SetPriority(Uart0StatusIRQ, 0);

	// IRQ Config UART3
	//enable_irq UART3
	// Clear prending interrupt for UART3
	NVIC_ClearPendingIRQ(Uart3StatusIRQ);

	// Interrupt enable for UART3
	NVIC_EnableIRQ(Uart3StatusIRQ);

	// Set interrupt priority for UART3
	NVIC_SetPriority(Uart3StatusIRQ, 0);

	// IRQ Config UART4
	//enable_irq UART4
	// Clear prending interrupt for UART4
	NVIC_ClearPendingIRQ(Uart4StatusIRQ);

	// Interrupt enable for UART4
	NVIC_EnableIRQ(Uart4StatusIRQ);

	// Set interrupt priority for UART4
	NVIC_SetPriority(Uart4StatusIRQ, 0);


	// UART0
	// UART Control Register 1 (UARTx_C1)
	// Loop Mode Select=0,Normal operation 
	// UARTSWAI=0, UART clock continues to run in wait mode
	// RSRC=0,Selects internal loop back mode and receiver input is internally connected to transmitter output
	// M=0, Normal - start + 8 data bits (MSB/LSB first as determined by MSBF) + stop
	// WAKE=0,Idle-line wakeup
	// ILT=0,Idle character bit count starts after start bit
	// PE=0,Parity function disabled
	// PT=0,Even parity 
	UART0_C1 = 0; /* We need all default settings, so entire register is cleared */

	// UART Baud Rate Registers:High (UARTx_BDH)
	// UART Baud Rate Registers: Low (UARTx_BDL)
	// Calculate baud rate settings
	aSbr = (UInt16) ((kClockCpukHz * 1000) / (kUart0BaudRate * 16));
	// Save off the current value of the UARTx_BDH except for the SBR field
	aTmp = UART0_BDH & ~(UART_BDH_SBR_MASK);
	UART0_BDH = aTmp | UART_BDH_SBR(((aSbr & 0x1F00) >> 8));
	UART0_BDL = (UInt8) (aSbr & UART_BDL_SBR_MASK);

	// UART Control Register 4 (UARTx_C4)
	// BRFA, Baud Rate Fine Adjust
	// Determine if a fractional divider is needed to get closer to the baud rate
	aBrfa = ((((UInt32) kClockCpukHz * 32000) / (kUart0BaudRate * 16))
			- (aSbr * 32));
	// Save off the current value of the UARTx_C4 register except for the BRFA field */
	aTmp = UART0_C4 & ~(UART_C4_BRFA(0x1F));
	UART0_C4 = aTmp | UART_C4_BRFA(aBrfa);

	// UART FIFO Parameters (UARTx_PFIFO)
	// TXFE=1,Transmit FIFO is enabled. Buffer is depth indicted by TXFIFOSIZE
	// TXFIFOSIZE=3,Transmit FIFO/Buffer Depth = 16 Datawords 
	UART0_PFIFO = 0;
	UART0_PFIFO |= (UART_PFIFO_TXFE_MASK | UART_PFIFO_TXFIFOSIZE(3));

	// UART FIFO Control Register (UARTx_CFIFO)
	// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 1283
	// Flush RX & TX fifo
	UART0_CFIFO |= (UART_CFIFO_TXFLUSH_MASK | UART_CFIFO_RXFLUSH_MASK);

	// UART Control Register 2 (UARTx_C2)
	// TIE=0, TDRE interrupt and DMA transfer requests disabled
	// TCIE=0, TC interrupt requests disabled
	// RIE=1,RDRF interrupt or DMA transfer requests enabled
	// ILIE=0,IDLE interrupt requests disabled
	// TE & RE =1, Enable receiver and transmitter
	UART0_C2 = 0;
	UART0_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK | UART_C2_RIE_MASK);




	// UART3
	// UART Control Register 1 (UARTx_C1)
	// Loop Mode Select=0,Normal operation 
	// UARTSWAI=0, UART clock continues to run in wait mode
	// RSRC=0,Selects internal loop back mode and receiver input is internally connected to transmitter output
	// M=0, Normal - start + 8 data bits (MSB/LSB first as determined by MSBF) + stop
	// WAKE=0,Idle-line wakeup
	// ILT=0,Idle character bit count starts after start bit
	// PE=0,Parity function disabled
	// PT=0,Even parity 
	UART3_C1 = 0; /* We need all default settings, so entire register is cleared */

	// UART Baud Rate Registers:High (UARTx_BDH)
	// UART Baud Rate Registers: Low (UARTx_BDL)
	// Calculate baud rate settings
	aSbr = (UInt16) ((kClockBuskHz * 1000) / (kUart3BaudRate * 16));
	// Save off the current value of the UARTx_BDH except for the SBR field
	aTmp = UART3_BDH & ~(UART_BDH_SBR_MASK);
	UART3_BDH = aTmp | UART_BDH_SBR(((aSbr & 0x1F00) >> 8));
	UART3_BDL = (UInt8) (aSbr & UART_BDL_SBR_MASK);

	// UART Control Register 4 (UARTx_C4)
	// BRFA, Baud Rate Fine Adjust
	// Determine if a fractional divider is needed to get closer to the baud rate
	aBrfa = ((((UInt32) kClockBuskHz * 32000) / (kUart3BaudRate * 16))
			- (aSbr * 32));
	// Save off the current value of the UARTx_C4 register except for the BRFA field */
	aTmp = UART3_C4 & ~(UART_C4_BRFA(0x1F));
	UART3_C4 = aTmp | UART_C4_BRFA(aBrfa);

	// UART FIFO Parameters (UARTx_PFIFO)
	// TXFE=1,Transmit FIFO is enabled. Buffer is depth indicted by TXFIFOSIZE
	// TXFIFOSIZE=3,Transmit FIFO/Buffer Depth = 16 Datawords 
	UART3_PFIFO = 0;
	UART3_PFIFO |= (UART_PFIFO_TXFE_MASK | UART_PFIFO_TXFIFOSIZE(3));

	// UART FIFO Control Register (UARTx_CFIFO)
	// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 1283
	// Flush RX & TX fifo
	UART3_CFIFO |= (UART_CFIFO_TXFLUSH_MASK | UART_CFIFO_RXFLUSH_MASK);

	// UART Control Register 2 (UARTx_C2)
	// TIE=0, TDRE interrupt and DMA transfer requests disabled
	// TCIE=0, TC interrupt requests disabled
	// RIE=1,RDRF interrupt or DMA transfer requests enabled
	// ILIE=0,IDLE interrupt requests disabled
	// TE & RE =1, Enable receiver and transmitter
	UART3_C2 = 0;
	UART3_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK | UART_C2_RIE_MASK);


	// UART4
	// UART Control Register 1 (UARTx_C1)
	// Loop Mode Select=0,Normal operation 
	// UARTSWAI=0, UART clock continues to run in wait mode
	// RSRC=0,Selects internal loop back mode and receiver input is internally connected to transmitter output
	// M=0, Normal - start + 8 data bits (MSB/LSB first as determined by MSBF) + stop
	// WAKE=0,Idle-line wakeup
	// ILT=0,Idle character bit count starts after start bit
	// PE=0,Parity function disabled
	// PT=0,Even parity 
	UART4_C1 = 0; /* We need all default settings, so entire register is cleared */

	// UART Baud Rate Registers:High (UARTx_BDH)
	// UART Baud Rate Registers: Low (UARTx_BDL)
	// Calculate baud rate settings
	aSbr = (UInt16) ((kClockBuskHz * 1000) / (kUart4BaudRate * 16));
	// Save off the current value of the UARTx_BDH except for the SBR field
	aTmp = UART4_BDH & ~(UART_BDH_SBR_MASK);
	UART4_BDH = aTmp | UART_BDH_SBR(((aSbr & 0x1F00) >> 8));
	UART4_BDL = (UInt8) (aSbr & UART_BDL_SBR_MASK);

	// UART Control Register 4 (UARTx_C4)
	// BRFA, Baud Rate Fine Adjust
	// Determine if a fractional divider is needed to get closer to the baud rate
	aBrfa = ((((UInt32) kClockBuskHz * 32000) / (kUart4BaudRate * 16))
			- (aSbr * 32));
	// Save off the current value of the UARTx_C4 register except for the BRFA field */
	aTmp = UART4_C4 & ~(UART_C4_BRFA(0x1F));
	UART4_C4 = aTmp | UART_C4_BRFA(aBrfa);

	// UART FIFO Parameters (UARTx_PFIFO)
	// TXFE=1,Transmit FIFO is enabled. Buffer is depth indicted by TXFIFOSIZE
	// TXFIFOSIZE=3,Transmit FIFO/Buffer Depth = 16 Datawords 
	UART4_PFIFO = 0;
	UART4_PFIFO |= (UART_PFIFO_TXFE_MASK | UART_PFIFO_TXFIFOSIZE(3));

	// UART FIFO Control Register (UARTx_CFIFO)
	// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 1283
	// Flush RX & TX fifo
	UART4_CFIFO |= (UART_CFIFO_TXFLUSH_MASK | UART_CFIFO_RXFLUSH_MASK);

	// UART Control Register 2 (UARTx_C2)
	// TIE=0, TDRE interrupt and DMA transfer requests disabled
	// TCIE=0, TC interrupt requests disabled
	// RIE=1,RDRF interrupt or DMA transfer requests enabled
	// ILIE=0,IDLE interrupt requests disabled
	// TE & RE =1, Enable receiver and transmitter
	UART4_C2 = 0;
	UART4_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK | UART_C2_RIE_MASK);

	// Enable de l'interruption
	//enable_irq(INT_UART3_RX_TX-16);
	//set_irq_priority (INT_UART3_RX_TX-16, 0);
}

//------------------------------------------------------------
// Get Uart3 flags state
// aStatus: which flag to read
// retour	: flag state
//------------------------------------------------------------
bool iUart_GetStatus(UartEnum uart, UartStatusEnum aStatus)
{
	bool status;

	switch (uart)
	{
		case kUart0Aux:
			status = ((UART0_S1 & aStatus) == aStatus);
			break;
		case kUart3USB:
			status = ((UART3_S1 & aStatus) == aStatus);
			break;
		case kUart4Aux:
			status = ((UART4_S1 & aStatus) == aStatus);
			break;
		case kUartAll:
			status = false;
			break;
		default:
			status = false;
			break;
	}
	// UART Status Register 1 (UARTx_S1)
	// K10 Sub-Family Reference Manual, Rev. 6, Nov 2011 page 1267
	return status;
}

//------------------------------------------------------------
// Get Uart3 fifo flags state
// aStatus: which flag to read
// retour	: flag state
//------------------------------------------------------------
bool iUart_GetFifoStatus(UartEnum uart, UartFifoStatusEnum aStatus)
{
	bool status;

	switch (uart)
	{
		case kUart0Aux:
			status = ((UART0_SFIFO & aStatus) == aStatus);
			break;
		case kUart3USB:
			status = ((UART3_SFIFO & aStatus) == aStatus);
			break;
		case kUart4Aux:
			status = ((UART4_SFIFO & aStatus) == aStatus);
			break;
		case kUartAll:
			status = false;
			break;
		default:
			status = false;
			break;
	}
	return status;
}

//------------------------------------------------------------
// Uart3 Data register write
// aData: datas to transmit
//------------------------------------------------------------
void iUart_SetData(UartEnum uart, UInt8 aData)
{
	switch (uart)
	{
		case kUart0Aux:
			UART0_D = aData;
			break;
		case kUart3USB:
			UART3_D = aData;
			break;
		case kUart4Aux:
			UART4_D = aData;
			break;
		case kUartAll:
			UART0_D = aData;
			UART3_D = aData;
			UART4_D = aData;
			break;
		default:
			break;
	}
}

//------------------------------------------------------------
// Check if the buffer is empty
// Return : true --> buffer empty, false --> buffer not empty
//------------------------------------------------------------
bool iUart_IsBufferEmpty(UartEnum uart)
{
	bool aRet = false;
	UartRecBufStruct* pUartRecBuf;

	switch (uart)
	{
		case kUart0Aux:
			pUartRecBuf = &Uart0RecBuff;
			break;
		case kUart3USB:
			pUartRecBuf = &Uart3RecBuff;
			break;
		case kUart4Aux:
			pUartRecBuf = &Uart4RecBuff;
			break;
		case kUartAll:
			return false;
			break;
		default:
			return false;
			break;
	}

	if ((*pUartRecBuf).ByteCount == 0)
	{
		aRet = true;
	}
	else
	{
		aRet = false;
	}

	return aRet;
}
//------------------------------------------------------------
// Return : Nb of bytes received
//------------------------------------------------------------
UInt16 iUart_NbByteReceive(UartEnum uart)
{
	UartRecBufStruct* pUartRecBuf;

	switch (uart)
	{
		case kUart0Aux:
			pUartRecBuf = &Uart0RecBuff;
			break;
		case kUart3USB:
			pUartRecBuf = &Uart3RecBuff;
			break;
		case kUart4Aux:
			pUartRecBuf = &Uart4RecBuff;
			break;
		case kUartAll:
			return false;
			break;
		default:
			return false;
			break;
	}
	return (*pUartRecBuf).ByteCount;
}
//------------------------------------------------------------
// Return : true if we have received a new tram otherwise false
//TODO utile?
//------------------------------------------------------------
bool iUart_IsNewTram(UartEnum uart)
{
	UartRecBufStruct* pUartRecBuf;
	bool result = false;

	switch (uart)
	{
		case kUart0Aux:
			pUartRecBuf = &Uart0RecBuff;
			break;
		case kUart3USB:
			pUartRecBuf = &Uart3RecBuff;
			break;
		case kUart4Aux:
			pUartRecBuf = &Uart4RecBuff;
			break;
		case kUartAll:
			result = false;
			break;
		default:
			result = false;
			break;
	}

	if ((*pUartRecBuf).InIndex > 1)
	{
		if (((*pUartRecBuf).ByteCount > 0)
				&& ((*pUartRecBuf).SciRecBuf[(*pUartRecBuf).InIndex - 1] == 0xa)
				&& ((*pUartRecBuf).SciRecBuf[(*pUartRecBuf).InIndex - 2] == 0xd))
		{
			result = true;
		}
		else
		{
			result = false;
		}
	}

	else if ((*pUartRecBuf).InIndex == 1)
	{
		if (((*pUartRecBuf).ByteCount > 0)
				&& ((*pUartRecBuf).SciRecBuf[0] == 0xa)
				&& ((*pUartRecBuf).SciRecBuf[199] == 0xd))
		{
			result = true;
		}
		else
		{
			result = false;
		}
	}
	else if ((*pUartRecBuf).InIndex == 0)
	{
		if (((*pUartRecBuf).ByteCount > 0)
				&& ((*pUartRecBuf).SciRecBuf[199] == 0xa)
				&& ((*pUartRecBuf).SciRecBuf[198] == 0xd))
		{
			result = true;
		}
		else
		{
			result = false;
		}
	}

	return result;

}
//------------------------------------------------------------
// Byte read in the RX buffer
// Return : oldest byte in the buffer
//------------------------------------------------------------
Int8 iUart_GetCharFromBuffer(UartEnum uart)
{
	Int8 aChar = 0;

	UartRecBufStruct* pUartRecBuf;

	switch (uart)
	{
		case kUart0Aux:
			pUartRecBuf = &Uart0RecBuff;
			break;
		case kUart3USB:
			pUartRecBuf = &Uart3RecBuff;
			break;
		case kUart4Aux:
			pUartRecBuf = &Uart4RecBuff;
			break;
		case kUartAll:
			return false;
			break;
		default:
			return false;
			break;
	}

	// Byte read
	aChar = (*pUartRecBuf).SciRecBuf[(*pUartRecBuf).OutIndex];

	// Index inc
	(*pUartRecBuf).OutIndex++;

	// Turning buffer
	if ((*pUartRecBuf).OutIndex >= kUartRecBufSize )
	{
		(*pUartRecBuf).OutIndex = 0;
	}

	// Byte counter dec
	(*pUartRecBuf).ByteCount--;

	// Retourne un byte du buffer
	return aChar;
}

//---------------------------------------------------------------------------
// RX interrupt UART0
//---------------------------------------------------------------------------
static UInt16 sCountRx0 = 0;
void UART0_Status_IRQHandler(void)
{
	Int8 aVal;
	static UInt8 sStatusUart0;

	sStatusUart0 = UART0_S1;

	// Read the RX byte
	aVal = UART0_D;

	//if(UART3_S1 & UART_S1_RDRF_MASK)
	{
		sCountRx0++;
		// Read the RX byte
		//aVal=UART0_D;

		if (Uart0RecBuff.ByteCount >= kUartRecBufSize )
		{
			// Buffer full flag
			Uart0RecBuff.BufferIsFull = true;
		}
		else
		{
			// Buffer not full flag
			Uart0RecBuff.BufferIsFull = false;

			// Save received data
			Uart0RecBuff.SciRecBuf[Uart0RecBuff.InIndex] = aVal;

			// Index inc
			Uart0RecBuff.InIndex++;

			// Bytes counter inc	
			Uart0RecBuff.ByteCount++;

			// Turning buffer
			if (Uart0RecBuff.InIndex >= kUartRecBufSize )
			{
				Uart0RecBuff.InIndex = 0;
			}
		}
	}
}

//---------------------------------------------------------------------------
// RX interrupt UART3
//---------------------------------------------------------------------------
static UInt16 sCountRx3 = 0;
void UART3_Status_IRQHandler(void)
{
	Int8 aVal;
	static UInt8 sStatusUart3;

	sStatusUart3 = UART3_S1;

	// Read the RX byte
	aVal = UART3_D;

	//if(UART3_S1 & UART_S1_RDRF_MASK)
	{
		sCountRx3++;
		// Read the RX byte
		//aVal=UART3_D;

		if (Uart3RecBuff.ByteCount >= kUartRecBufSize )
		{
			// Buffer full flag
			Uart3RecBuff.BufferIsFull = true;
		}
		else
		{
			// Buffer not full flag
			Uart3RecBuff.BufferIsFull = false;

			// Save received data
			Uart3RecBuff.SciRecBuf[Uart3RecBuff.InIndex] = aVal;

			// Index inc
			Uart3RecBuff.InIndex++;

			// Bytes counter inc	
			Uart3RecBuff.ByteCount++;

			// Turning buffer
			if (Uart3RecBuff.InIndex >= kUartRecBufSize )
			{
				Uart3RecBuff.InIndex = 0;
			}
		}
	}
}

//---------------------------------------------------------------------------
// RX interrupt UART4
//---------------------------------------------------------------------------
static UInt16 sCountRx4 = 0;
void UART4_Status_IRQHandler(void)
{
	Int8 aVal;
	static UInt8 sStatusUart4;

	sStatusUart4 = UART4_S1;

	// Read the RX byte
	aVal = UART4_D;

	//if(UART3_S1 & UART_S1_RDRF_MASK)
	{
		sCountRx4++;
		// Read the RX byte
		//aVal=UART3_D;

		if (Uart4RecBuff.ByteCount >= kUartRecBufSize )
		{
			// Buffer full flag
			Uart4RecBuff.BufferIsFull = true;
		}
		else
		{
			// Buffer not full flag
			Uart4RecBuff.BufferIsFull = false;

			// Save received data
			Uart4RecBuff.SciRecBuf[Uart4RecBuff.InIndex] = aVal;

			// Index inc
			Uart4RecBuff.InIndex++;

			// Bytes counter inc	
			Uart4RecBuff.ByteCount++;

			// Turning buffer
			if (Uart4RecBuff.InIndex >= kUartRecBufSize )
			{
				Uart4RecBuff.InIndex = 0;
			}
		}
	}
}
