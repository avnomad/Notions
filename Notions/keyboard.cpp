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

void keyPress(unsigned char key , int x , int y)
{
	switch(key)
	{
	case '\r':
		break;
	case '\b':
		grid_layer_status = !grid_layer_status;
		glutPostRedisplay();
		break;
	case '\33':
		exit(0);
		break;
	}
	glutPostRedisplay();
} // end function keypress

void keyPressSpecial(int key , int x , int y)
{
	switch(key)
	{
	case GLUT_KEY_RIGHT:
		selected = -1;
		line_segments.clear();
		polyLines.clear();
		strokes.clear();
		break;
	case GLUT_KEY_DOWN:
		++point_layer_status %= 4;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		line_segment_layer_status = !line_segment_layer_status;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		line_strip_layer_status = !line_strip_layer_status;
		glutPostRedisplay();
		break;
	}
	glutPostRedisplay();
} // end function keyPressSpecial