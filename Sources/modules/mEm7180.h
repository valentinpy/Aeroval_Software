/*
 * Copyright (C) 2015 Valentin Py
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

#ifndef SOURCES_MEM7180_H_
#define SOURCES_MEM7180_H_

#include "../userDefined.h"
#include "../interfaces/iI2C.h"
#include "../misc/def.h"
#include "mDelay.h"
#include "math.h"

// Addresses of registers
#define EM7180_ADDR_W 			0x50
#define EM7180_ADDR_R			0x51
#define SetupValue_MagRate 		0x1E
#define SetupValue_AccelRate 	0x0A
#define SetupValue_GyroRate 	0x14

//--------------------------------------------------
// Enum of addresses of registers from sensor (8 bits registers => base address)
//--------------------------------------------------
typedef enum{
	EM7180_QX 				= 0x00,  // this is a 32-bit normalized floating point number read from registers 0x00-03
	EM7180_QY				= 0x04,  // this is a 32-bit normalized floating point number read from registers 0x04-07
	EM7180_QZ				= 0x08,  // this is a 32-bit normalized floating point number read from registers 0x08-0B
	EM7180_QW				= 0x0C,  // this is a 32-bit normalized floating point number read from registers 0x0C-0F
	EM7180_QTIME			= 0x10,  // this is a 16-bit unsigned integer read from registers 0x10-11
	EM7180_MX				= 0x12,  // int16_t from registers 0x12-13
	EM7180_MY				= 0x14,  // int16_t from registers 0x14-15
	EM7180_MZ				= 0x16,  // int16_t from registers 0x16-17
	EM7180_MTIME			= 0x18,  // uint16_t from registers 0x18-19
	EM7180_AX				= 0x1A,  // int16_t from registers 0x1A-1B
	EM7180_AY				= 0x1C,  // int16_t from registers 0x1C-1D
	EM7180_AZ				= 0x1E,  // int16_t from registers 0x1E-1F
	EM7180_ATIME			= 0x20,  // uint16_t from registers 0x20-21
	EM7180_GX				= 0x22,  // int16_t from registers 0x22-23
	EM7180_GY				= 0x24,  // int16_t from registers 0x24-25
	EM7180_GZ				= 0x26,  // int16_t from registers 0x26-27
	EM7180_GTIME			= 0x28,  // uint16_t from registers 0x28-29
	EM7180_QRateDivisor 	= 0x32,  // uint8_t
	EM7180_EnableEvents		= 0x33,
	EM7180_HostControl      = 0x34,
	EM7180_EventStatus      = 0x35,
	EM7180_SensorStatus     = 0x36,
	EM7180_SentralStatus    = 0x37,
	EM7180_AlgorithmStatus  = 0x38,
	EM7180_FeatureFlags     = 0x39,
	EM7180_ParamAcknowledge = 0x3A,
	EM7180_SavedParamByte0  = 0x3B,
	EM7180_SavedParamByte1  = 0x3C,
	EM7180_SavedParamByte2  = 0x3D,
	EM7180_SavedParamByte3  = 0x3E,
	EM7180_ActualMagRate    = 0x45,
	EM7180_ActualAccelRate  = 0x46,
	EM7180_ActualGyroRate   = 0x47,
	EM7180_ErrorRegister    = 0x50,
	EM7180_AlgorithmControl = 0x54,
	EM7180_MagRate          = 0x55,
	EM7180_AccelRate        = 0x56,
	EM7180_GyroRate         = 0x57,
	EM7180_LoadParamByte0   = 0x60,
	EM7180_LoadParamByte1   = 0x61,
	EM7180_LoadParamByte2   = 0x62,
	EM7180_LoadParamByte3   = 0x63,
	EM7180_ParamRequest     = 0x64,
	EM7180_ROMVersion1      = 0x70,
	EM7180_ROMVersion2      = 0x71,
	EM7180_RAMVersion1      = 0x72,
	EM7180_RAMVersion2      = 0x73,
	EM7180_ProductID        = 0x90,
	EM7180_RevisionID       = 0x91,
	EM7180_RunStatus        = 0x92,
	EM7180_UploadAddress    = 0x94, // uint16_t registers 0x94 (MSB)-5(LSB)
	EM7180_UploadData       = 0x96,
	EM7180_CRCHost          = 0x97,  // uint32_t from registers 0x97-9A
	EM7180_ResetRequest     = 0x9B,
	EM7180_PassThruStatus   = 0x9E,
	EM7180_PassThruControl  = 0xA0

} EM7180_Reg_Enum;

//--------------------------------------------------
// Union to convert 4 bytes in float
// TODO find a better way to achieve this
//-------------------------------------------------
typedef union _data {
  float f;
  char  s[4];
} floatcharUnion;

//--------------------------------------------------
// Struct of datas read from sensor
//--------------------------------------------------
typedef struct{
	floatcharUnion QX;
	floatcharUnion QY;
	floatcharUnion QZ;
	floatcharUnion QW;
	UInt16 QTime;
	Int16 MX;
	Int16 MY;
	Int16 MZ;
	Int16 MTime;
	Int16 AX;
	Int16 AY;
	Int16 AZ;
	Int16 ATime;
	Int16 GX;
	Int16 GY;
	Int16 GZ;
	Int16 GTime;
	float Heading;
	float Roll;
	float Pitch;
	UInt16 Event;
} EM7180_DataStruct;

//-------------------------------------------------------------------
// Basic setup of the sensor
//-------------------------------------------------------------------
void mEM7180_Setup(void);

//-------------------------------------------------------------------
// Run sensor algorithm
//-------------------------------------------------------------------
void mEM7180_Open(void);

//-------------------------------------------------------------------
// Stop sensor algorithm
//-------------------------------------------------------------------
void mEm7180_Close(void);

//-------------------------------------------------------------------
// Get status, for debug purpose
//-------------------------------------------------------------------
void mEM7180_readStatus();


//-------------------------------------------------------------------
// Read heading, pitch, roll and timestamp
// *aResultStruct: pointer over a structure of type EM7180_DataStruct in which the values are stored (QX, QY, QZ, QTime)
//-------------------------------------------------------------------
void mEm7180_GetEuler(EM7180_DataStruct *aResultStruct);


#endif /* SOURCES_MEM7180_H_ */
