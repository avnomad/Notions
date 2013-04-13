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
#include "utility.h"

namespace Creation
{
	void mouseleftDown(const EventDispatcher &dispatcher, double time)						// mouseleftDown
	{
		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		current.cursor = unproject(current.cursor);

		if(!state.stroking)
		{
			// create a new stroke
			Stroke<> *newStroke = new Stroke<>();
			newStroke->color = current.curveColor;
			newStroke->width = current.curveWidth/transform.zoom;
			newStroke->land_point = StrokePoint<>(current.cursor,time);
			newStroke->lift_point = StrokePoint<>(current.cursor,time);

			// register the new stroke
			shapes.strokes.push_back(newStroke);

			// update state to stroking
			state.stroking = true;

			// disable keyboard handlers
			disableKeyboardHandlers(dispatcher);
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
			// finalize the current stroke
			shapes.strokes.back()->lift_point = StrokePoint<>(current.cursor,time);

			// update state to not stroking
			state.stroking = false;

			// enable keyboard handlers
			Creation::enableKeyboardHandlers(dispatcher);
		} // end if
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
			shapes.strokes.back()->curve.push_back(StrokePoint<>(current.cursor,time));
			shapes.strokes.back()->lift_point = StrokePoint<>(current.cursor,time);
		} // end if
	} // end function mouseMove


}; // end namespace Creation
