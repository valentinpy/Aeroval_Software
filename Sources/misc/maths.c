/*
 * Copyright (C) 2015 Valentin Py
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

#include "def.h"
#include "maths.h"

//Calculate x^y
UInt32 maths_UInt32Power(UInt32 x, UInt8 y)
{
	UInt32 result = 0;
	if (y==0)
	{
		result = 1;
	}
	else
	{
		UInt8 i=0;
		result =1;
		for(i=0; i<y; i++)
		{
			result*=x;
		}
	}
	return result;
}

//Calculate x^y
float maths_floatPower(float x, UInt8 y)
{
	float result = 0;
	if (y==0)
	{
		result = 1;
	}
	else
	{
		UInt8 i=0;
		result =1;
		for(i=0; i<y; i++)
		{
			result*=x;
		}
	}
	return result;
}
