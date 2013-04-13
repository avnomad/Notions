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

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <gl/glut.h>
#include <Space-Time/Vector2D.h>
#include "event handlers.h"

class Transform
{
	friend void Creation::mouseleftDown(const EventDispatcher &, double);					// mouseleftDown
	friend void Conversion::mouseleftDown(const EventDispatcher &, double);					// mouseleftDown
	friend void Conversion::mouseleftUp(const EventDispatcher &, double);					// mouseleftUp
	//friend void defaultPainter(const EventDispatcher &, double);							// defaultPainter
	//friend void navigationPainter(const EventDispatcher &, double);						// defaultPainter
	friend void Navigation::mouseleftDown(const EventDispatcher &, double);					// mouseleftDown
	friend void Navigation::mouseleftUp(const EventDispatcher &, double);					// mouseleftUp
	friend void Navigation::mouseMove(const EventDispatcher &, double);						// mouseMove
	friend void displayShapes();															// displayShapes
	friend void displayGUI();																// displayGUI
	friend void displayNavigationGUI();														// displayNavigationGUI
	friend inline void displayCursor();														// displayCursor
public:

	/***************************
	* contructors & destructor *
	***************************/

	inline Transform()																				// default constructor
		:displacement(0,0),rotation(0),zoom(1),zoomAngle(0)
	{
		// empty body
	} // end Transform default constructor


	inline ~Transform()																				// destructor
	{
		// do nothing
	} // end ~Transform destructor

private:

	inline Transform(const Transform &original)														// copy constructor
		:displacement(original.displacement),rotation(original.rotation),
		zoom(original.zoom),zoomAngle(original.zoomAngle)
	{
		// empty body
	} // end Transform copy constructor



	/************
	* operators *
	************/
	/*******************
	* member functions *
	*******************/

	inline void apply()																				// apply
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPushMatrix();
		glScaled(zoom,zoom,1);
		glRotated(rotation,0,0,1);
		glTranslated(displacement.x,displacement.y,0);
	} // end function apply



	/***************
	* data members *
	***************/

	Vector2D<> displacement;
	double rotation;	// in degrees!
	double zoom;
	double zoomAngle;	// in degrees!

}; // end class Transform

#endif // TRANSFORM_H
