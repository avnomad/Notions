//	Copyright (C) 2009, 2011, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
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

#include <utility>
using std::pair;
#include <vector>
using std::vector;
#include <utility.h>

//template<typename IIter , typename OIter1 , typename OIter2>
//pair<OIter1,OIter2> segments_and_corners(IIter iBegin , IIter iEnd , OIter1 sBegin , OIter2 cBegin)						// segments_and_corners
//{
//
//	return pair<OIter1,OIter2>(sBegin,cBegin);
//} // end function segments_and_corners


inline Vector2D<> velocity(const StrokePoint<> &terminal , const StrokePoint<> &initial)								// velocity
{
	return (terminal - initial) / (terminal.t - initial.t);
} // end function velocity


inline const Vector2D<> &point_with_min_velocity(const vector<Vector2D<> > &points , const vector<double> &magnitudes)	// point_with_min_velocity
{
	return *((std::min_element(magnitudes.begin(),magnitudes.end()) - magnitudes.begin()) + points.begin());
} // end function point_with_min_velocity


bool closed_parallel(const Vector2D<> &firstEnd , const Vector2D<> &afterFirstEnd , const Vector2D<> &secondEnd , const Vector2D<> &beforeSecondEnd , double distance2 , double ratio)	// closed_parallel
{
	if(inRange(secondEnd,afterFirstEnd,beforeSecondEnd,distance2) && inRange(firstEnd,afterFirstEnd,beforeSecondEnd,distance2))
	{
		if(inRange(firstEnd,secondEnd,beforeSecondEnd,distance2))
			return true;
		else
			return (firstEnd-secondEnd).norm() / (afterFirstEnd-beforeSecondEnd).norm() < ratio;	// parameter
	} // end if
	return false;
} // end function closed_parallel


bool closed_intersecting(const Vector2D<> &intersection , const Vector2D<> &firstEnd , const Vector2D<> &afterFirstEnd , const Vector2D<> &secondEnd , const Vector2D<> &beforeSecondEnd , double distance2 , double ratio)	// closed_intersecting
{
	double small_1 , small_2 , large_1 , large_2;

	if(inRange(intersection,firstEnd,afterFirstEnd,distance2))
	{
		large_1 = (afterFirstEnd-intersection).norm();
	}
	else if(inRange(firstEnd,intersection,afterFirstEnd,distance2))
	{
		large_1 = (afterFirstEnd-firstEnd).norm();
	}
	else
	{
		return false;
	} // end if-elseif-else

	if(inRange(intersection,secondEnd,beforeSecondEnd,distance2))
	{
		large_2 = (beforeSecondEnd-intersection).norm();
	}
	else if(inRange(secondEnd,intersection,beforeSecondEnd,distance2))
	{
		large_2 = (beforeSecondEnd-secondEnd).norm();
	}
	else
	{
		return false;
	} // end if-elseif-else

	small_1 = (firstEnd-intersection).norm();
	small_2 = (secondEnd-intersection).norm();

	return small_1/large_1 <= ratio || small_2/large_2 <= ratio;	// || or && ?
} // end function closed_intersecting


Socket *initialFindSocket(const Vector2D<> &point , double distance2)							// initialFindSocket
{
	Socket *socket;
	list<Region *>::iterator begin = shapes.regions.begin();
	list<Region *>::iterator end = shapes.regions.end();
	while(begin != end)
	{
		if(socket = (*begin)->initialNearSocket(point,distance2))
			return socket;
		++begin;
	} // end while
	return 0;
} // end function initialFindSocket
