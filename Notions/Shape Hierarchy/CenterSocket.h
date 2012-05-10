//	Copyright (C) 2009, 2011, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
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

#ifndef CENTER_SOCKET_H
#define CENTER_SOCKET_H

#include "Socket.h"

struct CenterSocket : public Socket
{
	/***************************
	* contructors & destructor *
	***************************/

	inline CenterSocket()																					// CenterSocket default constructor
	{
		// do nothing
	} // end CenterSocket default constructor


	inline CenterSocket(const CenterSocket &original)														// CenterSocket copy constructor
		:Socket(original)
	{
		// empty body
	} // end CenterSocket copy constructor


	inline CenterSocket(const Vector2D<> &point,double width,const Color<> &color, bool mark = false)		// CenterSocket constructor
		:Socket(point,width,color,mark)
	{
		// empty body
	} // end CenterSocket constructor


	inline CenterSocket(double x,double y,double width,const Color<> &color, bool mark = false)				// CenterSocket constructor
		:Socket(x,y,width,color,mark)
	{
		// empty body
	} // end CenterSocket constructor


	virtual ~CenterSocket()																					// CenterSocket destructor
	{
		// empty body
	} // end CenterSocket destructor



	/************
	* operators *
	************/

	virtual CenterSocket &operator = (const CenterSocket &original)											// operator =
	{
		Socket::operator =(original);
		return *this;
	} // end function operator =



	/*******************
	* member functions *
	*******************/

	virtual Vector2D<> &position()																		// position
	{
		parent->evaluateCenter();
		list<Plug *>::iterator begin = childs.begin();
		list<Plug *>::iterator end = childs.end();
		while(begin != end)
		{
			if((*begin)->permanent)
				(*begin)->Vector2D::operator =(*this);
			++begin;
		} // end while
		return *this;
	} // end function position


	virtual CenterSocket *clone() const																	// clone
	{
		return new CenterSocket(*this);
	} // end function clone



	/***************
	* data members *
	***************/

}; // end class CenterSocket

#endif // CENTER_SOCKET_H