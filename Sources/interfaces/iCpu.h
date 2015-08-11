/*
------------------------------------------------------------
Copyright 2003-2012 Haute �cole ARC Ing�ni�rie, Switzerland. 
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
01.06.2015 : R�ecriture des fonctions pour carte FRDM-K64F. 1x I�C (joystick), 
1x SPI (Module RF), 1x UART (Bluetooth), 16 PWM (12 Sorties, 4 Entr�es).
Configuration des alternatives du pinout.

-----------------------------------------------------------------------------
*/


#ifndef __ICPU__
#define __ICPU__

#include "../misc/def.h"
#include "../misc/derivative.h"

void iCpu_SysInit(void);

#endif
