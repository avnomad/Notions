// includes
#include "global.h"

void paint(void)
{
	// set background to black.
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0,0.5,1);	// set current color to light blue.
	glPointSize(2);	// set point size to 2.
	glLineWidth(1);	// set line width to 1.

	display(freePoints.begin(),freePoints.end(),GL_POINTS);

	display_with_color(velocity_magnitudes.begin(),velocity_magnitudes.end(),freePoints.begin(),GL_POINTS);
	
	glColor3f(0,1,0);	// set current color to green.
	display(line_segments.begin(),line_segments.end(),GL_LINES);
	/*glColor3f(1,0,1);	// set current color to purple.
	display(line_segments.begin(),line_segments.end(),GL_POINTS);*/
	// display.		
	glutSwapBuffers();
} // end function paint
