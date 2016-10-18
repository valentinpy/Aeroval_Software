/*
 * Copyright (C) 2015 Valentin Py
 * Copyright (C) 2014 Thimothée Fivaz
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

#ifndef DEF_H_
#define DEF_H_

//------------------------------------------------------------
// bool and standard types
//------------------------------------------------------------
typedef int bool;
typedef bool BOOL;

#define TRUE 1
#define true 1
#define FALSE 0
#define false 0

typedef unsigned char			UInt8;  /*  8 bits */
typedef unsigned short			UInt16; /* 16 bits */
typedef unsigned long			UInt32; /* 32 bits */
typedef unsigned long long		UInt64; /* 64 bits */

typedef char			    	Int8;   /*  8 bits */
typedef short	        		Int16;  /* 16 bits */
typedef long		            Int32;  /* 32 bits */
typedef long long            	Int64;  /* 64 bits */

typedef volatile Int8			VInt8;  /*  8 bits */
typedef volatile Int16			VInt16; /* 16 bits */
typedef volatile Int32			VInt32; /* 32 bits */
typedef volatile Int64			VInt64; /* 64 bits */

typedef volatile UInt8			VUInt8;  /*  8 bits */
typedef volatile UInt16			VUInt16; /* 16 bits */
typedef volatile UInt32			VUInt32; /* 32 bits */
typedef volatile UInt32       	UINT32;
typedef volatile UInt8       	UINT8;
typedef volatile Int8       	INT8;
typedef volatile UInt16       	UINT16;
typedef volatile UInt64       	UINT64;
typedef volatile Int64       	INT64;
typedef volatile Int16       	INT16;
typedef volatile Int32       	INT32;
typedef volatile Int8       	CHAR;

typedef unsigned char 			Byte;
typedef unsigned long 			LWord;
typedef unsigned short 			Word;

//------------------------------------------------------------
// Sensor data struct
//------------------------------------------------------------
typedef struct
{
	//-----------------------------------------------------------
	// Raw values
	//-----------------------------------------------------------

	UInt8 MagOutput;			//Does the sensor output mag ?
	UInt16 RawMagX;
	UInt16 RawMagY;
	UInt16 RawMagZ;
	UInt16 RawMagDeltaTime;

	UInt8 AccelOutput;
	UInt16 RawAccelX;
	UInt16 RawAccelY;
	UInt16 RawAccelZ;
	UInt16 RawAccelDeltaTime;

	UInt8 GyroOutput;
	UInt16 RawGyroX;
	UInt16 RawGyroY;
	UInt16 RawGyroZ;
	UInt16 RawGyroDeltaTime;

	UInt8 TempOutput;
	UInt16 RawTemp;

	UInt8 PressureOutput;
	UInt16 RawPressure;

	//-----------------------------------------------------------
	// Computed by sensor values
	//-----------------------------------------------------------

	Int8 EulerOutput;			//Does the sensor output Euler ?
	Int32 EulerHeading_urad;		//microrad
	Int32 EulerRoll_urad;			//microrad
	Int32 EulerPitch_urad;			//microrad
	Int32 EulerDeltaTime_us;		//microseconds since last value

	Int8 QOutput;				//Does the sensor output quaternions ?
	Int32 QW;						//TODO Warn: choose scale factor
	Int32 QX;						//TODO Warn: choose scale factor
	Int32 QY;						//TODO Warn: choose scale factor
	Int32 QZ;						//TODO Warn: choose scale factor
	Int8 QDeltaTime;

	Int8 AltitudeOutput;		//Does the sensor output altitude?
	Int32 Altitude;

} gIMUSensorStruct;


//------------------------------------------------------------
// Constants
//------------------------------------------------------------
// Core clock
#define kClockCpu 		100.0 // 100MHz
#define kClockBus		50.0 //50 MHz
#define kClockCpukHz 	100000 // 100MHz
#define kClockBuskHz	50000 // 50MHz

//Monitoring
#define kMonitoringStringLength	80

//Battery
#define kBatLevelWarning (10800)	//Low level battery threshold

//TODO Improv: move elsewhere
//Struct that contains the PID datas for each PID
typedef struct PIDdataStruct{
	float aKp, aKi, aKd;
	float aPreviousError;
	float aIntegral;
	UInt16 aPreviousTime;
	float aWindupGuard;
} PIDdata;


//------------------------------------------------------------
// Macros
//------------------------------------------------------------
// Enable maskable interrupts
#define EnableInterrupts __asm(" CPSIE i");

// Disable maskable interrupts
#define DisableInterrupts __asm(" CPSID i");

#endif /* DEF_H_ */
