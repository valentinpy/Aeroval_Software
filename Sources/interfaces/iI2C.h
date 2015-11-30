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

#ifndef __I2C__
#define __I2C__

#include "../misc/def.h"
#include "../misc/derivative.h"

//------------------------------------------------------------
// I2C number enum
//------------------------------------------------------------
typedef enum
{
	kI2c0,
	kI2c2
} I2cEnum;



typedef enum
{
	kAckAuto,
	kNoAck
}I2CAckEnum;

typedef enum
{
	kTransferComplete=0x80,
	kInterruptFlag=0x2,
	kRxAK=0x1,
	kBUSY=0x20
}I2CStatusEnum;

typedef enum
{
	kTxMode,
	kRxMode
}I2CTransmiteModeEnum;

//------------------------------------------------------------
// I2C module config
//------------------------------------------------------------
void iI2C_Config(void);

//------------------------------------------------------------
// I2C interface enable
//------------------------------------------------------------
void iI2C_Enable(I2cEnum aI2c);

//------------------------------------------------------------
// I2C interface disable
//------------------------------------------------------------
void iI2C_Disable(I2cEnum aI2c);

//------------------------------------------------------------
// Set START state
//------------------------------------------------------------
void iI2C_SetStartState(I2cEnum aI2c);

//------------------------------------------------------------
// Set repeated START state
//------------------------------------------------------------
void iI2C_SetRepeatedStartSate(I2cEnum aI2c);

//------------------------------------------------------------
// Set STOP state
//------------------------------------------------------------
void iI2C_SetStopState(I2cEnum aI2c);

//------------------------------------------------------------
// Generate automatic ACK or not
//------------------------------------------------------------
void iI2C_SetAckMode(I2cEnum aI2c, I2CAckEnum aAck);

//------------------------------------------------------------
// Select if we transmit or receive
//------------------------------------------------------------
void iI2C_TxRxSelect(I2cEnum aI2c, I2CTransmiteModeEnum aMode);

//------------------------------------------------------------
// Send a data
//------------------------------------------------------------
void iI2C_SendData(I2cEnum aI2c, UInt8 aData);

//------------------------------------------------------------
// Wait End of transmit or receive
//------------------------------------------------------------
void iI2C_WaitEndOfRxOrTx(I2cEnum aI2c);

//------------------------------------------------------------
// Read received data, ! generate I2C clock if not in STOP mode
//------------------------------------------------------------
UInt8 iI2C_ReadData(I2cEnum aI2c);

//------------------------------------------------------------
// Get I2C status flags
//------------------------------------------------------------
bool iI2C_ReadStatus(I2cEnum aI2c, I2CStatusEnum aStatus);

#endif
