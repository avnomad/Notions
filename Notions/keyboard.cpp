// includes
#include "global.h"

void keyPress(unsigned char key , int x , int y)
{
	switch(key)
	{
	case '\r':
		{
		velocities.clear();
		velocity_magnitudes.clear();
		line_segments.clear();
		//line_strip.clear();

		adjacent_difference(freePoints.begin(),freePoints.end(),back_inserter(velocities),getSpeed);
		velocities.erase(velocities.begin());
		transform(velocities.begin(),velocities.end(),back_inserter(velocity_magnitudes),getMagnitude);
		
		max = *max_element(velocity_magnitudes.begin(),velocity_magnitudes.end());
		min = *min_element(velocity_magnitudes.begin(),velocity_magnitudes.end());
		threshold = (max - min)*relative_threshold + min;

		vector<GLdouble>::iterator last = velocity_magnitudes.begin();
		vector<GLdouble>::iterator first;
		vector<GLdouble>::iterator temp;
		Comparer<GLdouble,greater<GLdouble> > over(threshold);
		Comparer<GLdouble,less_equal<GLdouble> > below(threshold);
		while(last != velocity_magnitudes.end())
		{
			first = find_if(last,velocity_magnitudes.end(),over);
			last = find_if(first,velocity_magnitudes.end(),below);
			/*while( (temp = find_if(last,velocity_magnitudes.end(),over)) - last == 1 )
				last = find_if(temp,velocity_magnitudes.end(),below);*/
			register_line_segment( (first-velocity_magnitudes.begin())+freePoints.begin() , (last-velocity_magnitudes.begin())+freePoints.begin() );
		} // end while

		//copy(velocity_magnitudes.begin(),velocity_magnitudes.end(),outIter);
		break;
		}
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
	case GLUT_KEY_DOWN:
		freePoints.clear();
		velocities.clear();
		velocity_magnitudes.clear();
		line_segments.clear();
		//line_strip.clear();
		break;
	}
	glutPostRedisplay();
} // end function keyPressSpecial