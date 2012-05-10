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

#ifndef CORRECTION_H
#define CORRECTION_H

#include <Space-Time/Vector2D.h>
#include "event handlers.h"

class Correction : private Vector2D<>
{
	friend void displayNavigationGUI();														// displayNavigationGUI

	friend void Conversion::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void Conversion::mouseleftUp(const EventDispatcher &, double);					// mouseLeftUp
	friend void Conversion::mouseleftDown(const EventDispatcher &, double);					// mouseLeftDown

	friend void Creation::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void Creation::mouseleftUp(const EventDispatcher &, double);						// mouseLeftUp
	friend void Creation::mouseleftDown(const EventDispatcher &, double);					// mouseLeftDown

	friend void Navigation::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void Navigation::mouseleftUp(const EventDispatcher &, double);					// mouseLeftUp
	friend void Navigation::mouseleftDown(const EventDispatcher &, double);					// mouseLeftDown

	friend void Selection::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void Selection::mouseleftUp(const EventDispatcher &, double);					// mouseLeftUp
	friend void Selection::mouseleftDown(const EventDispatcher &, double);					// mouseLeftDown

	friend void Configuration::mouseMove(const EventDispatcher &, double);					// mouseMove
	friend void Configuration::mouseleftUp(const EventDispatcher &, double);				// mouseLeftUp
	friend void Configuration::mouseleftDown(const EventDispatcher &, double);				// mouseLeftDown

	//friend void defaultPainter(const EventDispatcher & , double);							// defaultPainter
	//friend void navigationPainter(const EventDispatcher &, double);						// navigationPainter
	friend void suspendProjectionMatrix();													// suspendProjectionMatrix
	friend void displayGUI();																// displayGUI
	friend int WINAPI WinMain(InstanceHandle , InstanceHandle , CHAR * , int );				// WinMain
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Correction()																// Correction default constructor
	{
		// empty body
	} // end Correction default constructor


	inline ~Correction()															// Correction destructor
	{
		// empty body
	} // end Correction destructor


private:

	inline Correction(const Correction &original)									// Correction copy constructor
		:Vector2D(original)
	{
		// empty body
	} // end Correction copy constructor



	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/
	/***************
	* data members *
	***************/

	double maxY;
}; // end class Correction

#endif // CORRECTION_H