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

//--------------------------------------------------
// Union to convert 4 bytes in float
// TODO Improv: find a better way to achieve this
//-------------------------------------------------
typedef union _data {
  float f;
  char  s[4];
} floatcharUnion;


//------------------------------------------------------------
// I2C module config
//------------------------------------------------------------
void iI2C_Config(void);

//------------------------------------------------------------
// I2C interface enable
//------------------------------------------------------------
void iI2C_Enable(I2cEnum aI2c);

//-------------------------------------------------------------------
// Send a byte to aAddr_W over I2C
// aAddr_W: Address of the device
// aReg: register to write into
// aVal: value to write in aReg
// return: true: write successful, false: error when writing
//-------------------------------------------------------------------
bool iI2C_SetData8(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg,UInt8 aVal);

//-----------------------------------------------------------------------------
// Read one register (8 bits) from sensor
// aReg:    Address of the register we wnat to read
// aAddr_W:	Address of the device (Write)
// Return:	Value of the requested register
//-----------------------------------------------------------------------------
UInt8 iI2C_GetData8(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg);

//-----------------------------------------------------------------------------
// Read two registers (8 bits) from sensor
// aReg:    Address of the register we want to read
// aAddr_W:	Address of the device (Write)
// Return:	Value of the requested register
//-----------------------------------------------------------------------------
UInt16 iI2C_GetData16(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg);

//-----------------------------------------------------------------------------
// Read aLength registers (8 bits) from sensor
// aReg:    Address of the register we want to read
// aAddr_W:	Address of the device (Write)
// aLength: Number of bytes to read
// aRet*:	Pointer to return the data, must be big enough, according to aLength
// Return:	true if success, false else
//-----------------------------------------------------------------------------
bool iI2C_GetData(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg, UInt8 aLength, UInt8 *aRetData);

//-------------------------------------------------------------------
// Read 4 bytes from Em7180 over I2C
// aReg: first register to read
// return: value of the register aReg..aReg+3
//-------------------------------------------------------------------
float iI2C_GetDataFloat32(I2cEnum aI2c, UInt8 aAddr_W, UInt8 aReg);


#endif
