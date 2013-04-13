//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
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

void resize(int width , int height)
{
	windowHeight = height;
	windowWidth = width;
	glViewport(0,0,windowWidth,windowHeight);
	glutPostRedisplay();
} // end function resize

void drag(int x ,int y)
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	freePoints.push_back(Triple(x,y,time.QuadPart*multiplier));	// time will be in microseconds
	glutPostRedisplay();
} // end function drag
