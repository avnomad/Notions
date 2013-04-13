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

// handler prototypes.
void paint(void);
void resize(int width , int height);
void drag(int x ,int y);
void keyPress(unsigned char key , int x , int y);
void keyPressSpecial(int key , int x , int y);

// main
int main(int argc , char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Free-Curve to Line convertion");
	
	// application initialization
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	multiplier = 1.0e6 / freq.QuadPart;

	// OpenGL initialization
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1,0,1);

	// glut main loop initialization
	glutDisplayFunc(paint);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(keyPressSpecial);
	glutMotionFunc(drag);
	glutMainLoop();
	return 0;
} // end main
