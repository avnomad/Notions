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
	
	if(grid_layer_status)
	{
		glLineWidth(0.5);
		glColor3f(0,0.1,0.1);
		glBegin(GL_LINES);
		for(GLdouble c = 0 ; c <= windowWidth ; c += intercept_step)
		{
			glVertex2d(c / windowWidth , 0);
			glVertex2d(c / windowWidth , 1);
		} // end for
		for(GLdouble c = 0 ; c <= windowHeight ; c += intercept_step)
		{
			glVertex2d(0 , (windowHeight-1-c) / windowHeight);
			glVertex2d(1 , (windowHeight-1-c) / windowHeight);
		} // end for
		glEnd();
	} // end if


	glPointSize(1);
	glLineWidth(1);

	// draw current stroke (if user not drawing will do nothing)
	glColor3f(1,0.75,0);	// gold
	display(freePoints.begin(),freePoints.end(),GL_POINTS);

	switch( point_layer_status )
	{
	case PLAIN_POINTS:
		glColor3f(0,0.5,1);	// light blue.
		for(size_t i = 0 ; i < strokes.size() ; ++i)
			display(strokes[i].points.begin(),strokes[i].points.end(),GL_POINTS);
		break;
	case COLORED_POINTS_DISCRETE:
		for(size_t i = 0 ; i < strokes.size() ; ++i)
			display_with_color_discrete(strokes[i].velocity_magnitudes.begin(),strokes[i].velocity_magnitudes.end(),strokes[i].points.begin(),GL_POINTS,strokes[i].threshold);
		break;
	case COLORED_POINTS_CONTINUOUS:
		for(size_t i = 0 ; i < strokes.size() ; ++i)
			display_with_color_continuous(strokes[i].velocity_magnitudes.begin(),strokes[i].velocity_magnitudes.end(),strokes[i].points.begin(),GL_POINTS,strokes[i].threshold,strokes[i].min,strokes[i].max);
		break;
	} // end switch
	
	if(line_segment_layer_status)
	{
		glColor3f(0,1,0);	// set current color to green.
		display(line_segments.begin(),line_segments.end(),GL_LINES);
		glColor3f(1,0,1);	// set current color to purple.
		display(line_segments.begin(),line_segments.end(),GL_POINTS);
	} // end if

	//glPointSize(4);	// set point size to 4.
	//for_each(line_stats.begin(),line_stats.end(),printLine);

	if(selected != -1)
	{
		Triple temp(polyLines[selected].color);

		polyLines[selected].width *= 4;
		polyLines[selected].color = Triple(0,0.5,1);	// light blue
		polyLines[selected].display();
		polyLines[selected].width /= 4;
		polyLines[selected].color = temp;
	} // end if

	if(line_strip_layer_status)
	{
		int c = polyLines.size();
		while(c--)
		{
			polyLines[c].display();
		} // end while
	} // end if	
	
	// display.		
	glutSwapBuffers();
} // end function paint
