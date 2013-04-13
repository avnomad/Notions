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

// templates
template<typename IterType>
void display(IterType begin , IterType end , GLenum mode)
{
	glBegin(mode);
	while(begin != end)
	{
		glVertex2d(begin->x / windowWidth , (windowHeight-1-begin->y) / windowHeight);
		++begin;
	} // end while
	glEnd();
} // end function template display

template<typename IterType1, typename IterType2>
void display_with_color_continuous(IterType1 first , IterType1 last , IterType2 point , GLenum mode , GLdouble threshold , GLdouble min , GLdouble max)
{
	glBegin(mode);
	while(first != last)
	{
		if(*first > threshold)
		{
			glColor3d((*first-threshold)/(max-threshold),0,0);
		}
		else
		{
			glColor3d(0,0,(threshold-*first)/(threshold-min));
		} // end if-else
		glVertex2d(point->x / windowWidth , (windowHeight-1-point->y) / windowHeight);
		++point;
		++first;
	} // end while
	glEnd();
} // end function template display_with_color_continuous

template<typename IterType1, typename IterType2>
void display_with_color_discrete(IterType1 first , IterType1 last , IterType2 point , GLenum mode , GLdouble threshold)
{
	glBegin(mode);
	while(first != last)
	{
		if(*first > threshold)
		{
			glColor3d(1,0,0);
		}
		else
		{
			glColor3d(0,0,1);
		} // end if-else
		glVertex2d(point->x / windowWidth , (windowHeight-1-point->y) / windowHeight);
		++point;
		++first;
	} // end while
	glEnd();
} // end function template display_with_color_discrete

template<typename IterType1, typename IterType2>
void register_line_segment(IterType1 begin , IterType1 end , IterType2 line_stats_iter)
{
	if( end-begin <= 1 ) return;	// what kind of line will I get with a sole point?
	Statistics stats;

	accumulate(begin,end,&stats,add_to_sums);	// calculate sums.
	stats.n = end-begin;	// calculate number of points.
	if(max_element(begin,end,lessTriple)->x == min_element(begin,end,lessTriple)->x)
	{
		stats.a = tan(PI/2 - angle_step/4);	// should be snapped to vertical.
		stats.b = begin->x;	// dummy value.

		line_segments.push_back(*begin);
		line_segments.push_back(*(end-1));

		stats.center_x = begin->x;
		stats.center_y = (begin->y + (end-1)->y)/2;
	}
	else
	{
		GLdouble temp = stats.n*stats.x2 - stats.x*stats.x;	// calculate the common divisor.
		stats.a = (stats.n*stats.xy - stats.x*stats.y) / temp;	// calculate a
		stats.b = (stats.y*stats.x2-stats.x*stats.xy) / temp;	// and b.

		GLdouble x1,x2,y1,y2;
		if( fabs(stats.a) <= 1 )
		{
			line_segments.push_back( Triple(x1 = begin->x , y1 = stats.a*begin->x + stats.b , begin->t) );
			line_segments.push_back( Triple(x2 = (end-1)->x , y2 = stats.a*(end-1)->x + stats.b , (end-1)->t) );
		}
		else
		{
			line_segments.push_back( Triple(x1 = (begin->y-stats.b)/stats.a , y1 = begin->y , begin->t) );
			line_segments.push_back( Triple(x2 = ((end-1)->y-stats.b)/stats.a , y2 = (end-1)->y , (end-1)->t) );
		} // end if-else

		stats.center_x = (x1+x2)/2;
		stats.center_y = (y1+y2)/2;
	}
	*line_stats_iter = stats;	// register the stats for future use.
	++line_stats_iter;
} // end function template register_line_segment
