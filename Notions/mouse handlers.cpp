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

#include "configuration mouse.h"
#include "conversion mouse.h"
#include "creation mouse.h"
#include "navigation mouse.h"
#include "selection mouse.h"

#include "Shape Hierarchy.h"

Socket *findSocket(const Vector2D<> &point)												// findSocket
{
	Socket *socket;
	list<Region *>::iterator begin = shapes.regions.begin();
	list<Region *>::iterator end = shapes.regions.end();
	while(begin != end)
	{
		if(socket = (*begin)->nearSocket(point,unit))
			return socket;
		++begin;
	} // end while
	return 0;
} // end function findSocket
