/*
 * mEm7180.h
 *
 *  Created on: 7 août 2015
 *      Author: valentinpy
 */

#ifndef SOURCES_MEM7180_H_
#define SOURCES_MEM7180_H_

#include "../interfaces/iI2C.h"
#include "../misc/def.h"
#include "mDelay.h"
#include "math.h"

#define EM7180_ADDR_W 			0x50
#define EM7180_ADDR_R			0x51
#define SetupValue_MagRate 		0x1E
#define SetupValue_AccelRate 	0x0A
#define SetupValue_GyroRate 	0x14

//--------------------------------------------------
// Enumération de l'adresse des registres 8 bits du capteur
//--------------------------------------------------
typedef enum{
	//TODO check if correct
	//8bits
	SentralStatus	= 0x37,
	ResetReq		= 0x9B,
	HostControl		= 0x34,
	MagRate			= 0x55,
	AccelRate		= 0x56,
	GyroRate		= 0x57,
	ActualMagRate	= 0x45,
	ActualAccelRate	= 0x46,
	ActualGyroRate	= 0x47,
	QRateDivisor	= 0x32,
	EnableEvents	= 0x33,
	EventStatus		= 0x35,
	AlgorithmControl= 0x54,
	AlgorithmStatus	= 0x38,
	PassThroughControl= 0xA0,
	PassThroughStatus= 0x9E,
	Product_ID		= 0x90,
	Revision_ID		= 0x91,

	//16 bits
	ROM_Version		= 0x70,
	RAM_Version		= 0x72,
	QTime			= 0x10,
	MX				= 0x12,
	MY				= 0x14,
	MZ				= 0x16,
	MTime			= 0x18,
	AX				= 0x1A,
	AY				= 0x1C,
	AZ				= 0x1E,
	ATime			= 0x20,
	GX				= 0x22,
	GY				= 0x24,
	GZ				= 0x26,
	GTime			= 0x28,

	//32bits
	QX				= 0x00,
	QY				= 0x04,
	QZ				= 0x08,
	QW				= 0x0C

} EM7180_Reg_Enum;

//--------------------------------------------------
// Union pour convertir 4 byte en float
//--------------------------------------------------

typedef union _data {
  float f;
  char  s[4];
} floatcharUnion;

//--------------------------------------------------
// Définition du type structure de données lorsqu'on lit toute les données du capteur
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
} EM7180_DataStruct;


// Basic setup of the sensor
//-------------------------------------------------------------------
void mEm7180_Setup(void);

//-------------------------------------------------------------------
// Run sensor algorithm
//-------------------------------------------------------------------
void mEm7180_Open(void);

//-------------------------------------------------------------------
// Stop sensor algorithm
//-------------------------------------------------------------------
void mEm7180_Close(void);

bool mEm7180_SetData8(EM7180_Reg_Enum aReg,UInt8 aVal);
UInt8 mEm7180_GetData8(EM7180_Reg_Enum aReg);
void mEm7180_GetQuaternions(EM7180_DataStruct *aResultStruct);
void mEm7180_GetEuler(EM7180_DataStruct *aResultStruct);






#endif /* SOURCES_MEM7180_H_ */
