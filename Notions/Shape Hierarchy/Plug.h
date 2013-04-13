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

#ifndef PLUG_H
#define PLUG_H

// includes
#include "Socket.h"

// protorypes
Socket *findSocket(const Vector2D<> &point);

struct Plug : public Vertex
{
	/***************************
	* contructors & destructor *
	***************************/

	inline Plug()																							// Plug default constructor
	{
		// do nothing
	} // end Plug default constructor


	inline Plug(const Plug &original)																		// Plug copy constructor
		:Vertex(original),parent(original.parent),permanent(original.permanent)
	{
		// empty body
	} // end Plug copy constructor


	inline Plug(const Vector2D<> &point,double width,const Color<> &color, bool mark = false)				// Plug constructor
		:Vertex(point,width,color,mark),parent(0),permanent(false)
	{
		// empty body
	} // end Plug constructor


	inline Plug(double x,double y,double width,const Color<> &color, bool mark = false)						// Plug constructor
		:Vertex(x,y,width,color,mark),parent(0),permanent(false)
	{
		// empty body
	} // end Plug constructor


	virtual ~Plug()																							// Plug destructor
	{
		disconnect();
	} // end Plug destructor



	/************
	* operators *
	************/

	virtual Plug &operator = (const Plug &original)															// operator =
	{
		Vertex::operator =(original);
		parent = original.parent;
		permanent = original.permanent;
		return *this;
	} // end function operator =



	/*******************
	* member functions *
	*******************/

	inline Plug &setParent(Socket *socket)																	// setParent
	{
		parent = socket;
		return *this;
	} // end function setParent


	inline Plug &setPermanent(bool isPermanent)																// setPermanent
	{
		permanent = isPermanent;
		return *this;
	} // end function setPermanent


	inline Plug &connect(Socket *socket)																	// connect
	{
		socket->connect(this);
		parent->marked = true;
		return *this;
	} // end function connect


	inline Plug &disconnect()																				// disconnect
	{
		parent->marked = false;
		parent->disconnect(this);
		return *this;
	} // end function disconnect


	inline Plug &moveConnect(const Vector2D<> &displacement)												// moveConnect
	{							// should not be called if there is already a parent
		Socket *socket;
		*this += displacement;
		if(socket = findSocket(*this))
			connect(socket);
		return *this;
	} // end function moveConnect



	virtual Plug &display()																					// display
	{
		if(!parent)	Vertex::display();
		return *this;
	} // end function display


	virtual Plug &display(double zoom)																		// display
	{
		if(!parent)	Vertex::display(zoom);
		return *this;
	} // end function display


	virtual Plug &move(const Vector2D<> &displacement)														// move
	{
		if(!parent)
			moveConnect(displacement);
		else
			if(permanent)
				parent->notify(displacement);
			else
			{
				disconnect();
				moveConnect(displacement);
			} // end else
		return *this;
	} // end function move


	virtual Plug &moveDisconnect(const Vector2D<> &displacement)											// moveDisconnect
	{
		if(parent) disconnect();	// if you have a parent get rid of it.
		
		*this += displacement;
		return *this;
	} // end function moveDisconnect


	virtual Vertex *nearVertex(const Vector2D<> &point , double distance2)									// nearVertex
	{
		if(!parent) return Vertex::nearVertex(point,distance2);
		else return 0;
	} // end function nearVertex


	virtual Plug *clone() const																				// clone
	{
		return new Plug(*this);
	} // end function clone


	virtual Plug &work()																					// work
	{
		if(parent) parent->marked = true;
		return *this;
	} // end function work


	virtual Plug &rest()																					// rest
	{
		if(parent)
		{
			parent->marked = false;
			permanent = true;
			Vector2D::operator =(*parent);
		} // end if
		return *this;
	} // end function rest


	virtual Vector2D<> &position()																			// position
	{
		if(parent) return parent->position();
		else return *this;
	} // end function position



	/***************
	* data members *
	***************/

	Socket *parent;
	bool permanent;

}; // end class Plug

#endif // PLUG_H