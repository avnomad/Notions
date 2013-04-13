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

#include "event handlers.h"
#include "global variables.h"
#include <iterator>
#include <algorithm>
#include <numeric>
#include "utility.h"
#include <Space-Time/Line2D.h>
#include "conversion functions.h"

namespace Conversion
{
	void mouseleftDown(const EventDispatcher &dispatcher, double time)						// mouseleftDown
	{
		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		current.cursor = unproject(current.cursor);

		if(!state.stroking)
		{
			// initialize the current stroke
			shapes.currentStroke.color = current.lineColor;
			shapes.currentStroke.width = current.lineWidth/transform.zoom;
			shapes.currentStroke.land_point = StrokePoint<>(current.cursor,time);
			shapes.currentStroke.lift_point = StrokePoint<>(current.cursor,time);	// to avoid display of uninitialized values

			state.stroking = true;	// update state to stroking
			disableKeyboardHandlers(dispatcher);	// disable keyboard handlers
		} // end if
	} // end function mouseleftDown


	void mouseleftUp(const EventDispatcher &dispatcher, double time)						// mouseleftUp
	{
		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		current.cursor = unproject(current.cursor);

		if(state.stroking)
		{
			shapes.currentStroke.lift_point = StrokePoint<>(current.cursor,time);	// finalize the current stroke

			// conversion
			// constant declarations
			static const double threshold_percentage = 0.15;
			static const unsigned int point_threshold = 3;	// should be >= 1
			static const double angle_step = PI/12;
			static const double grid_resolution = 10;
			static const double parallel_ratio = 0.1;
			static const double intersecting_ratio = 0.2;
			static const double connect_distance2 = 225;	// the square of 15

			// a sorthand for the size
			unsigned int n = shapes.currentStroke.curve.size();

			if(n < 2)	// precaution
			{
				shapes.currentStroke.curve.clear();	// clear currentStroke to prepare for the next one.
				state.stroking = false;	// update state to not stroking.
				Conversion::enableKeyboardHandlers(dispatcher);	// enable keyboard handlers.
				return;
			} // end if

			// variable declarations
			vector<Vector2D<> > velocities(n);
			vector<double> magnitudes(n);
			vector<double> sorted_magnitudes(n);
			list<vector<Vector2D<> > > segments(n/2+n%2);			// strength reduction and
			vector<vector<Vector2D<> > > corners(n/2+n%2);			// common subexpression
			vector<vector<double> > segment_magnitudes(n/2+n%2);	// elimination left to
			vector<vector<double> > corner_magnitudes(n/2+n%2);		// compiler
			list<Vector2D<> > corner_points;
			vector<Line2D<> > lines;
			vector<Vector2D<> > centers;
			list<Vector2D<> > polyline;

			// threshold calculation
			adjacent_difference(shapes.currentStroke.curve.begin(),shapes.currentStroke.curve.end(),velocities.begin(),velocity);	// velocities
			velocities.front() = Vector2D<>(0,0);	// give a meaningful value to the first element
			mapm(velocities.begin(),velocities.end(),magnitudes.begin(),&Vector2D<>::norm);	// velocity magnitudes
			std::copy(magnitudes.begin(),magnitudes.end(),sorted_magnitudes.begin());	// copy velocity magnitudes
			std::sort(sorted_magnitudes.begin(),sorted_magnitudes.end());	// sorted velocity magnitudes

			Threshold<double> threshold(sorted_magnitudes[floor(threshold_percentage*n)]);	// threshold
			sorted_magnitudes.clear();	// some clean up
			velocities.clear();	// more clean up

			// split to line segments and corners using threshold
			std::pair<list<vector<Vector2D<> > >::iterator,vector<vector<Vector2D<> > >::iterator> ends =
				split_and_segment(magnitudes.begin(),magnitudes.end(),shapes.currentStroke.curve.begin(),segments.begin(),corners.begin(),threshold);
			segments.erase(ends.first,segments.end());	// truncate segments
			corners.erase(ends.second,corners.end());	// truncate corners
			std::pair<vector<vector<double> >::iterator,vector<vector<double> >::iterator> magnitude_ends =
				split_and_segment(magnitudes.begin(),magnitudes.end(),segment_magnitudes.begin(),corner_magnitudes.begin(),threshold);
			segment_magnitudes.erase(magnitude_ends.first,segment_magnitudes.end());	// truncate segment magnitudes
			corner_magnitudes.erase(magnitude_ends.second,corner_magnitudes.end());		// truncate corner magnitudes
			magnitudes.clear(); // magnitudes are no longer needed.
			segment_magnitudes.clear();	// segment magnitudes are no longer needed.

			// corner points calculation
			corner_points.resize(corners.size());	// preallocate space for the corner points
			std::transform(corners.begin(),corners.end(),corner_magnitudes.begin(),corner_points.begin(),point_with_min_velocity);	// corner points
			corners.clear();	// corners are no longer needed.
			corner_magnitudes.clear();	// corner magnitudes are no longer needed.

			// lines calculation
			list<vector<Vector2D<> > >::iterator segment = segments.begin();	// segments
			list<Vector2D<> >::iterator corner = corner_points.begin();	// corner points
			n = segments.size();
			lines.resize(n);	// preallocate space for the lines
			centers.resize(n);	// preallocate space for the centers
			vector<Line2D<> >::iterator line = lines.begin();	// lines
			vector<Vector2D<> >::iterator center = centers.begin();	// centers

			while(segment != segments.end())	// for each segment
			{
				if(segment->size() > point_threshold)	// ignore segments with not enough points.
				{
					*center = line->setTo(segment->begin(),segment->end());
					++corner , ++line , ++center , ++segment;
				}
				else
				{
					corner = corner_points.erase(corner);	// we should preserve the correspondance
					segment = segments.erase(segment);	//  between lines, corners and segments
				} // end else
			} // end while
			lines.erase(line,lines.end());	// truncate lines
			centers.erase(center,centers.end());	// truncate centers

			// snap lines to grid
			n = lines.size();
			for(unsigned int c = 0 ; c < n ; ++c)	// for each line
			{
				lines[c].roundAngle(angle_step,(Pi/180)*transform.rotation,centers[c]);
				lines[c].roundC(grid_resolution/transform.zoom,transform.displacement);
			} // end for
			centers.clear();	// centers are no longer needed.

			if(n == 0)	// precaution
			{
				shapes.currentStroke.curve.clear();	// clear currentStroke to prepare for the next one.
				state.stroking = false;	// update state to not stroking.
				Conversion::enableKeyboardHandlers(dispatcher);	// enable keyboard handlers.
				return;
			} // end if
			
			
			// polyline calculation
			polyline.resize(n-1);	// preallocate space for the polyline
			corner_points.erase(corner_points.begin());	// the first corner is not needed
			list<Vector2D<> >::iterator polyPoint = polyline.begin();	// polyline
			line = lines.begin();	// lines
			vector<Line2D<> >::iterator oldLine = lines.begin();
			corner = corner_points.begin();	// corner points
			segment = segments.begin();	// segments
			list<vector<Vector2D<> > >::iterator oldSegment = segments.begin();
			++line , ++segment;
			while(line != lines.end())
			{
				if(!parallel(*oldLine,*line))	// use intersection
				{
					*polyPoint = intersection(*oldLine,*line);
					++polyPoint , ++oldLine , ++line , ++corner , ++oldSegment , ++segment;
				}
				else if((projection(oldSegment->back(),*oldLine) - projection(oldSegment->front(),*oldLine)) *
					(projection(segment->back(),*line) - projection(segment->front(),*line)) < 0)	// use corner
				{
					*polyPoint = projection(*corner,*oldLine) , ++polyPoint;
					line = lines.erase(line);
					segment = segments.erase(segment);
					corner = corner_points.erase(corner);
					std::swap(oldSegment->back(),oldSegment->front());	// a bit of a trick but works.
				}
				else
				{
					line = lines.erase(line);
					segment = segments.erase(segment);
					corner = corner_points.erase(corner);
				} // end else
			} // end while
			polyline.erase(polyPoint,polyline.end());	// truncate polyline.
			corner_points.clear();	// corner points are no longer needed.
			segments.clear();	// segments are no longer needed.

			
			// closed or not determination
			bool closed = false;
			if((n = lines.size()) > 1)
			{
				if(parallel(lines.front(),lines.back()))	// parallel
				{
					if(closed_parallel(projection(shapes.currentStroke.land_point,lines.front()) , polyline.front() ,
						projection(shapes.currentStroke.lift_point,lines.back()) , polyline.back() , 8 , parallel_ratio))
					{
						closed = true;
					} // end if
				}
				else	// intersecting
				{
					Vector2D<> intersectionPoint = intersection(lines.front(),lines.back());
					if(closed_intersecting(intersectionPoint,projection(shapes.currentStroke.land_point,lines.front()) , polyline.front() ,
						projection(shapes.currentStroke.lift_point,lines.back()) , polyline.back() , 8 , intersecting_ratio))
					{
						closed = true;
						polyline.push_back(intersectionPoint);
					}
				} // end else
			} // end if


			if(closed)
			{
				if(fillable(polyline.begin(),polyline.end()))	// fillable
				{
					// ConvexPolygon
					ConvexPolygon *polygon = new ConvexPolygon(shapes.currentStroke.width,shapes.currentStroke.color);	// creation
					polygon->setFillColor(current.fillColor);	// fill color
					for(polyPoint = polyline.begin() ; polyPoint != polyline.end() ; ++polyPoint)	// vertex sockets
						polygon->vertices.push_back( &(new Socket(*polyPoint,shapes.currentStroke.width,red))->setParent(polygon) );

					list<Vertex *>::iterator vBegin = polygon->vertices.begin();	// edge sockets
					list<Vertex *>::iterator vOld = polygon->vertices.begin();
					list<Vertex *>::iterator vEnd = polygon->vertices.end();
					++vBegin;
					while(vBegin != vEnd)
					{
						polygon->sockets.push_back(&(new EdgeSocket(0,0,shapes.currentStroke.width,red))->setLeft(*vOld).setRight(*vBegin).setParent(polygon));
						++vBegin , ++vOld;
					} // end while
					polygon->sockets.push_back(&(new EdgeSocket(0,0,shapes.currentStroke.width,red))->setLeft(*vOld).setRight(polygon->vertices.front()).setParent(polygon));	// last edge socket

					polygon->center = &(new CenterSocket(0,0,shapes.currentStroke.width,red))->setParent(polygon);	// center socket

					// integrate strokes
					list<Stroke<> *>::iterator begin = shapes.strokes.begin();
					while(begin != shapes.strokes.end())
					{
						if(polygon->inside((*begin)->land_point) && polygon->inside((*begin)->lift_point))
						{
							vector<StrokePoint<> >::iterator cBegin = (*begin)->curve.begin();
							vector<StrokePoint<> >::iterator cEnd = (*begin)->curve.end();
							while(cBegin != cEnd && polygon->inside(*cBegin))
								++cBegin;
							if(cBegin == cEnd)
							{
								polygon->strokes.push_back(*begin);
								begin = shapes.strokes.erase(begin);
							} // end if
							else
								++begin;
						}
						else
							++begin;
					} // end while

					shapes.regions.push_back(polygon);	// register polygon
				}
				else	// not fillable
				{
					// LineLoop
					LineLoop *lineLoop = new LineLoop(shapes.currentStroke.width,shapes.currentStroke.color);	// creation
					lineLoop->setFillColor(current.fillColor);	// fill color
					for(polyPoint = polyline.begin() ; polyPoint != polyline.end() ; ++polyPoint)	// vertex sockets
						lineLoop->vertices.push_back( &(new Socket(*polyPoint,shapes.currentStroke.width,red))->setParent(lineLoop) );

					list<Vertex *>::iterator vBegin = lineLoop->vertices.begin();	// edge sockets
					list<Vertex *>::iterator vOld = lineLoop->vertices.begin();
					list<Vertex *>::iterator vEnd = lineLoop->vertices.end();
					++vBegin;
					while(vBegin != vEnd)
					{
						lineLoop->sockets.push_back(&(new EdgeSocket(0,0,shapes.currentStroke.width,red))->setLeft(*vOld).setRight(*vBegin).setParent(lineLoop));
						++vBegin , ++vOld;
					} // end while
					lineLoop->sockets.push_back(&(new EdgeSocket(0,0,shapes.currentStroke.width,red))->setLeft(*vOld).setRight(lineLoop->vertices.front()).setParent(lineLoop));	// last edge socket

					lineLoop->center = &(new CenterSocket(0,0,shapes.currentStroke.width,red))->setParent(lineLoop);	// center socket

					shapes.regions.push_back(lineLoop);	// register lineLoop
				} // end else (fillable)
			}
			else	// not closed
			{
				// LineStrip
				Plug *plug;
				Socket *socket;

				LineStrip *lineStrip = new LineStrip(shapes.currentStroke.width,shapes.currentStroke.color);	// create LineStrip
					// first plug
				lineStrip->vertices.push_back(plug = new Plug(projection(shapes.currentStroke.land_point,lines.front()),shapes.currentStroke.width,red));
				if(socket = initialFindSocket(shapes.currentStroke.land_point,connect_distance2/(transform.zoom*transform.zoom)))	// connect if possible
					plug->connect(socket).rest();
					// vertices
				for(polyPoint = polyline.begin() ; polyPoint != polyline.end() ; ++polyPoint)
					lineStrip->vertices.push_back(new Vertex(*polyPoint,shapes.currentStroke.width,red));
					// second plug
				lineStrip->vertices.push_back(plug = new Plug(projection(shapes.currentStroke.lift_point,lines.back()),shapes.currentStroke.width,red));
				if(socket = initialFindSocket(shapes.currentStroke.lift_point,connect_distance2/(transform.zoom*transform.zoom)))	// connect if possible
					plug->connect(socket).rest();

				shapes.shapes.push_back(lineStrip);	// register the new line strip.
			} // end else (closed)


			shapes.currentStroke.curve.clear();	// clear currentStroke to prepare for the next one.
			state.stroking = false;	// update state to not stroking.
			Conversion::enableKeyboardHandlers(dispatcher);	// enable keyboard handlers.
		} // end if (stroking)
	} // end function mouseleftUp


	void mouseMove(const EventDispatcher &dispatcher, double time)							// mouseMove
	{
		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		current.cursor = unproject(current.cursor);

		if(state.stroking)
		{
			// add point to the current stroke
			shapes.currentStroke.curve.push_back(StrokePoint<>(current.cursor,time));
			shapes.currentStroke.lift_point = StrokePoint<>(current.cursor,time);	// to avoid display of extra line segment
		} // end if
	} // end function mouseMove

}; // end namespace Conversion
