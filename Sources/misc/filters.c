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
