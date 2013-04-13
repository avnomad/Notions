//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
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

struct Statistics
{
	// member functions
	Statistics()
		:x(0),y(0),xy(0),x2(0),n(0),a(0),b(0)
	{
		// empty body
	} // end Statistics default constructor

	Statistics(const Statistics &original)
		:x(original.x),y(original.y),xy(original.xy),x2(original.x2),n(original.n),a(original.a),b(original.b)
	{
		// empty body
	} // end Statistics copy constructor

	Statistics(GLdouble sx , GLdouble sy , GLdouble sxy , GLdouble sx2 , unsigned int sn , GLdouble sa , GLdouble sb)
		:x(sx),y(sy),xy(sxy),x2(sx2),n(sn),a(sa),b(sb)
	{
		// empty body
	} // end Statistics constructor

	Statistics &operator=(const Statistics &original)
	{
		x = original.x;
		y = original.y;
		xy = original.xy;
		x2 = original.x2;
		n = original.n;
		a = original.a;
		b = original.b;
		return *this;
	} // end function operator =

	// data members
	GLdouble x;
	GLdouble y;
	GLdouble xy;
	GLdouble x2;
	unsigned int n;
	GLdouble a;
	GLdouble b;	
}; // end class Statistics