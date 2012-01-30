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
