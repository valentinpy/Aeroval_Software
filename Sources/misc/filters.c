/*
 * filters.c
 *
 *  Created on: 12 nov. 2015
 *      Author: valentinpy
 */

#include "filters.h"
#include "def.h"

Int16 misc_MedianFilter(Int16 a_0, Int16 a_1, Int16 a_2)
{
	Int16 middle;
	if((a_0<=a_1)&&(a_0<=a_2))
	{
		middle = (a_1<=a_2) ? a_1 : a_2;
	}
	else if((a_1<=a_0)&&(a_1<=a_2))
	{
		middle = (a_0<=a_2) ? a_0 : a_2;
	}
	else
	{
		middle=(a_0<=a_1) ? a_0: a_1;
	}
	 return middle;
}
