//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
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

// includes
#include "global.h"

void paint(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0,0.5,1);	// light blue.
	glPointSize(2);
	glLineWidth(1);

	display(freePoints.begin(),freePoints.end(),GL_POINTS);

	display_with_color(velocity_magnitudes.begin(),velocity_magnitudes.end(),freePoints.begin(),GL_POINTS);
	
	glColor3f(0,1,0);	// lime.
	display(line_segments.begin(),line_segments.end(),GL_LINES);
	/*glColor3f(1,0,1);	// set current color to purple.
	display(line_segments.begin(),line_segments.end(),GL_POINTS);*/

	// display.		
	glutSwapBuffers();
} // end function paint
