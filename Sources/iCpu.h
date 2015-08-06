/*
------------------------------------------------------------
Copyright 2003-2012 Haute école ARC Ingéniérie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name 		: 	iCpu.h	
Author and date :	Monnerat Serge   23.11.2011
Modified 		: 	Billmann Maurice 01.06.2015

But : Interface de la CPU 

-----------------------------------------------------------------------------
Historique:
-----------------------------------------------------------------------------

$History: $
01.06.2015 : Réecriture des fonctions pour carte FRDM-K64F. 1x I²C (joystick), 
1x SPI (Module RF), 1x UART (Bluetooth), 16 PWM (12 Sorties, 4 Entrées).
Configuration des alternatives du pinout.

-----------------------------------------------------------------------------
*/


#ifndef __ICPU__
#define __ICPU__

#include "def.h"

void iCpu_SysInit(void);

#endif
