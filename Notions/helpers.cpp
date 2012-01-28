// includes
#include "global.h"

Triple getSpeed(const Triple &final , const Triple &initial)	// check
{
	GLdouble temp = final.t - initial.t;

	return Triple( (final.x - initial.x) / temp , (final.y - initial.y) / temp , final.t );
} // end function getSpeed

GLdouble getMagnitude(const Triple &vector)	// check
{
	return sqrt(vector.x*vector.x + vector.y*vector.y);
} // end function getMagnitude

Statistics *add_to_sums(Statistics *statPtr , const Triple &point)	// check
{
	statPtr->x += point.x;
	statPtr->y += point.y;
	statPtr->xy += point.x*point.y;
	statPtr->x2 += point.x*point.x;
	return statPtr;
} // end function add_to_sums

Triple getIntersectionPoint(const Statistics &line1 , const Statistics &line2)	// check
{
	GLdouble D = line1.a*line2.b - line2.a*line1.b;
#ifdef _DEBUG
	if(D == 0)
	{
		cerr<<"The Determinant is 0!"<<endl;
		return Triple(line2.center_x,line2.center_y,0);
	} // end if
#endif
	return Triple(	(line2.b*line1.c - line1.b*line2.c)/D ,	(line1.a*line2.c - line2.a*line1.c)/D , D);
} // end function getIntersectionPoint

void snap_to_grid(Statistics &stats)	// check
{
	if( fabs(stats.a) >= tan(PI/2-angle_step/2) )
	{
		stats.a = 1;
		stats.b = 0;
		stats.c = intercept_step*floor(stats.center_x/intercept_step + 0.5);
	}
	else
	{
		stats.a = -tan( angle_step*floor(atan(stats.a)/angle_step + 0.5) );
		stats.b = 1;
		stats.c = stats.a*stats.center_x + stats.center_y;
		stats.c = intercept_step*floor(stats.c/intercept_step + 0.5);		
	} // end if-else
} // end function snap_to_grid

void printLine(Statistics &stats)	// check
{
	glColor3f(1,0,1);	// set color to purple
	glBegin(GL_LINES);
	if( stats.b != 0 )
	{
		glVertex2d(0,(windowHeight-1-stats.c)/windowHeight);
		glVertex2d(1,(windowHeight-1-stats.c+stats.a*windowWidth)/windowHeight);
	}
	else
	{
		glVertex2d(stats.c/windowWidth,0);
		glVertex2d(stats.c/windowWidth,1);
	} // end if-else
	glEnd();

	glColor3f(0.5,0.25,0);	// set color to brown
	glBegin(GL_POINTS);
	glVertex2d(stats.center_x/windowWidth , (windowHeight-1-stats.center_y)/windowHeight);
	glEnd();
} // end function printLine

Triple dummy_project(const Triple &point , const Statistics &line)	// TODO: replace with actual projection function
{
	if( fabs(line.a) >= 1 )
	{
		return Triple( (line.c-line.b*point.y)/line.a , point.y , 0);
	}
	else
	{
		return Triple(point.x , line.c-line.a*point.x , 0);
	} // end if-else
} // end function axis_project

bool point_in_segment(const Triple &p , const Triple &p1, const Triple &p2 , GLfloat width)
{
	width *= 1.5;
	if(p1.x == p2.x)
		if(p1.y < p2.y)
			return p1.y <= p.y && p.y <= p2.y && fabs(p.x-p1.x) < ceil(width);
		else
			return p2.y <= p.y && p.y <= p1.y && fabs(p.x-p1.x) < ceil(width);
	if(p1.y == p2.y)
		if(p1.x < p2.x)
			return p1.x <= p.x && p.x <= p2.x && fabs(p.y-p1.y) < ceil(width);
		else
			return p2.x <= p.x && p.x <= p1.x && fabs(p.y-p1.y) < ceil(width);

	GLdouble t1 = (p.x-p1.x)/(p2.x-p1.x);
	//GLdouble t2 = (p.y-p1.y)/(p2.y-p1.y);
	return 0 <= t1 && t1 <= 1 && fabs(p.y-p1.y-t1*(p2.y-p1.y)) < ceil(width);
} // end function point_in_segment

bool lessTriple(const Triple &left , const Triple &right)
{
	return left.x < right.x;
} // end function lessTriple

bool check_intersecting(const Triple &intersection , const Triple &seg_1_out , const Triple &seg_1_in , const Triple &seg_2_in , const Triple &seg_2_out)
{
	GLdouble small_1 , small_2 , large_1 , large_2;

	if(point_in_segment(intersection,seg_1_out,seg_1_in,1.5))
	{
		large_1 = getMagnitude(seg_1_in-intersection);
	}
	else if(point_in_segment(seg_1_out,intersection,seg_1_in,1.5))
	{
		large_1 = getMagnitude(seg_1_in-seg_1_out);
	}
	else
	{
		return false;
	} // end if-elseif-else

	if(point_in_segment(intersection,seg_2_out,seg_2_in,1.5))
	{
		large_2 = getMagnitude(seg_2_in-intersection);
	}
	else if(point_in_segment(seg_2_out,intersection,seg_2_in,1.5))
	{
		large_2 = getMagnitude(seg_2_in-seg_2_out);
	}
	else
	{
		return false;
	} // end if-elseif-else

	small_1 = getMagnitude(seg_1_out-intersection);
	small_2 = getMagnitude(seg_2_out-intersection);

	return small_1/large_1 <= 0.2 || small_2/large_2 <= 0.2;	// || or && ?
} // end function check_intersecting

bool check_parallel(const Triple &seg_1_out , const Triple &seg_1_in , const Triple &seg_2_in , const Triple &seg_2_out)
{
	if(point_in_segment(seg_1_out,seg_1_in,seg_2_in,1.5) && point_in_segment(seg_2_out,seg_1_in,seg_2_in,1.5))
	{
		if(point_in_segment(seg_1_out,seg_2_in,seg_2_out,1.5))
			return true;
		else
			return getMagnitude(seg_1_out-seg_2_out)/getMagnitude(seg_1_in-seg_2_in) < 0.1;
	} // end if
	return false;
} // end function check_parallel
