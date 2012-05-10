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

#ifndef DISPLAY_LISTS_H
#define DISPLAY_LISTS_H

// includes
#include <graphics/RotationIndicator.h>
#include <graphics/SquareGrid.h>

#include <direct input/mouse and keyboard/EventDispatcher.h>
using namespace MouseAndKeyboard;

class DisplayLists
{
	friend void Navigation::mouseleftDown(const EventDispatcher &, double);			// mouseleftDown
	//friend void defaultPainter(const EventDispatcher & , double);					// defaultPainter
	//friend void navigationPainter(const EventDispatcher &, double);				// navigationPainter
	friend void displayGrid();														// displayGrid
	friend void displayNavigationGUI();												// displayNavigationGUI
	friend int WINAPI WinMain(InstanceHandle,InstanceHandle,CHAR *,int);			// WinMain
public:

	/***************************
	* contructors & destructor *
	***************************/

	DisplayLists()																	// default constructor
	{
		// do nothing
	} // end DisplayLists default constructor


	inline ~DisplayLists()															// destructor
	{
		// do nothing
	} // end ~DisplayLists destructor


private:

	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/



	/***************
	* data members *
	***************/

	SquareGrid<> grid;
	RotationIndicator rotationIndicator;

}; // end class DisplayLists

#endif // DISPLAY_LISTS_H
