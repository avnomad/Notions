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

struct Triple	// check
{
	// member functions
	Triple(){}	// default constructor

	Triple(const Triple &original)
		:x(original.x),y(original.y),t(original.t)
	{
		// empty body
	} // end Triple copy constructor

	Triple(GLdouble px , GLdouble py , GLdouble pt)
		:x(px),y(py),t(pt)
	{
		// empty body
	} // end Triple constructor

	Triple &operator=(const Triple &original)
	{
		x = original.x;
		y = original.y;
		t = original.t;
		return *this;
	} // end function operator =

	Triple &operator=(const Statistics &stats)	// dummy function to work around a problem with
	{											// adjacent_difference assigning the first element as is.
		return *this;
	} // end function operator =
	
	Triple operator-(const Triple &right) const
	{
		return Triple( this->x - right.x , this->y - right.y , this->t - right.t );
	} // end function operator-

	// data members
	GLdouble x;
	GLdouble y;
	GLdouble t;
}; // end class Triple