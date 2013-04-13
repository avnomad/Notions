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

namespace Selection
{
	extern bool locked;
	extern std::pair<Shape *,Shape *> part;
	extern Shape *wholeShape;


							/************
							* key press *
							************/

	void leftDown(const EventDispatcher &dispatcher, double time)						// leftDown
	{

	} // end function leftDown


	void rightDown(const EventDispatcher &dispatcher, double time)						// rightDown
	{

	} // end function rightDown


	void upDown(const EventDispatcher &dispatcher, double time)							// upDown
	{
		if(locked)
		{
			if(part.first)
				part.first->moveDisconnect(Vector2D<>(0,0));
			if(part.second && !(dynamic_cast<Plug *>(part.first) && dynamic_cast<Plug *>(part.second) &&
				((Plug *)part.first)->permanent && ((Plug *)part.second)-> permanent &&
				((Plug *)part.first)->parent->parent == ((Plug *)part.second)->parent->parent))
					part.second->moveDisconnect(Vector2D<>(0,0));
		} // end if
	} // end function upDown


	void downDown(const EventDispatcher &dispatcher, double time)						// downDown
	{
		if(state.locked)
		{
			state.mode = CONVERSION;
			Conversion::setHandlers(dispatcher);
		} // end if
	} // end function downDown


	void enterDown(const EventDispatcher &dispatcher, double time)						// enterDown
	{
		if(state.locked)
		{
			state.mode = CONVERSION;
			Conversion::setHandlers(dispatcher);
		} // end if
		state.locked = !state.locked;
	} // end function enterDown


							/**************
							* key release *
							**************/

	void leftUp(const EventDispatcher &dispatcher, double time)								// leftUp
	{

	} // end function leftUp


	void rightUp(const EventDispatcher &dispatcher, double time)							// rightUp
	{

	} // end function rightUp


	void upUp(const EventDispatcher &dispatcher, double time)								// upUp
	{
		if(locked)
		{
			if(part.first)
				part.first->move(Vector2D<>(0,0));
			if(part.second && !(dynamic_cast<Plug *>(part.first) && dynamic_cast<Plug *>(part.second) &&
				((Plug *)part.first)->permanent && ((Plug *)part.second)-> permanent &&
				((Plug *)part.first)->parent->parent == ((Plug *)part.second)->parent->parent))
					part.second->move(Vector2D<>(0,0));
		} // end if
	} // end function upUp


	void downUp(const EventDispatcher &dispatcher, double time)								// downUp
	{
		if(!state.locked)
		{
			state.mode = CONVERSION;
			Conversion::setHandlers(dispatcher);
		} // end if
	} // end function downUp


	void enterUp(const EventDispatcher &dispatcher, double time)							// enterUp
	{
		// stay
	} // end function enterUp


}; // end namespace Selection
