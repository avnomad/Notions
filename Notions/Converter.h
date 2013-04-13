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

#ifndef CONVERTER_H
#define CONVERTER_H

#include <sstream>
using std::ostringstream;
#include <string>
#include "event handlers.h"

class Converter
{
	// friend declarations
	friend void displayNavigationGUI();													// displayNavigationGUI
	friend void displayGUI();															// displayGUI
	//friend void defaultPainter(const EventDispatcher & , double);						// defaultPainter
	//friend void navigationPainter(const EventDispatcher &, double);					// navigationPainter
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Converter()															// default constructor
	{
		// do nothing
	} // end Converter default constructor


	inline ~Converter()															// destructor
	{
		// do nothing
	} // end ~Converter destructor

private:

	/***************
	* data members *
	***************/

	ostringstream stream;
	std::string string;
}; // end class Converter

#endif // CONVERTER_H
