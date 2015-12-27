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

#ifndef SOURCES_MISC_FILTERS_H_
#define SOURCES_MISC_FILTERS_H_

#include "def.h"

//Median filter
//Return: output of the filter (middle value of the 3 inputs)
//Inputs: 3 values
Int16 filter_MedianFilter(Int16 a_0, Int16 a_1, Int16 a_2);

//Low pass filter
//Return: output of the filter
//Current value: new value (input)
//Previous value: previous output of the filter
//alpha: coeff of the filter. Between 0 and 1
float filter_lowPassFilter(float currentValue, float previousValue, float alpha);

#endif /* SOURCES_MISC_FILTERS_H_ */
