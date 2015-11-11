/*
 * def.h
 *
 *  Created on: Jun 15, 2015
 *      Author: timothee.fivaz
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

//TODO move elsewhere
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
