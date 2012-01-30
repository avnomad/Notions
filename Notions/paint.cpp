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
		//glVertex2d(0.00001,0);
		//glVertex2d(0.00001,1);
		//for(GLdouble c = -PI/2 + angle_step ; c <= PI/2 - angle_step ; c += angle_step)
		//{
		//	glVertex2d(0,0.5);
		//	glVertex2d(1,tan(c)*windowWidth/windowHeight + 0.5);
		//} // end for
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




	glPointSize(1);	// set point size to 2.
	glLineWidth(1);	// set line width to 1.

	glColor3f(1,0.75,0);	// gold
	display(freePoints.begin(),freePoints.end(),GL_POINTS);

	switch( point_layer_status )
	{
	case PLAIN_POINTS:
		glColor3f(0,0.5,1);	// set current color to light blue.
		display(freePointsAccumulated.begin(),freePointsAccumulated.end(),GL_POINTS);
		break;
	case COLORED_POINTS_DISCRETE:
		display_with_color_discrete(velocity_magnitudes_accumulated.begin(),velocity_magnitudes_accumulated.end(),freePointsAccumulated.begin(),GL_POINTS);
		break;
	case COLORED_POINTS_CONTINUOUS:
		display_with_color_continuous(velocity_magnitudes_accumulated.begin(),velocity_magnitudes_accumulated.end(),freePointsAccumulated.begin(),GL_POINTS);
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
