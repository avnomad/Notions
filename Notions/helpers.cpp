// includes
#include "global.h"

Triple getSpeed(const Triple &final , const Triple &initial)
{
	GLdouble temp = final.t - initial.t;

	return Triple((final.x - initial.x) / temp , (final.y - initial.y) / temp , final.t);
} // end function getSpeed

GLdouble getMagnitude(const Triple &vector)
{
	return sqrt(vector.x*vector.x + vector.y*vector.y);
} // end function getMagnitude

Statistics *add_to_sums(Statistics *statPtr , const Triple &point)
{
	statPtr->x += point.x;
	statPtr->y += point.y;
	statPtr->xy += point.x*point.y;
	statPtr->x2 += point.x*point.x;
	return statPtr;
} // end function add_to_sums