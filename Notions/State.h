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

#ifndef STATE_H
#define STATE_H

#include "event handlers.h"

enum Mode { CONVERSION,CREATION,NAVIGATION,SELECTION,CONFIGURATION };

class State
{
	friend inline void displayCursor();																// displayCursor
	friend void displayShapes();																	// displayShapes
	friend void displayGUI();																		// displayGUI

	friend void Creation::mouseMove(const EventDispatcher &, double);								// mouseMove
	friend void Creation::mouseleftUp(const EventDispatcher &, double);								// mouseLeftUp
	friend void Creation::mouseleftDown(const EventDispatcher &, double);							// mouseLeftDown
	friend void Conversion::mouseMove(const EventDispatcher &, double);								// mouseMove
	friend void Conversion::mouseleftUp(const EventDispatcher &, double);							// mouseleftUp
	friend void Conversion::mouseleftDown(const EventDispatcher &, double);							// mouseleftDown

	friend void Conversion::leftDown(const EventDispatcher &dispatcher, double time);				// leftDown
	friend void Conversion::rightDown(const EventDispatcher &dispatcher, double time);				// rightDown
	friend void Conversion::upDown(const EventDispatcher &dispatcher, double time);					// upDown
	friend void Conversion::downDown(const EventDispatcher &dispatcher, double time);				// downDown
	friend void Conversion::enterDown(const EventDispatcher &dispatcher, double time);				// enterDown

	friend void Creation::enterDown(const EventDispatcher &dispatcher, double time);				// enterDown
	friend void Navigation::enterDown(const EventDispatcher &dispatcher, double time);				// enterDown
	friend void Selection::enterDown(const EventDispatcher &dispatcher, double time);				// enterDown
	friend void Configuration::enterDown(const EventDispatcher &dispatcher, double time);			// enterDown

	friend void Creation::upDown(const EventDispatcher &dispatcher, double time);					// leftDown
	friend void Navigation::rightDown(const EventDispatcher &dispatcher, double time);				// rightDown
	friend void Selection::downDown(const EventDispatcher &dispatcher, double time);				// upDown
	friend void Configuration::leftDown(const EventDispatcher &dispatcher, double time);			// downDown

	friend void Creation::upUp(const EventDispatcher &dispatcher, double time);						// leftUp
	friend void Navigation::rightUp(const EventDispatcher &dispatcher, double time);				// rightUp
	friend void Selection::downUp(const EventDispatcher &dispatcher, double time);					// upUp
	friend void Configuration::leftUp(const EventDispatcher &dispatcher, double time);				// downUp
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline State()																	// default constructor
		:mode(CONVERSION),locked(false),stroking(false)
	{
		// empty body.
	} // end State dafault constructor


	inline ~State()																	// destructor
	{
		// do nothing
	} // end ~State destructor

private:

	inline State(const State &original)												// copy constructor
		:mode(original.mode),locked(original.locked),stroking(original.stroking)
	{
		// empty body
	} // end State copy constructor


	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/


	/***************
	* data members *
	***************/

	Mode mode;
	bool locked;
	bool stroking;
}; // end class State

#endif // STATE_H
