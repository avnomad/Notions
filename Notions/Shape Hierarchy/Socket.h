//	Copyright (C) 2009, 2011, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
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

#ifndef SOCKET_H
#define SOCKET_H

// includes
#include "Vertex.h"
#include "Region.h"

struct Plug;

struct Socket : public Vertex
{
	/***************************
	* contructors & destructor *
	***************************/

	inline Socket()																								// Socket default constructor
	{
		// do nothing
	} // end Socket default constructor


	inline Socket(const Socket &original)																		// Socket copy constructor
		:Vertex(original),parent(original.parent),childs(original.childs)
	{
		// empty body
	} // end Socket copy constructor


	inline Socket(const Vector2D<> &point,double width,const Color<> &color, bool mark = false)					// Socket constructor
		:Vertex(point,width,color,mark),parent(0)
	{
		// empty body
	} // end Socket constructor


	inline Socket(double x,double y,double width,const Color<> &color, bool mark = false)						// Socket constructor
		:Vertex(x,y,width,color,mark),parent(0)
	{
		// empty body
	} // end Socket constructor


	virtual ~Socket()																							// Socket destructor
	{
		disconnect();
	} // end Socket destructor




	/************
	* operators *
	************/

	virtual Socket &operator = (const Socket &original)															// operator =
	{
		Vertex::operator =(original);
		parent = original.parent;
		childs = original.childs;
		return *this;
	} // end function operator =


	/*******************
	* member functions *
	*******************/

	inline Socket &setParent(Region *region)																	// setParent
	{
		parent = region;
		return *this;
	} // end function setParent


	inline Socket &setChilds(const list<Plug *> &plugs)															// setChilds
	{
		childs = plugs;
		return *this;
	} // end function setChilds


	Socket &connect(Plug *plug);																				// connect
	Socket &disconnect(Plug *plug);																				// disconnect
	Socket &disconnect();																						// disconnect


	inline Socket &notify(const Vector2D<> &displacement)														// notify
	{
		parent->move(displacement);
		return *this;
	} // end function notify


	virtual Socket &Socket::move(const Vector2D<> &displacement);												// move
	virtual Socket &Socket::moveDisconnect(const Vector2D<> &displacement);										// moveDisconnect


	virtual Socket *clone() const																				// clone
	{
		return new Socket(*this);
	} // end function clone



	/***************
	* data members *
	***************/

	Region *parent;
	list<Plug *> childs;

}; // end class Socket

#endif // SOCKET_H