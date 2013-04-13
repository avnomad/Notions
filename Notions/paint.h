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

#ifndef PAINT_H
#define PAINT_H

// includes
#include "event handlers.h"

class Paint
{
	typedef void (*PainterType)(const EventDispatcher &,double);

	friend int WINAPI WinMain(InstanceHandle,InstanceHandle,CHAR *,int);
	friend void Navigation::rightDown(const EventDispatcher &, double);					// rightDown
	friend void Navigation::rightUp(const EventDispatcher &, double);					// rightUp
	friend void Navigation::enterDown(const EventDispatcher &, double);					// enterDown
	friend void Conversion::rightDown(const EventDispatcher &, double);					// rightDown
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Paint()															// default constructor
	{
		// do nothing
	} // end Paint default constructor


	inline ~Paint()															// destructor
	{
		// do nothing
	} // end ~Paint destructor

private:

	inline Paint(const Paint &original)										// copy constructor
		:iPaint(original.iPaint)
	{
		// empty body
	} // end Paint copy constructor


	/************
	* operators *
	************/

	inline Paint &operator = (PainterType painter)							// operator =
	{
		iPaint = painter;
		return *this;
	} // end function operator =


	inline Paint &operator = (const Paint &original)						// operator =
	{
		iPaint = original.iPaint;
		return *this;
	} // end function operator =


	inline operator PainterType () const									// cast operator
	{
		return iPaint;
	} // end function cast operator


	/*******************
	* member functions *
	*******************/

	/***************
	* data members *
	***************/

	PainterType iPaint;

}; // end class Paint

#endif // PAINT_H
