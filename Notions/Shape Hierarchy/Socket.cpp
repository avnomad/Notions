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

#include "Socket.h"
#include "Plug.h"
#include <algorithm>
using std::remove;


Socket &Socket::connect(Plug *plug)																				// connect
{
	plug->parent = this;
	childs.push_back(plug);
	return *this;
} // end function connect


Socket &Socket::disconnect(Plug *plug)																			// disconnect
{
	plug->parent = 0;
	plug->permanent = false;
	childs.erase(remove(childs.begin(),childs.end(),plug),childs.end());

	return *this;
} // end function disconnect


Socket &Socket::disconnect()																					// disconnect
{
	list<Plug *>::iterator begin = childs.begin();
	list<Plug *>::iterator end = childs.end();
	while(begin != end)
	{
		(*begin)->parent = 0;
		(*begin)->permanent = false;
	} // end while
	childs.clear();
	return *this;
} // end function disconnect


Socket &Socket::move(const Vector2D<> &displacement)															// move
{
	list<Plug *>::iterator begin = childs.begin();
	list<Plug *>::iterator end = childs.end();
	while(begin != end)
	{
		**begin += displacement;
		++begin;
	} // end while

	*this += displacement;
	return *this;
} // end function move


Socket &Socket::moveDisconnect(const Vector2D<> &displacement)													// moveDisconnect
{
	disconnect() += displacement;
	return *this;
} // end function moveDisconnect
