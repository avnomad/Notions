//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Notions.
 *
 *	Notions is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Notions is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Notions.  If not, see <http://www.gnu.org/licenses/>.
 */

// includes
#include "global.h"

Triple getSpeed(const Triple &final , const Triple &initial)
{
	GLdouble temp = final.t - initial.t;

	return Triple((final.x - initial.x) / temp , (final.y - initial.y) / temp , final.t);
} // end function getSpeed

GLdouble getMagnitude(const Triple &vector)
{
	return sqrt(vector.x*vector.x + vector.y*vector.y);
} // end function getMagnitude

Statistics *add_to_sums(Statistics *statPtr , const Triple &point)
{
	statPtr->x += point.x;
	statPtr->y += point.y;
	statPtr->xy += point.x*point.y;
	statPtr->x2 += point.x*point.x;
	return statPtr;
} // end function add_to_sums