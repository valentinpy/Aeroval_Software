/*
 File name 			:	iDio.c
 Author and date 	:	Fivaz Timothée, 22.06.2015

 Description in the header file iDio.h

 -----------------------------------------------------------------------------
 */

#include "iDio.h"
#include "derivative.h"

/*-----------------------------------------------------------------------------
 / Pin Alternate configuration
 /-----------------------------------------------------------------------------*/
void iDio_PinConfig(PortIOEnum aPort, PinNbEnum aPinNb,	PinFunctionEnum aPinFunc) {
	unsigned long *aPortPtr;

	/* Pointer selection */
	switch (aPort) {
	// DDRA
	case kPortA:
		aPortPtr = (unsigned long *) (PORTA_BASE + (aPinNb * 4));
		break;

		// DDRB
	case kPortB:
		aPortPtr = (unsigned long *) (PORTB_BASE + (aPinNb * 4));
		break;

		// DDRC
	case kPortC:
		aPortPtr = (unsigned long *) (PORTC_BASE + (aPinNb * 4));
		break;

		// DDRD
	case kPortD:
		aPortPtr = (unsigned long *) (PORTD_BASE + (aPinNb * 4));
		break;

		// DDRE
	case kPortE:
		aPortPtr = (unsigned long *) (PORTE_BASE + (aPinNb * 4));
		break;
	}

	// MUX reset, bits 10-8 in PORTx_PCRn
	*aPortPtr &= 0xFFFFF8FF;
	// Alternative selection
	*aPortPtr |= aPinFunc;
}

//-----------------------------------------------------------------------------
// Configuration des Ports en entrée ou en sortie
// aPort: le port IO que l'on veut configurer
// aMask: choix des pins du port sur lesquelles on veut agir (si bit à 1)
// aDir:  choix de la direction des pins sélectionnées avec aMask
//-----------------------------------------------------------------------------
void iDio_SetPortDirection(PortIOEnum aPort, IoMaskEnum aMask,
		IoDirectionEnum aDir) {
	unsigned long *aPortPtr;

	// Configuration du pointeur selon le port passé en paramètre
	switch (aPort) {
	// DDRA
	case kPortA:
		aPortPtr = (unsigned long *) (&GPIOA_PDDR );
		break;

		// DDRB
	case kPortB:
		aPortPtr = (unsigned long *) (&GPIOB_PDDR );
		break;

		// DDRC
	case kPortC:
		aPortPtr = (unsigned long *) (&GPIOC_PDDR );
		break;

		// DDRD
	case kPortD:
		aPortPtr = (unsigned long *) (&GPIOD_PDDR );
		break;

		// DDRE
	case kPortE:
		aPortPtr = (unsigned long *) (&GPIOE_PDDR );
		break;
	}

	// Input or output configuration
	if (kIoOutput == aDir) {
		*aPortPtr |= aMask;
	} else if (kIoInput == aDir) {
		*aPortPtr &= ~aMask;
	}
}

//-----------------------------------------------------------------------------
// Affectation de l'état des pins du port configurées en sortie
// aMask:   choix des pins du port sur lesquelles on veut agir (si bit à 1)
// aState:  choix de l'état des bits du port désirés
//-----------------------------------------------------------------------------
void iDio_SetPort(PortIOEnum aPort, IoMaskEnum aMask, IoStateEnum aState) {
	unsigned long *aPortPtr;

	// Configuration du pointeur selon le port passé en paramètre
	switch (aPort) {
	// DDRA
	case kPortA:
		aPortPtr = (unsigned long *) (&GPIOA_PDOR );
		break;

		// DDRB
	case kPortB:
		aPortPtr = (unsigned long *) (&GPIOB_PDOR );
		break;

		// DDRC
	case kPortC:
		aPortPtr = (unsigned long *) (&GPIOC_PDOR );
		break;

		// DDRD
	case kPortD:
		aPortPtr = (unsigned long *) (&GPIOD_PDOR );
		break;

		// DDRE
	case kPortE:
		aPortPtr = (unsigned long *) (&GPIOE_PDOR );
		break;
	}

	// Configuration de l'état des bits du port configurés en sortie
	if (kIoOn == aState) {
		*aPortPtr |= aMask;
	} else if (kIoOff == aState) {
		*aPortPtr &= ~aMask;
	}
}

//-----------------------------------------------------------------------------
// Changmenet de l'état des pins du port configurées en sortie
// aMask:   choix des pins du port sur lesquelles on veut agir (si bit à 1)
//-----------------------------------------------------------------------------
void iDio_TogglePort(PortIOEnum aPort, IoMaskEnum aMask) {
	unsigned long *aPortPtr;

	// Configuration du pointeur selon le port passé en paramètre
	switch (aPort) {
	// DDRA
	case kPortA:
		aPortPtr = (unsigned long *) (&GPIOA_PTOR );
		break;

		// DDRB
	case kPortB:
		aPortPtr = (unsigned long *) (&GPIOB_PTOR );
		break;

		// DDRC
	case kPortC:
		aPortPtr = (unsigned long *) (&GPIOC_PTOR );
		break;

		// DDRD
	case kPortD:
		aPortPtr = (unsigned long *) (&GPIOD_PTOR );
		break;

		// DDRE
	case kPortE:
		aPortPtr = (unsigned long *) (&GPIOE_PTOR );
		break;
	}

	//Toggle output
	*aPortPtr |= aMask;
}


//-----------------------------------------------------------------------------
// Lecture de l'état des pins du port configurées en entrée
// aMask:   de quelle pin ou veut l'état 
// retour:  état de la pin --> true ou false
//-----------------------------------------------------------------------------
bool iDio_GetPort(PortIOEnum aPort, IoMaskEnum aMask) {
	bool aRet = false;
	unsigned long *aPortPtr;

	// Configuration du pointeur selon le port passé en paramètre
	switch (aPort) {
	// DDRA
	case kPortA:
		aPortPtr = (unsigned long *) (&GPIOA_PDIR );
		break;

		// DDRB
	case kPortB:
		aPortPtr = (unsigned long *) (&GPIOB_PDIR );
		break;

		// DDRC
	case kPortC:
		aPortPtr = (unsigned long *) (&GPIOC_PDIR );
		break;

		// DDRD
	case kPortD:
		aPortPtr = (unsigned long *) (&GPIOD_PDIR );
		break;

		// DDRE
	case kPortE:
		aPortPtr = (unsigned long *) (&GPIOE_PDIR );
		break;
	}

	// Lecture de l'état des bit du port configurés en entrée
	aRet = (bool) ((*aPortPtr & aMask) == aMask);

	return aRet;
}

//-----------------------------------------------------------------------------
// Read port E input pin
// return:  data in register value
//-----------------------------------------------------------------------------
UInt32 iDio_GetPortE(void)
{
  return GPIOE_PDIR;
}
