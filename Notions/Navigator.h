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

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "event handlers.h"
#include <Space-Time/Vector2D.h>

class Navigator
{
	friend void defaultPainter(const EventDispatcher &, double);							// defaultPainter
	friend void Navigation::mouseleftDown(const EventDispatcher &, double);					// mouseleftDown
	friend void Navigation::mouseleftUp(const EventDispatcher &, double);					// mouseleftUp
	friend void Navigation::mouseMove(const EventDispatcher &, double);						// mouseMove
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Navigator()															// Navigator default constructor
		:dispositioning(false),rotating(false),zooming(false)
	{
		// do nothing
	} // end Navigator default constructor


	inline ~Navigator()															// Navigator destructor
	{
		// empty body
	} // end Navigator destructor


private:

	inline Navigator(const Navigator &original)									// Navigator copy constructor
		:dispositioning(original.dispositioning),
		rotating(original.rotating),zooming(original.zooming),
		oldPosition(original.oldPosition)
	{
		// empty body
	} // end Navigator copy constructor



	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/


	/***************
	* data members *
	***************/

	bool dispositioning;
	bool rotating;
	bool zooming;
	Vector2D<> oldPosition;

}; // end class Navigator

#endif // NAVIGATOR_H