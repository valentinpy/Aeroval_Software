/*
 File name 			:	iPit.h
 Author and date 	:	Fivaz Timoth�e, 22.06.2015

 Description 		:	Interface for the timers

 -----------------------------------------------------------------------------
 */

#ifndef __iPit__
#define __iPit__

#include "../misc/def.h"
#include "MK64F12.h"

// Maximum delay number
#define kNbDelays 			20
#define kNbTickers100Us		3

#define PIT0IRQ	48
#define PIT1IRQ	49
#define PIT2IRQ	50
#define PIT3IRQ	51


// PIT enum
typedef enum
{
	kPit0 = 0, kPit1 = 1, kPit2 = 2, kPit3 = 3
} PitEnum;

// Delay struct
typedef struct
{
	UInt16 Counter;
	bool isFree;
	bool DelayDone;
} CounterStruct;

typedef struct
{
	CounterStruct CounterTab[kNbDelays];
} DlyStruct;

static DlyStruct sDly[3];
extern UInt32 sTicker100Us[kNbTickers100Us];


//------------------------------------------------------------
// PIT setup
// aPit					: which PIT (0 to 3)
// aPeriodeMs  	: PIT period in ms
//------------------------------------------------------------
void iPit_Config(PitEnum aPit,UInt16 aPeriodeUs);

//------------------------------------------------------------
// Start Pit
// aPit		: which PIT
//------------------------------------------------------------
void iPit_StartPit(PitEnum aPit);

//------------------------------------------------------------
// Setup the delay structure
// aPit		: which PIT
//------------------------------------------------------------
void iPit_InitDelay(PitEnum aPit);

//------------------------------------------------------------
// Get and setup a delay
// aPit		: which PIT
// aDelay	: the delay (ms)
// Retour	: the delay number
//------------------------------------------------------------
Int16 iPit_GetDelay(PitEnum aPit,UInt16 aDelay);

//------------------------------------------------------------
// Check if the delay is done
// aPit			: which PIT
// aDelayNb	: the delay number
// Retour		: state of the delay
//------------------------------------------------------------
bool iPit_IsDelayDone(PitEnum aPit,UInt16 aDelayNb);

//------------------------------------------------------------
// Release a delay
// aPit			: which PIT
// aDelayNb	: the delay number
//------------------------------------------------------------
void iPit_DelayRelease(PitEnum aPit,UInt16 aDelayNb);

//------------------------------------------------------------
// Restart un delay
// aPit			: which PIT
// aDelayNb	: the delay number
// aDelay		: the delay time
//------------------------------------------------------------
void iPit_ReStart(PitEnum aPit,UInt16 aDelayNb,UInt16 aDelay);


#endif
