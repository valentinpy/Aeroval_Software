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

#ifndef SOURCES_STRING_H_
#define SOURCES_STRING_H_

//Convert a UInt8 to array of char (hexadecimal)
//output must be a pointer to an array of char with at least 2 free elements after the pointer
void string_UInt8toCharArrayHex(UInt8 input, char* output);

//Convert a UInt8 to array of 3 char (decimal)
//output must be a pointer to an array of char with at least 3 free elements after the pointer
void string_UInt8toCharArrayDec(UInt8 input, char* output);

//Convert a UInt16 to array of 5 char (decimal)
//output must be a pointer to an array of char with at least 5 free elements after the pointer
void string_UInt16toCharArrayDec(UInt16 input, char* output);

//Convert a UInt32 to array of 10 char (decimal)
//output must be a pointer to an array of char with at least 10 free elements after the pointer
void string_UInt32toCharArrayDec(UInt32 input, char* output);

//Convert a Int32 to array of 10 char (decimal), preceded with the sign
//output must be a pointer to an array of char with at least 11 free elements after the pointer
void string_Int32toCharArrayDec(Int32 input, char* output);

#endif /* SOURCES_TESTS_H_ */
