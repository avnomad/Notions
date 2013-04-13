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

#ifndef REGION_H
#define REGION_H

// includes
#include "Shape.h"
#include <string>
using std::string;
#include <list>
using std::list;
#include <Digitizing/Stroke.h>
#include <algorithms.h>

struct Socket;

struct Region : public Shape
{
	/***************************
	* contructors & destructor *
	***************************/

	inline Region()																							// Region default constructor
	{
		// do nothing
	} // end Region default constructor


	inline Region(const Region &original)																	// Region copy constructor
		:Shape(original),fillColor(original.fillColor),textColor(original.textColor),
		textWidth(original.textWidth),text(original.text)
	{
		setStrokes(original.strokes);
	} // end Region copy constructor


	inline Region(double width, const Color<> &color, bool mark = false)									// Region constructor
		:Shape(width,color,mark)
	{
		// empty body
	} // end Region constructor


	virtual ~Region()																						// Region destructor
	{
		deleteStrokes();
	} // end Region destructor




	/************
	* operators *
	************/

	virtual Region &operator = (const Region &original)														// operator =
	{
		Shape::operator =(original);
		fillColor = original.fillColor;
		textColor = original.textColor;
		text = original.text;
		textWidth = original.textWidth;
		setStrokes(original.strokes);
		return *this;
	} // end function operator =


	/*******************
	* member functions *
	*******************/

	inline Region &deleteStrokes()																			// deleteStrokes
	{
		list<Stroke<> *>::iterator begin = strokes.begin();
		list<Stroke<> *>::iterator end = strokes.end();
		while(begin != end)
			delete *begin;
		strokes.clear();
		return *this;
	} // end function deleteStrokes


	inline Region &setFillColor(const Color<> &color)														// setFillColor
	{
		fillColor = color;
		return *this;
	} // end function setFillColor


	inline Region &setTextColor(const Color<> &color)														// setTextColor
	{
		textColor = color;
		return *this;
	} // end function setTextColor


	inline Region &setText(const string &regionText)														// setText
	{
		text = regionText;
		return *this;
	} // end function setText


	inline Region &setTextWidth(double width)																// setTextWidth
	{
		textWidth = width;
		return *this;
	} // end function setTextWidth


	inline Region &setStrokes(const list<Stroke<> *> &regionStrokes)										// setStrokes
	{
		deleteStrokes();	// delete old strokes
		// and make new ones.
		list<Stroke<> *>::const_iterator begin = regionStrokes.begin();
		list<Stroke<> *>::const_iterator end = regionStrokes.end();
		while(begin != end)
			strokes.push_back(new Stroke<>(**begin));
		return *this;
	} // end function setStrokes


	virtual Region &display()																				// display
	{
		execute_indirect(strokes.begin(),strokes.end(),&Stroke<>::display);
		return *this;
	} // end function display


	virtual Region &display(double zoom)																	// display
	{
		execute_indirect(strokes.begin(),strokes.end(),&Stroke<>::display,zoom);
		return *this;
	} // end function display


	virtual Region &move(const Vector2D<> &displacement)													// move
	{
		execute_indirect(strokes.begin(),strokes.end(),&Stroke<>::move,displacement);
		return *this;
	} // end function move


	virtual Region *inside(const Vector2D<> &point)															// inside
	{
		return 0;
	} // end function inside


	virtual Socket *nearSocket(const Vector2D<> &point , double distance2) = 0;								// nearSocket
	virtual Socket *initialNearSocket(const Vector2D<> &point , double distance2) = 0;						// initialNearSocket


	virtual Region &evaluateCenter()																		// evaluateCenter
	{
		return *this;
	} // end function evaluateCenter



	/***************
	* data members *
	***************/

	Color<> fillColor;
	Color<> textColor;
	string text;
	list<Stroke<> *> strokes;
	double textWidth;

}; // end class Region

#endif // REGION_H