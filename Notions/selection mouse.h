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

static double unit = 16;

namespace Selection
{
	bool locked = false;
	static double oldTime = 0;
	Shape *wholeShape = 0;
	std::pair<Shape *,Shape *> part(nullptr,nullptr);

	void mouseleftDown(const EventDispatcher &dispatcher, double time)						// mouseleftDown
	{
		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		current.cursor = unproject(current.cursor);

		if(!locked)
		{
			// iterator declarations
			list<Shape *>::iterator sBegin = shapes.shapes.begin();
			list<Shape *>::iterator sEnd = shapes.shapes.end();
			list<Region *>::iterator rBegin;
			list<Region *>::iterator rEnd;

			//// check for reselection
			//if(wholeShape)
			//	if(wholeShape->nearVertex(current.cursor,9) ||
			//		wholeShape->nearEdge(current.cursor,9).first ||
			//		dynamic_cast<Region *>(wholeShape) && 
			//		static_cast<Region *>(wholeShape)->inside(current.cursor,9))
			//	{	// selected the same shape
			//		part.first = wholeShape;
			//		part.second = 0;
			//		goto found;
			//	} // end if

			// search for vertex in shapes
			sBegin = shapes.shapes.begin();
			sEnd = shapes.shapes.end();
			while(sBegin != sEnd)
			{
				if(part.first = (*sBegin)->nearVertex(current.cursor,unit))
				{
					part.second = 0;
					if(wholeShape)
					{
						wholeShape->rest();
						wholeShape->marked = false;
					} // end if
					wholeShape = *sBegin;
					goto found;
				} // end if
				++sBegin;
			} // end while

			// search for vertex in regions
			rBegin = shapes.regions.begin();
			rEnd = shapes.regions.end();
			while(rBegin != rEnd)
			{
				if(part.first = (*rBegin)->nearVertex(current.cursor,unit))
				{
					part.second = 0;
					if(wholeShape)
					{
						wholeShape->rest();
						wholeShape->marked = false;
					} // end if
					wholeShape = *rBegin;
					goto found;
				} // end if
				++rBegin;
			} // end while

			// search for edge in shapes
			sBegin = shapes.shapes.begin();
			sEnd = shapes.shapes.end();
			while(sBegin != sEnd)
			{
				part = (*sBegin)->nearEdge(current.cursor,unit);
				if(part.first)
				{
					if(wholeShape)
					{
						wholeShape->rest();
						wholeShape->marked = false;
					} // end if
					wholeShape = *sBegin;
					goto found;
				} // end if
				++sBegin;
			} // end while

			// search for edge in regions
			rBegin = shapes.regions.begin();
			rEnd = shapes.regions.end();
			while(rBegin != rEnd)
			{
				part = (*rBegin)->nearEdge(current.cursor,unit);
				if(part.first)
				{
					if(wholeShape)
					{
						wholeShape->rest();
						wholeShape->marked = false;
					} // end if
					wholeShape = *rBegin;
					goto found;
				} // end if
				++rBegin;
			} // end while

			// search for region in regions
			rBegin = shapes.regions.begin();
			rEnd = shapes.regions.end();
			while(rBegin != rEnd)
			{
				if(part.first = (*rBegin)->inside(current.cursor))
				{
					part.second = 0;
					if(wholeShape)
					{
						wholeShape->rest();
						wholeShape->marked = false;
					} // end if
					wholeShape = *rBegin;
					goto found;
				} // end if
				++rBegin;
			} // end while

			// not found
			if(wholeShape)
			{
				wholeShape->rest();
				wholeShape->marked = false;
			}
			wholeShape = 0;
			part.first = 0;
			part.second = 0;

			locked = true;	// update state to locked
			disableKeyboardHandlers(dispatcher);	// disable keyboard handlers
			return;
found:
			if( 0 < time-oldTime && time-oldTime < 400)
			{
				part.first = wholeShape;
				part.second = 0;
			} // end if

			// note time
			oldTime = time;

			wholeShape->marked = true;	
			wholeShape->work();

			locked = true;	// update state to locked
			disableKeyboardHandlers(dispatcher);	// disable keyboard handlers
			dispatcher.key[DIK_UP].down = Selection::upDown;
			dispatcher.key[DIK_UP].up = Selection::upUp;
			return;
		} // end if
	} // end function mouseleftDown


	void mouseleftUp(const EventDispatcher &dispatcher, double time)						// mouseleftUp
	{
		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		current.cursor = unproject(current.cursor);

		if(locked)
		{
			if(wholeShape)
				wholeShape->rest();
			locked = false;	// update state to not locked
			Selection::enableKeyboardHandlers(dispatcher);	// enable keyboard handlers
		} // end if
	} // end function mouseleftUp


	void mouseMove(const EventDispatcher &dispatcher, double time)							// mouseMove
	{
		Vector2D<> displacement(current.cursor);	// old cursor

		// find the position of the current cursor in the scene.
		current.cursor.x = dispatcher.mouse.absolute.x;
		current.cursor.y = correction.maxY - dispatcher.mouse.absolute.y;
		current.cursor = unproject(current.cursor);

		if(locked)
		{
			displacement = current.cursor - displacement;
			if(part.first)
				if(dispatcher.keyboard.key[DIK_UP])
					part.first->moveDisconnect(displacement);
				else
					part.first->move(displacement);
			if(part.second && !(dynamic_cast<Plug *>(part.first) && dynamic_cast<Plug *>(part.second) &&
				((Plug *)part.first)->permanent && ((Plug *)part.second)-> permanent &&
				((Plug *)part.first)->parent->parent == ((Plug *)part.second)->parent->parent))
					if(dispatcher.keyboard.key[DIK_UP])
						part.second->moveDisconnect(displacement);
					else
						part.second->move(displacement);
		} // end if
	} // end function mouseMove


}; // end namespace Selection
