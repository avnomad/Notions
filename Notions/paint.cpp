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
	freePointsMutex.lock();
	display(freePoints.begin(),freePoints.end(),GL_POINTS);
	freePointsMutex.unlock();

	unsigned char point_layer_status;
	point_layer_status_mutex.lock();
		point_layer_status = ::point_layer_status;
	point_layer_status_mutex.unlock();
	switch( point_layer_status )
	{
	case PLAIN_POINTS:
		glColor3f(0,0.5,1);	// light blue.
		strokesMutex.lock();
			for(size_t i = 0 ; i < strokes.size() ; ++i)
				display(strokes[i].points.begin(),strokes[i].points.end(),GL_POINTS);
		strokesMutex.unlock();
		break;
	case COLORED_POINTS_DISCRETE:
		strokesMutex.lock();
			for(size_t i = 0 ; i < strokes.size() ; ++i)
				display_with_color_discrete(strokes[i].velocity_magnitudes.begin(),strokes[i].velocity_magnitudes.end(),strokes[i].points.begin(),GL_POINTS,strokes[i].threshold);
		strokesMutex.unlock();
		break;
	case COLORED_POINTS_CONTINUOUS:
		strokesMutex.lock();
			for(size_t i = 0 ; i < strokes.size() ; ++i)
				display_with_color_continuous(strokes[i].velocity_magnitudes.begin(),strokes[i].velocity_magnitudes.end(),strokes[i].points.begin(),GL_POINTS,strokes[i].threshold,strokes[i].min,strokes[i].max);
		strokesMutex.unlock();
		break;
	} // end switch
	
	if(line_segment_layer_status)
	{
		line_segments_mutex.lock();
			glColor3f(0,1,0);	// set current color to green.
			display(line_segments.begin(),line_segments.end(),GL_LINES);
			glColor3f(1,0,1);	// set current color to purple.
			display(line_segments.begin(),line_segments.end(),GL_POINTS);
		line_segments_mutex.unlock();
	} // end if

	//glPointSize(4);	// set point size to 4.
	//for_each(line_stats.begin(),line_stats.end(),printLine);

	boost::lock(polyLinesMutex,selectedMutex);	// I assume this function doesn't lock the first and waits for the other...
	if(selected != -1)
	{
		Triple temp(polyLines[selected].color);

		polyLines[selected].width *= 4;
		polyLines[selected].color = Triple(0,0.5,1);	// light blue
		polyLines[selected].display();
		polyLines[selected].width /= 4;
		polyLines[selected].color = temp;
	} // end if
	polyLinesMutex.unlock();
	selectedMutex.unlock();

	if(line_strip_layer_status)
	{
		polyLinesMutex.lock();
			int c = polyLines.size();
			while(c--)
			{
				polyLines[c].display();
			} // end while
		polyLinesMutex.unlock();
	} // end if	
	
	// display.		
	glutSwapBuffers();
} // end function paint
