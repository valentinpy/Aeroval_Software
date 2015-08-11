/*
------------------------------------------------------------
Copyright 2003-2015 Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name : 		mCpu.c	
Authors and date :	Serge Monnerat 	26.09.2014
					Valentin Py		15.06.2015

Goal :
Description in the header

*/

#include "mCpu.h"


//-----------------------------------------------------------------------
// Low level CPU setup
//-----------------------------------------------------------------------
void mCpu_Setup(void)
{
	// PLL configuration
	iCpu_SysInit();
}

