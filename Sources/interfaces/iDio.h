/*
 * Copyright (C) 2015 Valentin Py
 * Copyright (C) 2015 Timothée Fivaz
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

#ifndef IDIO_H_
#define IDIO_H_

#include "../misc/def.h"
#include "../misc/derivative.h"

// Direction des IO --> entrée ou sortie
typedef enum {
	kIoOutput, kIoInput
} IoDirectionEnum;

// Masque des IO
typedef enum {
	kMaskIo0 = 0x01,
	kMaskIo1 = 0x02,
	kMaskIo2 = 0x04,
	kMaskIo3 = 0x08,
	kMaskIo4 = 0x10,
	kMaskIo5 = 0x20,
	kMaskIo6 = 0x40,
	kMaskIo7 = 0x80,
	kMaskIo8 = 0x100,
	kMaskIo9 = 0x200,
	kMaskIo10 = 0x400,
	kMaskIo11 = 0x800,
	kMaskIo12 = 0x1000,
	kMaskIo13 = 0x2000,
	kMaskIo14 = 0x4000,
	kMaskIo15 = 0x8000,
	kMaskIo16 = 0x10000,
	kMaskIo17 = 0x20000,
	kMaskIo18 = 0x40000,
	kMaskIo19 = 0x80000,
	kMaskIo20 = 0x100000,
	kMaskIo21 = 0x200000,
	kMaskIo22 = 0x400000,
	kMaskIo23 = 0x800000,
	kMaskIo24 = 0x1000000,
	kMaskIo25 = 0x2000000,
	kMaskIo26 = 0x4000000,
	kMaskIo27 = 0x8000000,
	kMaskIo28 = 0x10000000,
	kMaskIo29 = 0x20000000,
	kMaskIo30 = 0x40000000,
	kMaskIo31 = 0x80000000,
	kMaskIoAll = 0xffffffff
} IoMaskEnum;

// Les diff�rents port IO
typedef enum {
	kPortA, kPortB, kPortC, kPortD, kPortE
} PortIOEnum;

// Etat des IO configur�s en sortie
typedef enum {
	kIoOn, kIoOff
} IoStateEnum;

// Fonctionnalit� des pins
typedef enum {
	kAlternate0 = 0,
	kAlternate1 = 0x100,
	kAlternate2 = 0x200,
	kAlternate3 = 0x300,
	kAlternate4 = 0x400,
	kAlternate5 = 0x500,
	kAlternate6 = 0x600,
	kAlternate7 = 0x700
} PinFunctionEnum;

// Num�ro des PINS
typedef enum {
	kPin0 = 0,
	kPin1,
	kPin2,
	kPin3,
	kPin4,
	kPin5,
	kPin6,
	kPin7,
	kPin8,
	kPin9,
	kPin10,
	kPin11,
	kPin12,
	kPin13,
	kPin14,
	kPin15,
	kPin16,
	kPin17,
	kPin18,
	kPin19,
	kPin20,
	kPin21,
	kPin22,
	kPin23,
	kPin24,
	kPin25,
	kPin26,
	kPin27,
	kPin28,
	kPin29,
	kPin30,
	kPin31
} PinNbEnum;

//-----------------------------------------------------------------------------
// Enable du clock des GPIO
//-----------------------------------------------------------------------------
void iDio_EnablePortClk(void);

//-----------------------------------------------------------------------------
// Configuration de la fonctionnalit� de chaque PIN
//-----------------------------------------------------------------------------
void iDio_PinConfig(PortIOEnum aPort, PinNbEnum aPinNb,
		PinFunctionEnum aPinFunc);

//-----------------------------------------------------------------------------
// Configuration des Ports en entr�e ou en sortie
// aPort: le port IO que l'on veut configurer
// aMask: choix des pins du port sur lesquelles on veut agir (si bit � 1)
// aDir:  choix de la direction des pins s�lectionn�es avec aMask
//-----------------------------------------------------------------------------
void iDio_SetPortDirection(PortIOEnum aPort, IoMaskEnum aMask,
		IoDirectionEnum aDir);

//-----------------------------------------------------------------------------
// Affectation de l'�tat des pins du port configur�es en sortie
// aMask:   choix des pins du port sur lesquelles on veut agir (si bit � 1)
// aState:  choix de l'�tat des bits du port d�sir�s
//-----------------------------------------------------------------------------
void iDio_SetPort(PortIOEnum aPort, IoMaskEnum aMask, IoStateEnum aState);

//-----------------------------------------------------------------------------
// Changemnet de l'�tat des pins du port configur�es en sortie
// aMask:   choix des pins du port sur lesquelles on veut agir (si bit � 1)
//-----------------------------------------------------------------------------
void iDio_TogglePort(PortIOEnum aPort, IoMaskEnum aMask);

//-----------------------------------------------------------------------------
// Lecture de l'�tat des pins du port configur�es en entr�e
// aMask:   de quelle pin ou veut l'�tat 
// retour:  �tat de la pin --> true ou false
//-----------------------------------------------------------------------------
bool iDio_GetPort(PortIOEnum aPort, IoMaskEnum aMask);

//-----------------------------------------------------------------------------
// Read port E input pin
// return:  data in register value
//-----------------------------------------------------------------------------
UInt32 iDio_GetPortE(void);


#endif /* IDIO_H_ */
