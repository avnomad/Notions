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
		{
		velocities.clear();
		velocity_magnitudes.clear();
		line_segments.clear();

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
			register_line_segment( (first-velocity_magnitudes.begin())+freePoints.begin() , (last-velocity_magnitudes.begin())+freePoints.begin() );
		} // end while

#if LOGGING
		copy(velocity_magnitudes.begin(),velocity_magnitudes.end(),outIter);
#endif
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
		break;
	}
	glutPostRedisplay();
} // end function keyPressSpecial